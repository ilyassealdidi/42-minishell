/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:55:06 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/20 18:54:51 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	update_oldpwd(t_object *obj)
{
	t_dictionnary	dict;

	dict.key = "OLDPWD";
	dict.value = get_env(obj->env, "PWD");
	if (dict.value != NULL)
	{
		if (set_env(&obj->env, dict) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	update_pwd(t_object *obj)
{
	t_dictionnary	dict;

	dict.key = "PWD";
	dict.value = getcwd(NULL, 0);
	if (isnull(dict.value))
	{
		free(dict.value);
		ft_error(B_CD, "error retrieving current directory: getcwd: ", NULL);
		return (FAILURE);
	}
	if (set_env(&obj->env, dict) == FAILURE)
	{
		free(dict.value);
		obj->exit_status = 1;
		ft_error(NULL, NULL, NULL);
		return (FAILURE);
	}
	free(dict.value);
	return (SUCCESS);
}

int	builtin_cd(t_object *obj, t_command *command)
{
	t_string			path;

	if (isnull(command->argv[1]))
		path = get_env(obj->env, "HOME");
	else
		path = command->argv[1];
	if (isnull(path))
	{
		ft_error(B_CD, NULL, EMHNS);
		obj->exit_status = 1;
		return (FAILURE);
	}
	if (chdir(path) == -1)
	{
		ft_error(B_CD, path, NULL);
		obj->exit_status = 1;
		return (FAILURE);
	}
	if (update_oldpwd(obj) == FAILURE || update_pwd(obj) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
