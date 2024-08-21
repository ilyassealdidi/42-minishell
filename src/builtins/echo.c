/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:47:33 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/21 22:41:52 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_echo(t_command *cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	while (cmd->args[i] != NULL && cmd->args[i][0] == '-')
	{
		if (ft_strspn(&cmd->args[i][1], "n") == ft_strlen(cmd->args[i]) - 1)
 			nl = 1;
		else
			break ;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (nl == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
}
