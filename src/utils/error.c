/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:47:26 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/29 16:25:36 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error(int status, char *arg)
{
	(void)arg;
	ft_putstr_fd("minishell: ", 2);
	if (status == ERROR)
		ft_putstr_fd(SYNTAX_ERR, 2);
	else if (status == FAILURE)
		ft_putstr_fd(MEMORY_ERR, 2);
}
