/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:27:10 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/10 18:21:42 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_env(t_object *obj, t_command *cmd)
{
	t_environment	*env;
	t_list			*node;

	node = obj->env;
	while (node != NULL)
	{
		env = node->content;
		if (env->hidden == false)
		{
			ft_dprintf(cmd->out, "%s=%s\n",
				env->element.key, env->element.value);
		}
		node = node->next;
	}
}
