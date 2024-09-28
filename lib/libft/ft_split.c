/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:41:54 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/28 02:06:57 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char const *charset)
{
	int	cnt;
	int	pre;

	cnt = 0;
	pre = 1;
	while (*s)
	{
		if (ft_strchr(charset, *s))
			pre = 1;
		else if (pre)
		{
			pre = 0;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static void	*free_memory(char **strs, int i)
{
	while (i--)
		free(strs[i]);
	free(strs);
	return (NULL);
}

static char	**split(char **strs, char const *s, char const *charset)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (*s)
	{
		while (*s && ft_strchr(charset, *s))
			s++;
		if (*s)
		{
			len = 0;
			while (s[len] && !ft_strchr(charset, s[len]))
				len++;
			strs[i] = ft_substr(s, 0, len);
			if (!strs[i])
				return (free_memory(strs, i));
			s += len;
			i++;
		}
	}
	strs[i] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char const *charset)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = (char **)ft_calloc(count_words(s, charset) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	return (split(strs, s, charset));
}
