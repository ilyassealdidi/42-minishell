/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:52:24 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/24 16:45:10 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_shell_env(t_list **env_list)
{
	char	*pwd;

	if (insert_env(env_list, (t_dictionnary){"?", "0"}, 1) == FAILURE
		|| insert_env(env_list, (t_dictionnary){"@OLDPWD", NULL}, 1) == FAILURE)
		return (FAILURE);
	if (isset(get_env(*env_list, "OLDPWD")))
		unset_env(env_list, "OLDPWD");
	if (insert_env(env_list, (t_dictionnary){"OLDPWD", NULL}, 0) == FAILURE)
		return (FAILURE);
	pwd = getcwd(NULL, 0);
	if (isnull(pwd))
		ft_error(NULL, NULL, EMRCD);
	if (!isset(get_env(*env_list, "PWD")))
	{
		if (insert_env(env_list, (t_dictionnary){"PWD", pwd}, 0) == FAILURE)
			return (free(pwd), FAILURE);
	}
	if (insert_env(env_list, (t_dictionnary){"@PWD", pwd}, 1) == FAILURE)
		return (free(pwd), FAILURE);
	free(pwd);
	return (SUCCESS);
}

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
	if (init_shell_env(env_list) == FAILURE)
		return (ft_lstclear(env_list, destroy_env), FAILURE);
	return (SUCCESS);
}
