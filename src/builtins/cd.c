/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:55:06 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/21 01:58:57 by ialdidi          ###   ########.fr       */
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

int	cd(t_object *obj, t_command *command)
{
	char	*path;

	if (command->args[1] == NULL)
		path = get_env(obj->env, "HOME");
	else
		path = command->args[1];
	if (path == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		obj->exit_status = 1;
		return (FAILURE);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		obj->exit_status = 1;
		return (FAILURE);
	}
	;
	if (update_oldpwd(obj) == FAILURE || update_pwd(obj) == FAILURE)
		return (obj->exit_status = 1, FAILURE);
	return (SUCCESS);
}
