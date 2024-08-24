/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:47:33 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/24 16:36:40 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_echo(t_command *cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	while (cmd->argv[i] != NULL && cmd->argv[i][0] == '-')
	{
		if (ft_strspn(&cmd->argv[i][1], "n") == ft_strlen(cmd->argv[i]) - 1)
 			nl = 1;
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
	if (nl == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
}
