/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:43:02 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/11 23:08:42 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	ft_fork(t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		perror("minishell: fork");
	return (pid);
}
