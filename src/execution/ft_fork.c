/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:43:02 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/17 00:13:05 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		ft_error(NULL, NULL, NULL);
	return (pid);
}
