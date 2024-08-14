/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:52:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/14 08:31:32 by ialdidi          ###   ########.fr       */
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

char	*get_env(t_object *obj, char *key)
{
	t_list			*tmp;
	t_dictionnary	*element;

	tmp = obj->env;
	while (tmp)
	{
		element = tmp->content;
		if (ft_strcmp(element->key, key) == 0)
			return (element->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	set_env(t_object *obj, char *key, char *value)
{
	t_list			*tmp;
	t_dictionnary	*element;

	tmp = obj->env;
	while (tmp)
	{
		element = tmp->content;
		if (ft_strcmp(element->key, key) == 0)
		{
			free(element->value);
			element->value = ft_strdup(value);
			if (element->value == NULL)
				return (FAILURE);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	element = create_element(key, value);
	if (element == NULL)
		return (FAILURE);
	ft_lstadd_back(&obj->env, ft_lstnew(element));
	return (SUCCESS);
}
