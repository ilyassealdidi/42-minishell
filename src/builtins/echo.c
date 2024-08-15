/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:47:33 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/29 00:21:22 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	echo(t_cmd *cmd)
// {
// 	int	i;
// 	int	n;

// 	i = 1;
// 	n = 0;
// 	while (cmd->args[i] && cmd->args[i][0] == '-')
// 	{
// 		if (ft_strspn(&cmd->args[i][1], "n") == ft_strlen(cmd->args[i]) - 1)
// 			n = 1;
// 		else
// 		{
// 			ft_printf("%s", cmd->args[i++]);
// 			write(1, " ", 1);
// 			break ;
// 		}
// 		i++;
// 	}
// 	while (cmd->args[i])
// 	{
// 		ft_putstr_fd(cmd->args[i], 1);
// 		if (cmd->args[i + 1])
// 			write(1, " ", 1);
// 		i++;
// 	}
// 	if (n == 0)
// 		write(1, "\n", 1);
// }
