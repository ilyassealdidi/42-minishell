/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:20:43 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/22 13:43:30 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Sets the value of an environment variable in the given environment list.
 * If the variable does not exist, it gets created.
 *
 * @param env_list The pointer to the environment list.
 * @param dict The dictionary containing the key-value pair to set.
 * @return Returns SUCCESS if the variable is successfully set,
 * FAILURE otherwise.
 */
int set_env(t_list **env_list, t_dictionnary dict)
{
	t_list          *tmp;
	t_environment   *env;

	tmp = *env_list;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strcmp(env->element.key, dict.key) == 0)
		{
			if (dict.value == NULL)
				return (SUCCESS);
			free(env->element.value);
			env->element.value = ft_strdup(dict.value);
			if (env->element.value == NULL && dict.value != NULL)
				return (FAILURE);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	if (insert_env(env_list, dict, false) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
