/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:55:06 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/23 14:12:16 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	update_oldpwd(t_object *obj)
{
	t_dictionnary	dict;
	int				status;

	status = SUCCESS;
	dict.key = "@OLDPWD";
	dict.value = get_env_value(obj->env, "@PWD");
	status = set_env(&obj->env, dict);
	if (status == SUCCESS && isset(get_env(obj->env, "OLDPWD")))
	{
		dict.key = "OLDPWD";
		status = set_env(&obj->env, dict);
	}
	return (status);
}


/*
➜ echo $PWD
/Users/ialdidi/master/5
➜ echo $OLDPWD
/Users/ialdidi/master/5/6/7/8/../..

*/
int	update_pwd(t_object *obj, char *arg)
{
	t_dictionnary	dict;
	int				status;

	status = SUCCESS;
	dict.key = "@PWD";
	dict.value = getcwd(NULL, 0);
	if (isnull(dict.value))
	{
		dict.value = ft_strjoin(get_env_value(obj->env, "@PWD"), "/");
		dict.value = ft_strjoin(dict.value, arg);
		if (isnull(dict.value))
			return (FAILURE);
		ft_error(B_CD, "error retrieving current directory: getcwd", NULL);
	}
	status = set_env(&obj->env, (t_dictionnary){"@PWD", dict.value});
	if (status == SUCCESS && isset(get_env(obj->env, "PWD")))
	{
		dict.key = "PWD";
		status = set_env(&obj->env, dict);
	}
	free(dict.value);
	return (status);
}

int	builtin_cd(t_object *obj, t_command *command)
{
	t_string			path;

	if (isnull(command->argv[1]))
		path = get_env_value(obj->env, "HOME");
	else
		path = command->argv[1];
	if (isnull(path))
	{
		ft_error(B_CD, NULL, EMHNS);
		return (FAILURE);
	}
	if (chdir(path) == -1)
	{
		ft_error(B_CD, path, NULL);
		return (FAILURE);
	}
	if (update_oldpwd(obj) == FAILURE
		|| update_pwd(obj, command->argv[1]) == FAILURE)
		return (perror(EMBASE), FAILURE);
	return (SUCCESS);
}
