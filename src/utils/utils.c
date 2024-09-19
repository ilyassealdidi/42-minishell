/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:27:41 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/19 09:35:27 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	isset(void *ptr)
{
	return (ptr != NULL);
}

bool	is_builtin(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, B_ECHO) == 0
		|| ft_strcmp(str, B_CD) == 0
		|| ft_strcmp(str, B_PWD) == 0
		|| ft_strcmp(str, B_EXPORT) == 0
		|| ft_strcmp(str, B_UNSET) == 0
		|| ft_strcmp(str, B_ENV) == 0
		|| ft_strcmp(str, B_EXIT) == 0)
		return (true);
	return (false);
}
