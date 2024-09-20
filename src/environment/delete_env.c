/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:21:57 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/20 18:54:51 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Decrements the index of all environment variables in the given list
 * that have an index greater than the specified index.
 *
 * @param env_list The list of environment variables.
 * @param index The index to compare against.
 */
void	decrement_env_index(t_list *env_list, int index)
{
	t_list			*node;
	t_environment	*env;

	node = env_list;
	while (node)
	{
		env = node->content;
		if (env->index > index)
			env->index--;
		node = node->next;
	}
}

/**
 * Removes an environment variable from the given environment list.
 *
 * @param env_list The pointer to the head of the environment list.
 * @param key The key of the environment variable to be removed.
 */
void	unset_env(t_list **env_list, t_string key)
{
	t_list			*node;
	t_environment	*env;

	node = *env_list;
	while (node)
	{
		env = node->content;
		if (ft_strcmp(env->element.key, key) == 0)
		{
			decrement_env_index(*env_list, env->index);
			if (isnull(node->previous))
				*env_list = node->next;
			else
			{
				node->previous->next = node->next;
				if (node->next != NULL)
					node->next->previous = node->previous;
			}
			ft_lstdelone(node, destroy_env);
			break ;
		}
		node = node->next;
	}
}
