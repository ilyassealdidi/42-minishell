/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 06:13:03 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/22 11:02:29 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_redirect(t_command *cmd)
{
	if (has_redirection(cmd->in))
		ft_dup(cmd->in, STDIN_FILENO, NOTHING);
	if (has_redirection(cmd->out))
		ft_dup(cmd->out, STDOUT_FILENO, NOTHING);
}

void	ft_close_redirections(t_command *cmd)
{
	if (has_redirection(cmd->in))
		ft_close(cmd->in);
	if (has_redirection(cmd->out))
		ft_close(cmd->out);
}
