/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:15:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/17 00:12:46 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_close(int fd)
{
	if (fd == NOTHING)
		return ;
	close(fd);
}

void	ft_dup(int from, int to, int to_close)
{
	ft_close(to_close);
	if (dup2(from, to) == FAILED)
		ft_error(NULL, NULL, NULL);
	ft_close(from);
}
