/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeme.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:41:14 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/07 02:45:37 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pipeme(int fields[2])
{
	if (pipe(fields) == FAILED)
	{
		perror("minishell: pipe");
		// exit(FAILURE);
	}
}
