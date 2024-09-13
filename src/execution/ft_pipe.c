/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:41:14 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/11 04:07:48 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pipe(int fields[2])
{
	if (pipe(fields) == FAILED)
		perror("minishell: pipe");
}

void	ft_pipe_in(t_list *cmds, t_command *cmd)
{
	if (has_next(cmds))
		ft_dup(cmd->pipefd[PIN], STDIN_FILENO, cmd->pipefd[POUT]);
}

void	ft_pipe_out(t_list *cmds, t_command *cmd)
{
	if (has_next(cmds))
		ft_dup(cmd->pipefd[POUT], STDOUT_FILENO, cmd->pipefd[PIN]);
}
