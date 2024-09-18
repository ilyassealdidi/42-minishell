/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:59:32 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/17 14:35:31 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = NULL;
	while (*s)
	{
		if (*s == (char)c)
			str = (char *)s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (str);
}
