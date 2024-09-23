/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 06:15:31 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/23 16:36:45 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	command_is(char *str, char *cmd)
{
	return (ft_strcmp(str, cmd) == SUCCESS);
}

int	execute_builtin(t_object *obj, t_list *node)
{
	t_command	*command;
	int			status;

	status = SUCCESS;
	command = node->content;
	if (command->in == FAILED || command->out == FAILED)
		return (FAILURE);
	if (command_is(command->cmd, B_EXIT))
		status = builtin_exit(obj, command);
	else if (command_is(command->cmd, B_ECHO))
		builtin_echo(command);
	else if (command_is(command->cmd, B_EXPORT))
		status = builtin_export(obj, command);
	else if (command_is(command->cmd, B_CD))
		status = builtin_cd(obj, command);
	else if (command_is(command->cmd, B_PWD))
		status = builtin_pwd(obj);
	else if (command_is(command->cmd, B_ENV))
		builtin_env(obj);
	else if (command_is(command->cmd, B_UNSET))
		status = builtin_unset(obj, command);
	return (status);
}
