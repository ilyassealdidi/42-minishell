/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:19:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/23 13:58:27 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_pwd(t_object *obj)
{
	t_string			pwd;

	pwd = get_env_value(obj->env, "@PWD");
	if (isnull(pwd))
	{
		pwd = getcwd(NULL, 0);
		if (isnull(pwd))
			return (ft_error(B_PWD, NULL, EMRCD), FAILURE);
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("%s\n", pwd);
	return (SUCCESS);
}
