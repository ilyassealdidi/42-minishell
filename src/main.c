/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/13 13:14:26 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int					g_received_signal = 0;

int	update_exit_status(t_object *obj)
{
	if (g_received_signal != obj->received_signals)
	{
		obj->exit_status = 1;
		obj->received_signals = g_received_signal;
	}
	if (set_exit_status(obj) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	f(){system("leaks minishell");}

int	main(int argc, char **argv, char **env)
{
	t_object		obj;

	if (argc != 1 || !isatty(STDIN_FILENO))
		return (ft_putstr_fd("Usage: ./minishell\n", 2), EXIT_FAILURE);
	obj = (t_object){0};
	init_signals();
	if (init_env(&obj.env, env) == FAILURE)
		return (ft_error(NULL, NULL, NULL), EXIT_FAILURE);
	while (true)
	{
		if (generate_commands(&obj) == FAILURE)
			continue ;
		execute_commands(&obj);
		ft_lstclear(&obj.commands, destroy_command);
	}
	return ((void)argv, EXIT_SUCCESS);
}
