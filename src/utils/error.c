/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:47:26 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/05 16:46:01 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error(int status, char *arg)
{
	(void)arg;
	ft_putstr_fd("minishell: ", 2);
	if (status == ERROR)
		return ;
		// ft_putstr_fd(SYNTAX_ERR, 2);
	else if (status == FAILURE)
		ft_putstr_fd(MEMORY_ERR, 2);
}
