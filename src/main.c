/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/16 20:39:57 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_received_signal = 0;

void	update_exit_status(t_object *obj)
{
	if (g_received_signal != obj->received_signals)
	{
		obj->exit_status = 1;
		set_env(obj, "?", "1");
		obj->received_signals = g_received_signal;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_object			obj;
	int					status;
	// if (argc != 1)
	// 	return (ft_printf("Usage: ./minishell\n"), 1);
	ft_memset(&obj, 0, sizeof(t_object));
	init_signals();
	if (init_env(&obj, env) == FAILURE)
		return (ft_printf("Error: failed to initialize environment\n"), 1);
	// ft_lstiter(obj.env, print_env);
	while (1)
	{
		if (argv[1])
			obj.line = ft_strdup("echo Hello");
		else
			obj.line = readline("$> ");
		if (!obj.line)
			exit_shell(&obj);
		if (obj.line[0] != '\0')
			add_history(obj.line);
		update_exit_status(&obj);
		status = generate_commands(&obj);
		free(obj.line);
		ft_lstclear(&obj.commands, destroy_command);
		if (status != SUCCESS)
			continue ;
		//exec(&obj);
	}
	return ((void)argc, 0);
}
