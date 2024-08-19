/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/19 11:01:12 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_received_signal = 0;

int	update_exit_status(t_object *obj)
{
	if (g_received_signal != obj->received_signals)
	{
		obj->received_signals = g_received_signal;
		obj->exit_status = 1;
		if (set_exit_status(obj) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_object			obj;

	if (argc != 1)
		return (printf("Usage: ./minishell\n"), 1);
	ft_memset(&obj, 0, sizeof(t_object));
	init_signals();
	if (init_env(&obj.env, env) == FAILURE)
		return (print_error(FAILURE), 1);
	while (1)
	{
		if (generate_commands(&obj) != SUCCESS)
			continue ;
	}
	return ((void)argc, 0);
}
