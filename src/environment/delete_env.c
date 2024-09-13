/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:21:57 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/11 00:23:01 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Removes an environment variable from the given environment list.
 *
 * @param env_list The pointer to the head of the environment list.
 * @param key The key of the environment variable to be removed.
 */
void	unset_env(t_list **env_list, char *key)
{
	t_list			*node;
	t_environment	*env;

	node = *env_list;
	while (node)
	{
		env = node->content;
		if (ft_strcmp(env->element.key, key) == 0)
		{
			if (node->previous == NULL)
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
