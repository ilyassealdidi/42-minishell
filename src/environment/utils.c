/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:04:05 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/18 11:51:44 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_environment	*create_env(t_dictionnary dict, bool is_visible)
{
	t_environment	*env;

	env = (t_environment *)malloc(sizeof(t_environment));
	if (env == NULL)
		return (NULL);
	env->element = dict;
	env->is_visible = is_visible;
	return (env);
}

void	destroy_env(void *content)
{
	t_environment	*env;

	env = (t_environment *)content;
	destroy_dictionnary(&env->element);
	free(env);
}
