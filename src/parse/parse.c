/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/19 09:32:44 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	update_exit_status(t_object *obj)
{
	string			value;

	if (g_received_signal != obj->received_signals)
	{
		obj->exit_status = 1;
		obj->received_signals = g_received_signal;
	}
	if (ft_atoi(get_env(obj->env, "?")) != obj->exit_status)
	{
		value = ft_itoa(obj->exit_status);
		if (value == NULL)
			return (FAILURE);
		if (set_env(&obj->env, (t_dictionnary){"?", value}) == FAILURE)
			return (free(value), FAILURE);
		free(value);
	}
	return (SUCCESS);
}

static int	parse(t_object *obj)
{
	string			line;

	if (obj->exit_status == 0)
		line = readline(SUCCESS_PROMPT);
	else
		line = readline(FAILURE_PROMPT);
	if (line == NULL)
		exit_shell(obj);
	if (line[0] != '\0')
		add_history(line);
	if (update_exit_status(obj) == FAILURE)
		return (free(line), FAILURE);
	obj->exit_status = tokens_init(obj, line);
	free(line);
	if (obj->exit_status == FAILURE)
		return (perror(EMBASE),
			ft_lstclear(&obj->tokens, destroy_token), FAILURE);
	if (obj->exit_status == ERROR)
		return (ft_error(NULL, NULL, EMSYNTAX),
			ft_lstclear(&obj->tokens, destroy_token), FAILURE);
	return (SUCCESS);
}

int	generate_commands(t_object *obj)
{
	if (parse(obj) == FAILURE)
		return (FAILURE);
	if (heredocs_init(obj) == FAILURE)
		return (ft_lstclear(&obj->tokens, destroy_token), FAILURE);
	if (commands_init(obj) == FAILURE)
		return (perror(EMBASE), ft_lstclear(&obj->tokens, destroy_token),
			FAILURE);
	ft_lstclear(&obj->tokens, destroy_token);
	return (SUCCESS);
}
