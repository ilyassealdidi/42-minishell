/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:47:26 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/19 13:21:03 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error(int status, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (status == ERROR)
		ft_putstr_fd(SYNTAX_ERR, 2);
	else if (status == FAILURE)
		ft_putstr_fd(MEMORY_ERR, 2);
	else if (status == INVALID_IDENTIFIER)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(INVALID_IDENTIFIER_ERR, 2);
	}
}
