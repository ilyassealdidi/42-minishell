/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:12:45 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/16 09:15:34 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_wait(t_object *obj)
{
	t_list			*cmds;
	t_command		*cmd;
	int				index;

	cmds = obj->commands;
	while (cmds)
	{
		cmd = cmds->content;
		waitpid(cmd->pid, &obj->exit_status, 0);
		if (WIFEXITED(obj->exit_status))
			obj->exit_status = WEXITSTATUS(obj->exit_status);
		cmds = cmds->next;
	}
}
