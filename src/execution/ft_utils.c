/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:42:10 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/11 23:28:49 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	has_redirection(t_command *cmd)
{
	return (cmd->in > 2 || cmd->out > 2);
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
