/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:19:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/10 22:57:18 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_pwd(t_object *obj)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_error(PWD, NULL, EMRCD);
		obj->exit_status = 1;
		return (FAILURE);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
