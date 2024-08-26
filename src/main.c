/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/25 00:26:17 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_received_signal = 0;

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

int	main(int argc, char **argv, char **env)
{
	t_object			obj;
	int					ret;

	if (argc != 1)
		return (ft_putstr_fd("Usage: ./minishell\n", 2), EXIT_FAILURE);
	ft_memset(&obj, 0, sizeof(t_object));
	init_signals();
	if (init_env(&obj.env, env) == FAILURE)
		return (print_error(FAILURE, NULL), EXIT_FAILURE);
	while (1)
	{
		// obj.debug_line = "ls";
		if (generate_commands(&obj) != SUCCESS)
			continue ;
		if (execute_commands(&obj) == FAILURE)
		{
			ft_lstclear(&obj.commands, destroy_command);
			continue ;
		}
		ft_lstclear(&obj.commands, destroy_command);
	}
	return (EXIT_SUCCESS);
}
