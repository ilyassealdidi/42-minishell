/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:47:33 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/10 22:54:39 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_echo(t_command *cmd)
{
	int				i;
	bool			nl;

	i = 1;
	nl = false;
	while (cmd->argv[i] != NULL && ft_strncmp(cmd->argv[i], "-n", 2) == 0)
	{
		if (ft_strspn(&cmd->argv[i][1], "n") == ft_strlen(cmd->argv[i]) - 1)
			nl = true;
		else
			break ;
		i++;
	}
	while (cmd->argv[i] != NULL)
	{
		ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		if (cmd->argv[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (nl == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
