/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:27:10 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/09 22:27:42 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_env(t_object *obj, t_command *cmd)
{
	t_environment	*env;
	t_list			*node;

	node = obj->env;
	while (node != NULL)
	{
		env = node->content;
		if (env->hidden == false)
		{
			ft_putstr_fd(env->element.key, cmd->out);
			ft_putstr_fd("=", cmd->out);
			ft_putendl_fd(env->element.value, cmd->out);
		}
		node = node->next;
	}
	return (SUCCESS);
}
