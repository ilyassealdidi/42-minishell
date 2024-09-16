/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:12:45 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/17 00:26:09 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_signal(t_object *obj)
{
	int				index;

	if (WIFEXITED(obj->exit_status))
		obj->exit_status = WEXITSTATUS(obj->exit_status);
	else if (WIFSIGNALED(obj->exit_status))
	{
		index = WTERMSIG(obj->exit_status);
		if (index == SIGINT)
		{
			ft_dprintf(STDERR_FILENO, "\n");
			obj->exit_status = 130;
		}
		else if (index == SIGQUIT)
		{
			ft_dprintf(STDERR_FILENO, "Quit: 3\n");
			obj->exit_status = 131;
		}
	}
}

void	ft_wait(t_object *obj)
{
	t_list			*cmds;
	t_command		*cmd;

	cmds = obj->commands;
	while (cmds)
	{
		cmd = cmds->content;
		waitpid(cmd->pid, &obj->exit_status, 0);
		check_signal(obj);
		cmds = cmds->next;
	}
}
