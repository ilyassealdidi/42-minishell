/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_seperator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:25:13 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/21 19:48:09 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*is_seperator(char	*str)
{
	static char	*seps[] = {"|", ">>", "<<", ">", "<", NULL};
	int			i;

	i = -1;
	while (seps[++i] != NULL)
		if (strncmp(str, seps[i], strlen(seps[i])) == 0)
			return (seps[i]);
	return (NULL);
}
