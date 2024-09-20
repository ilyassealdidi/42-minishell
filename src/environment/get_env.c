/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:24:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/20 18:54:51 by ialdidi          ###   ########.fr       */
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
t_string	get_env(t_list *env_list, t_string key)
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
