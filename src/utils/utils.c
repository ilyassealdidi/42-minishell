/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:27:41 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/18 16:31:30 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	update_exit_status(t_object *obj, int status)
// {
// 	obj->exit_status = status;
// 	return (status);
// }

bool	isset(void *ptr)
{
	return (ptr != NULL);
}

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (str == NULL)
		return (NULL);
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
