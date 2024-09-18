/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:47:26 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/18 16:26:32 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_error(string location, string cause, string error)
{
	ft_dprintf(STDERR_FILENO, "minishell: ");
	if (location != NULL)
		ft_dprintf(STDERR_FILENO, "%s: ", location);
	if (error != NULL)
	{
		if (cause != NULL)
			ft_dprintf(STDERR_FILENO, "%s: ", cause);
		ft_dprintf(STDERR_FILENO, "%s\n", error);
	}
	else
		perror(cause);
}
