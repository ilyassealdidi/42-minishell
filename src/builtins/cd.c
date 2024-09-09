/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:55:06 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/09 22:52:22 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	update_oldpwd(t_object *obj)
{
	t_dictionnary	dict;

	dict.key = "OLDPWD";
	dict.value = get_env(obj->env, "PWD");
	if (dict.value != NULL && set_env(&obj->env, dict) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	update_pwd(t_object *obj)
{
	t_dictionnary	dict;

	dict.key = "PWD";
	dict.value = getcwd(NULL, 0);
	if (dict.value == NULL || set_env(&obj->env, dict) == FAILURE)
		return (free(dict.value), FAILURE);
	return (SUCCESS);
}

int	builtin_cd(t_object *obj, t_command *command)
{
	char	*path;

	if (command->argv[1] == NULL)
		path = get_env(obj->env, "HOME");
	else
		path = command->argv[1];
	if (path == NULL)
	{
		ft_error(CD, EMHNS, NULL);
		obj->exit_status = 1;
		return (FAILURE);
	}
	if (chdir(path) == -1)
	{
		ft_error(CD, path, NULL);
		obj->exit_status = 1;
		return (FAILURE);
	}
	if (update_oldpwd(obj) == FAILURE || update_pwd(obj) == FAILURE)
		return (obj->exit_status = 1, FAILURE); //Should the error be printed here?
	return (SUCCESS);
}
