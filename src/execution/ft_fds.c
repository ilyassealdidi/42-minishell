/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 06:30:37 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/16 17:11:33 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_save_fd(int *fd, int src)
{
	*fd = dup(src);
	if (*fd == FAILED)
		perror("minishell: dup"); //! use ft_error(NULL, NULL, NULL);
}
