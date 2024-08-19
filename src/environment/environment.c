/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:52:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/19 15:42:09 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Retrieves the value of an environment variable given its key.
 *
 * @param env_list The linked list of environment variables.
 * @param key The key of the environment variable to retrieve.
 * @return The value of the environment variable if found, NULL otherwise.
 */
char *get_env(t_list *env_list, char *key)
{
	t_environment *env;

	while (env_list)
	{
		env = env_list->content;
		if (ft_strcmp(env->element.key, key) == 0)
			return (env->element.value);
		env_list = env_list->next;
	}
	return (NULL);
}

/**
 * Inserts a new environment variable into the environment list.
 * 
 * @attention the values of the dictionary *dict* are duplicated.
 * so you have to free them after calling this function.
 *
 * @param env_list The pointer to the environment list.
 * @param dict The dictionary containing the key-value pair
 * of the environment variable.
 * @param hidden A boolean value indicating whether the environment
 * variable is hidden.
 * @return Returns SUCCESS if the environment variable is successfully inserted,
 * otherwise FAILURE.
 */
int insert_env(t_list **env_list, t_dictionnary dict, bool hidden)
{
	t_list          *new;
	t_environment   *env;
	t_dictionnary   newdict;

	if (dict.key == NULL || dict.value == NULL)
		return (FAILURE);
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

/**
 * Sets the value of an environment variable in the given environment list.
 * If the variable does not exist, it gets created.
 *
 * @param env_list The pointer to the environment list.
 * @param dict The dictionary containing the key-value pair to set.
 * @return Returns SUCCESS if the variable is successfully set,
 * FAILURE otherwise.
 */
int set_env(t_list **env_list, t_dictionnary dict)
{
	t_list          *tmp;
	t_environment   *env;

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
	if (insert_env(env_list, dict, false) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * Appends a key-value pair to the environment list or updates the value
 * if the key already exists.
 *
 * @param env_list The pointer to the environment list.
 * @param dict The dictionary containing the key-value pair to be appended
 * or updated.
 * @return Returns SUCCESS if the operation is successful,
 * otherwise returns FAILURE.
 */
int append_env(t_list **env_list, t_dictionnary dict)
{
	t_list          *tmp;
	t_dictionnary   *element;

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
	if (insert_env(env_list, dict, false) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * Initializes the environment list with the given environment variables.
 * The environment contains also the exit status of the last command.
 *
 * @param env_list The pointer to the environment list.
 * @param envp The array of environment variables.
 * @return Returns SUCCESS if the initialization is successful,
 * otherwise returns FAILURE.
 */
int	init_env(t_list **env_list, char **envp)
{
	t_environment	*env;
	t_dictionnary	dict;

	while (*envp)
	{
		dict.key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		dict.value = ft_strdup(ft_strchr(*envp, '=') + 1);
		if (insert_env(env_list, dict, false) == FAILURE)
			return (ft_lstclear(env_list, destroy_env),
				destroy_dictionnary(&dict), FAILURE);
		destroy_dictionnary(&dict);
		envp++;
	}
	if (insert_env(env_list, (t_dictionnary){"?", "0"}, true) == FAILURE
		|| insert_env(env_list, (t_dictionnary){"OLDPWD", ""}, true) == FAILURE)
		return (ft_lstclear(env_list, destroy_env), FAILURE);
	return (SUCCESS);
}
