/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:42:10 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/23 20:07:14 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	has_redirection(int fd)
{
	return (fd > 2);
}

bool	has_next(t_list *node)
{
	return (node->next != NULL);
}

bool	is_parent(pid_t pid)
{
	return (pid != CHILD);
}

bool	is_child(pid_t pid)
{
	return (pid == CHILD);
}

void	is_directory(t_command *cmd)
{
	struct stat		path_stat;

	if (ft_strchr(cmd->cmd, '/') && stat(cmd->cmd, &path_stat) == SUCCESS)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_error(NULL, cmd->cmd, EMISDIR);
			exit(126);
		}
	}
}
