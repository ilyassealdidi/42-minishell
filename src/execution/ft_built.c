/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 06:15:31 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/13 11:33:08 by aaitelka         ###   ########.fr       */
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

	command = node->content;
	if (command_is(command->cmd, EXIT))
		status = builtin_exit(obj, command);
	else if (command_is(command->cmd, ECHO))
		builtin_echo(command);
	else if (command_is(command->cmd, EXPORT))
		status = builtin_export(obj, command);
	else if (command_is(command->cmd, CD))
		status = builtin_cd(obj, command);
	else if (command_is(command->cmd, PWD))
		status = builtin_pwd(obj);
	else if (command_is(command->cmd, ENV))
		builtin_env(obj);
	else if (command_is(command->cmd, UNSET))
		status = builtin_unset(obj, command);
	return (status);
}
