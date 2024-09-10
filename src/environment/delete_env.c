/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:21:57 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/10 16:05:48 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
