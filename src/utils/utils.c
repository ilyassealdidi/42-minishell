/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:27:41 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/11 21:20:27 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_exit_status(t_object *obj)
{
	char			*value;

	value = ft_itoa(obj->exit_status);
	if (value == NULL)
		return (FAILURE);
	if (set_env(&obj->env, (t_dictionnary){"?", value}) == FAILURE)
		return (free(value), FAILURE);
	free(value);
	return (SUCCESS);
}

bool	isset(void *ptr)
{
	return (ptr != NULL);
}

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char			*str;

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

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, ECHO) == 0
		|| ft_strcmp(str, CD) == 0
		|| ft_strcmp(str, PWD) == 0
		|| ft_strcmp(str, EXPORT) == 0
		|| ft_strcmp(str, UNSET) == 0
		|| ft_strcmp(str, ENV) == 0
		|| ft_strcmp(str, EXIT) == 0)
		return (true);
	return (false);
}
