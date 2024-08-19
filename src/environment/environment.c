/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:52:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/19 10:27:33 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env(t_list *env_list, char *key)
{
	t_environment	*env;

	while (env_list)
	{
		env = env_list->content;
		if (ft_strcmp(env->element.key, key) == 0)
			return (env->element.value);
		env_list = env_list->next;
	}
	return (NULL);
}

int	insert_env(t_list **env_list, t_dictionnary dict, bool hidden)
{
	t_list			*new;
	t_environment	*env;
	t_dictionnary	newdict;

	newdict.key = ft_strdup(dict.key);
	newdict.value = ft_strdup(dict.value);
	if (newdict.key == NULL || newdict.value == NULL)
		return (destroy_dictionnary(&newdict), FAILURE);	
	env = create_env(newdict, hidden);
	if (env == NULL)
		return (destroy_dictionnary(&newdict), FAILURE);
	new = ft_lstnew(env);
	if (new == NULL)
		return (destroy_env(env), FAILURE);
	ft_lstadd_back(env_list, new);
	return (SUCCESS);
}

int	set_env(t_list **env_list, t_dictionnary dict)
{
	t_list			*tmp;
	t_environment	*env;

	tmp = *env_list;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strcmp(env->element.key, dict.key) == 0)
		{
			free(env->element.value);
			env->element.value = ft_strdup(dict.value);
			if (env->element.value == NULL)
				return (FAILURE);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	if (insert_env(env_list, dict, true) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	append_env(t_list **env_list, t_dictionnary dict)
{
	t_list			*tmp;
	t_dictionnary	*element;

	tmp = *env_list;
	while (tmp)
	{
		element = tmp->content;
		if (ft_strcmp(element->key, dict.key) == 0)
		{
			element->value = ft_strjoin_free(element->value, dict.value, LEFT);
			if (element->value == NULL)
				return (FAILURE);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	if (insert_env(env_list, dict, true) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	init_env(t_list **env_list, char **envp)
{
	t_environment	*env;
	t_dictionnary	dict;

	while (*envp)
	{
		dict.key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		dict.value = ft_strdup(ft_strchr(*envp, '=') + 1);
		if (dict.key == NULL || dict.value == NULL)
			return (destroy_dictionnary(&dict), FAILURE);
		if (insert_env(env_list, dict, true) == FAILURE)
			return (destroy_dictionnary(&dict), FAILURE);
		destroy_dictionnary(&dict);
		envp++;
	}
	if (insert_env(env_list, (t_dictionnary){"?", "0"}, false) == FAILURE)
		return (ft_lstclear(env_list, destroy_env), FAILURE);
	return (SUCCESS);
}
