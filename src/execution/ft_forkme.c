/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forkme.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:43:02 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/07 23:57:20 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	ft_forkme(t_object *obj)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
	{
		ft_close(obj->pipefd[PIN]);
		ft_close(obj->pipefd[POUT]);
		perror("minishell: fork");
	}
	return (pid);
}