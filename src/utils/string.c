/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:34:44 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/20 18:55:00 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_string	ft_strjoin_free(t_string s1, t_string s2, int to_free)
{
	t_string			str;

	str = ft_strjoin(s1, s2);
	if (to_free == LEFT)
		free(s1);
	else if (to_free == RIGHT)
		free(s2);
	else if (to_free == BOTH)
	{
		free(s1);
		free(s2);
	}
	return (str);
}
