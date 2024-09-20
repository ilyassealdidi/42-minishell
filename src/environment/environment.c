/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:52:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/19 22:12:29 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * Initializes the environment list with the given environment variables.
 * The environment contains also the exit status of the last command.
 *
 * @param env_list The pointer to the environment list.
 * @param envp The array of environment variables.
 * @return Returns SUCCESS if the initialization is successful,
 * otherwise returns FAILURE.
 */
int	init_env(t_list **env_list, char **envp)
{
	t_dictionnary	dict;

	while (*envp)
	{
		dict.key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		dict.value = ft_strdup(ft_strchr(*envp, '=') + 1);
		if (isnull(dict.key) || isnull(dict.value)
			|| insert_env(env_list, dict, false) == FAILURE)
			return (ft_lstclear(env_list, destroy_env),
				destroy_dictionnary(&dict), FAILURE);
		destroy_dictionnary(&dict);
		envp++;
	}
	if (insert_env(env_list, (t_dictionnary){"?", "0"}, 1) == FAILURE
		|| insert_env(env_list, (t_dictionnary){"OLDPWD", NULL}, 0) == FAILURE
		|| insert_env(env_list, (t_dictionnary){"PWD", NULL}, 0) == FAILURE)
		return (ft_lstclear(env_list, destroy_env), FAILURE);
	return (SUCCESS);
}
