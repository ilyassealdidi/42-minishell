/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/21 16:50:26 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	update_exit_status(t_object *obj)
{
	t_string		value;

	if (g_received_signal != obj->received_signals)
	{
		obj->exit_status = 1;
		obj->received_signals = g_received_signal;
	}
	if (ft_atoi(get_env(obj->env, "?")) != obj->exit_status)
	{
		value = ft_itoa(obj->exit_status);
		if (isnull(value))
			return (FAILURE);
		if (set_env(&obj->env, (t_dictionnary){"?", value}) == FAILURE)
			return (free(value), FAILURE);
		free(value);
	}
	return (SUCCESS);
}

static t_string	read_line(t_object *obj)
{
	t_string		line;
	t_string		trimmed_line;

	if (obj->exit_status == SUCCESS)
		line = readline(SUCCESS_PROMPT);
	else
		line = readline(FAILURE_PROMPT);
	if (isnull(line))
		exit_shell(obj);
	if (*line != '\0')
		add_history(line);
	trimmed_line = ft_strtrim(line, " \t");
	free(line);
	return (trimmed_line);
}

static int	parse(t_object *obj)
{
	t_string		line;

	line = read_line(obj);
	if (isnull(line))
		return (perror(EMBASE), obj->exit_status = 1, FAILURE);
	if (update_exit_status(obj) == FAILURE)
		return (perror(EMBASE), obj->exit_status = 1, free(line), FAILURE);
	if (*line == '\0')
		return (FAILURE);
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
	if (heredocs_init(obj) == FAILURE || commands_init(obj) == FAILURE)
		return (perror(EMBASE), ft_lstclear(&obj->tokens, destroy_token),
			FAILURE);
	ft_lstclear(&obj->tokens, destroy_token);
	return (SUCCESS);
}
