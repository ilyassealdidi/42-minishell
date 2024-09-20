/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:04:05 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/20 18:59:44 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
