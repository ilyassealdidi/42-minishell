/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:47:26 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/21 15:56:34 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_error(t_string location, t_string cause, t_string error)
{
	ft_dprintf(STDERR_FILENO, "minishell: ");
	if (!isnull(location))
		ft_dprintf(STDERR_FILENO, "%s: ", location);
	if (!isnull(error))
	{
		if (!isnull(cause))
			ft_dprintf(STDERR_FILENO, "%s: ", cause);
		ft_dprintf(STDERR_FILENO, "%s\n", error);
	}
	else
		perror(cause);
}
