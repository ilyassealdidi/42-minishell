/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:59:11 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/10 10:41:40 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
NULL ""
NULL echo
echo ""
NULL echo
echo >

*/
char	*join(char *str1, char *str2)
{
	char	*joined;

	if (str1 != NULL && *str1 != '\0' && *str2 == '\0')
		return (str1);
	if (*str2 == '\0')
	{
		str2 = ft_strdup("");
		if (str2 == NULL)
			return (free(str1), NULL);
	}
	joined = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (joined);
}
