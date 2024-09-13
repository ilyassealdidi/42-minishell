/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 06:13:03 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/11 01:48:48 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//redirect the file descriptor to the right place
//2 means another file are opened
//so we need to duplicate it to the std{in||out}
void	ft_redirect(t_command *cmd)
{
	if (cmd->in > 2)
		ft_dup(cmd->in, STDIN_FILENO, NOTHING);
	if (cmd->out > 2)
		ft_dup(cmd->out, STDOUT_FILENO, NOTHING);
}

void	ft_close_redirections(t_command *cmd)
{
	if (cmd->in > 2)
		ft_close(cmd->in);
	if (cmd->out > 2)
		ft_close(cmd->out);
}
