/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:19:36 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/29 16:20:55 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Sets the index values for the given environment variable and its
 * corresponding linked list.
 * The index value represents the position of the environment
 * variable in the list.
 * 
 * @param env The environment variable to set the index for.
 * @param env_list The linked list containing the environment variables.
 */
void	set_index(t_environment *new, t_list *env_list)
{
	t_environment	*node;
	int				index;
	int				ret;

	if (new->hidden == true)
		return ;
	index = 0;
	while (env_list)
	{
		node = env_list->content;
		if (node->hidden == false)
		{
			ret = ft_strcmp(node->element.key, new->element.key);
			if (ret > 0)
				node->index++;
			else if (ret < 0)
				new->index++;
		}
		env_list = env_list->next;
	}
}

/**
 * Inserts a new environment variable into the environment list.
 * 
 * @attention the values of the dictionary *dict* are duplicated.
 * so you have to free them after calling this function.
 *
 * @param env_list The pointer to the environment list.
 * @param dict The dictionary containing the key-value pair
 * of the environment variable.
 * @param hidden A boolean value indicating whether the environment
 * variable is hidden.
 * @return Returns SUCCESS if the environment variable is successfully inserted,
 * otherwise FAILURE.
 */
int insert_env(t_list **env_list, t_dictionnary dict, bool hidden)
{
	t_list          *new;
	t_environment   *env;
	t_dictionnary   newdict;

	newdict.key = ft_strdup(dict.key);
	if (dict.value != NULL)
		newdict.value = ft_strdup(dict.value);
	else
		newdict.value = NULL;
	if (newdict.key == NULL || (newdict.value == NULL && dict.value != NULL))
		return (destroy_dictionnary(&newdict), FAILURE);
	env = create_env(newdict, hidden);
	if (env == NULL)
		return (destroy_dictionnary(&newdict), FAILURE);
	set_index(env, *env_list);
	new = ft_lstnew(env);
	if (new == NULL)
		return (destroy_env(env), FAILURE);
	ft_lstadd_back(env_list, new);
	return (SUCCESS);
}
