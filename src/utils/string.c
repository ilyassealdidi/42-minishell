/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:34:44 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/19 09:35:22 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

string	ft_strjoin_free(string s1, string s2, int to_free)
{
	string			str;

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