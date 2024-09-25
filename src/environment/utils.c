/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:04:05 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/25 12:40:49 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_size(t_list *env_list, bool exclude_n)
{
	t_list			*node;
	t_environment	*env;
	int				size;

	size = 0;
	node = env_list;
	while (node)
	{
		env = node->content;
		if (!env->hidden)
			size++;
		node = node->next;
	}
	return (size);
}

t_environment	*create_env(t_dictionnary dict, bool hidden)
{
	t_environment	*env;

	env = (t_environment *)ft_calloc(1, sizeof(t_environment));
	if (isnull(env))
		return (NULL);
	env->element = dict;
	env->hidden = hidden;
	if (!hidden)
		env->index = 1;
	return (env);
}

void	destroy_dictionnary(void *content)
{
	t_dictionnary	*dict;

	dict = (t_dictionnary *)content;
	free(dict->key);
	free(dict->value);
}

void	destroy_env(void *content)
{
	t_environment	*env;

	env = (t_environment *)content;
	destroy_dictionnary(&env->element);
	free(env);
}
