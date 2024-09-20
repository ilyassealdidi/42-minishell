/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 06:30:37 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/19 23:37:52 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_save_fd(int *fd, int src)
{
	*fd = dup(src);  //! The function must return a value
	if (*fd == FAILED)
		ft_error(NULL, NULL, NULL);
}
