/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:15:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/19 23:37:19 by ialdidi          ###   ########.fr       */
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
	if (dup2(from, to) == FAILED) //! The function must return a value
		ft_error(NULL, NULL, NULL);
	ft_close(from);
}
