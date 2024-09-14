/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/14 12:29:52 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	parse(t_object *obj)
{
	char			*line;

	line = readline(PROMPT);
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
		return (ft_error(NULL, NULL, SYNTAX_ERR),
			ft_lstclear(&obj->tokens, destroy_token), FAILURE);
	return (SUCCESS);
}

int	generate_commands(t_object *obj)
{
	if (parse(obj) == FAILURE)
		return (FAILURE);
	if (heredocs_init(obj) == FAILURE)
		return (ft_lstclear(&obj->tokens, destroy_token), FAILURE);
	if (commands_init(obj) == FAILURE || set_exit_status(obj) == FAILURE) // Why set_exit_status is here?
		return (perror(EMBASE), ft_lstclear(&obj->tokens, destroy_token),
			FAILURE);
	ft_lstclear(&obj->tokens, destroy_token);
	// ft_lstiter(obj->commands, display_command);
	return (SUCCESS);
}
