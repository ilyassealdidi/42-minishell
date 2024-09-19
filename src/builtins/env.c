/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:27:10 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/19 14:14:21 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_env(void *content)
{
	t_environment	*env;

	env = content;
	if (env->hidden == true || isnull(env->element.value))
		return ;
	printf("%s=%s\n", env->element.key, env->element.value);
}

void	builtin_env(t_object *obj)
{
	ft_lstiter(obj->env, print_env);
}
