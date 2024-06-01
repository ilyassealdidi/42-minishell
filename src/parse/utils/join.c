/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:59:11 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/31 10:59:27 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*join(char *str1, char *str2)
{
	char	*tmp;
	char	*joined;

	if (!str1)
	{
		tmp = ft_strdup(str2);
		if (tmp == NULL)
			free(str2);
		return (tmp);
	}
	tmp = str1;
	joined = ft_strjoin(str1, str2);
	free(tmp);
	if (joined == NULL)
		return (NULL);
	return (joined);
}
