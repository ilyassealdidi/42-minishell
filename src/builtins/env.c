/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:27:10 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/10 22:56:45 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_env(t_object *obj)
{
	t_environment	*env;
	t_list			*node;

	node = obj->env;
	while (node != NULL)
	{
		env = node->content;
		if (env->hidden == false)
			ft_printf("%s=%s\n", env->element.key, env->element.value);
		node = node->next;
	}
}
