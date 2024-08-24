/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:28:33 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/24 16:24:46 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*dict_toenv(t_dictionnary *dict)
{
	char	*key;
	char	*env;

	key = ft_strjoin(dict->key, "=");
	if (key == NULL)
		return (NULL);
	env = ft_strjoin_free(key, dict->value, LEFT);
	if (env == NULL)
		return (free(key), NULL);
	return (env);
}

// char	**generate_envp(t_list *list)
// {
// 	int				i;
// 	int				count;
// 	char			**array;
// 	t_environment	*env;

// 	count = ft_lstsize(list);
// 	array = malloc(sizeof(char *) * (count + 1));
// 	if (array == NULL)
// 		return (NULL);
// 	array[count] = NULL;
// 	i = 0;
// 	while (list)
// 	{
// 		env = list->content;
// 		if (env->hidden == false)
// 		{
// 			array[i] = dict_toenv(&env->element);
// 			if (array[i] == NULL)
// 				return (free_array(array), FAILURE);
// 			i++;
// 		}
// 		list = list->next;
// 	}
// 	return (array);		
// }
