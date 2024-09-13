/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:15:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/07 22:27:35 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//dupeme is used to redirect the output 
//of the previous command to the input of the next command
//amd close the unused end of the pipe

void	ft_close(int fd)
{
	if (fd == NOTHING)
		return ;
	if (close(fd) == FAILED)				// close the read end of the pipe
		perror("minishell: 322: close");
}

void	ft_dupme(int from, int to, int to_close)
{
	ft_close(to_close);
	if (dup2(from, to) == FAILED)		// redirect the output of the previous command to the input of the next command
		perror("minishell: 321: dup2");
	ft_close(from);
}
