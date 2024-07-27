/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:52:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/26 02:16:00 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_env(t_object *obj, char **env)
{
	t_dictionnary	*element;
	char			*key;
	char			*value;

	while (*env)
	{
		key = ft_substr(*env, 0, ft_strchr(*env, '=') - *env);
		if (key == NULL)
			return (FAILURE);
		value = ft_strdup(ft_strchr(*env, '=') + 1);
		if (value == NULL)
			return (FAILURE);
		element = create_element(key, value);
		if (element == NULL)
			return (FAILURE);
		ft_lstadd_back(&obj->env, ft_lstnew(element));
		env++;
	}
	return (SUCCESS);
}
