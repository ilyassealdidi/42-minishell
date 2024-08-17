/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:54:20 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/17 17:55:11 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_bit(int *n, int pos)
{
	*n |= (1 << pos);
}

void	clear_bit(int *n, int pos)
{
	*n &= ~(1 << pos);
}

bool	check_bit(int n, int pos)
{
	return ((n & (1 << pos)) != 0);
}

int		toggle_bit(int n, int pos)
{
	return (n ^ (1 << pos));
}

void	unset_bit(int *n, int pos)
{
	*n &= ~(1 << pos);
}
