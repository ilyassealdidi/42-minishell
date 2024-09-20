/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:19:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/20 18:54:51 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_pwd(t_object *obj)
{
	t_string			pwd;

	pwd = getcwd(NULL, 0);
	if (isnull(pwd))
	{
		ft_error(B_PWD, NULL, EMRCD);
		obj->exit_status = 1;
		return (FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
