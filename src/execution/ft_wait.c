/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:12:45 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/16 15:51:12 by ialdidi          ###   ########.fr       */
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
		else if (WIFSIGNALED(obj->exit_status))
		{
			index = WTERMSIG(obj->exit_status);
			if (index == SIGINT)
			{
				ft_dprintf(STDERR_FILENO ,"\n");
				obj->exit_status = 130;
			}
			else if (index == SIGQUIT)
			{
				ft_dprintf(STDERR_FILENO ,"Quit: 3\n");
				obj->exit_status = 131;
			}
		}
		cmds = cmds->next;
	}
}
