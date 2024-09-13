/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:24:08 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/11 00:24:19 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Appends a key-value pair to the environment list or updates the value
 * if the key already exists.
 *
 * @param env_list The pointer to the environment list.
 * @param dict The dictionary containing the key-value pair to be appended
 * or updated.
 * @return Returns SUCCESS if the operation is successful,
 * otherwise returns FAILURE.
 */
int	append_env(t_list **env_list, t_dictionnary dict)
{
	t_list			*tmp;
	t_dictionnary	*element;

	tmp = *env_list;
	while (tmp)
	{
		element = tmp->content;
		if (ft_strcmp(element->key, dict.key) == 0)
		{
			if (dict.value == NULL)
				return (SUCCESS);
			element->value = ft_strjoin_free(element->value, dict.value, LEFT);
			if (element->value == NULL)
				return (FAILURE);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	if (insert_env(env_list, dict, false) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
