/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/11 00:58:25 by ialdidi          ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_object		obj;

	if (argc != 1)
		return (ft_error(NULL, NULL, "Usage: ./minishell\n"), EXIT_FAILURE);
	ft_memset(&obj, 0, sizeof(t_object));
	init_signals();
	if (init_env(&obj.env, env) == FAILURE)
		return (ft_error(NULL, NULL, NULL), EXIT_FAILURE);
	while (1)
	{
		if (generate_commands(&obj) == FAILURE)
			continue ;
		// if (execute_commands(&obj) == FAILURE)
		// {
		// 	ft_lstclear(&obj.commands, destroy_command);
		// 	continue ;
		// } // Think to set the exit status to 0
		ft_lstclear(&obj.commands, destroy_command);
	}
	return ((void)argv, EXIT_SUCCESS);
}
