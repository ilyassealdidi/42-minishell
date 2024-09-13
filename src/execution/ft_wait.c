/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:12:45 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/12 01:42:57 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_wait(int *exit_status)
{
	while (waitpid(-1, exit_status, 0) != FAILED)
	{
		if (WIFEXITED(*exit_status))
			*exit_status = WEXITSTATUS(*exit_status);
	}
}
