/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/21 22:53:58 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_received_signal = 0;

int	builtin(t_object *obj, t_list *node)
{
	t_command	*command;
	int			status;

	command = node->content;
	if (ft_strcmp(command->args[0], "exit") == 0)
		status = builtin_exit(obj, command);
	else if (ft_strcmp(command->args[0], "echo") == 0)
		status = builtin_echo(command);
	else if (ft_strcmp(command->args[0], "export") == 0)
		status = builtin_export(obj, command);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		status = builtin_cd(obj, command);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		status = builtin_pwd(obj);
	else if (ft_strcmp(command->args[0], "env") == 0)
		status = builtin_env(obj);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		status = builtin_unset(obj, command);
	// else
	// 	status = execute_command(obj, node);
	return (status);
}

int	execute_command(t_object *obj, t_list *node)
{
	t_command	*command;
	int			status;

	command = node->content;
	if (command->args[0] != NULL && is_builtin(command->args[0]))
		status = builtin(obj, node);
	return (status);
}

int	execute_commands(t_object *obj)
{
	t_list	*commands;

	commands = obj->commands;
	while (commands)
	{
		if (execute_command(obj, commands) == FAILURE)
			return (FAILURE);
		commands = commands->next;
	}
	return (SUCCESS);
}

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
		// obj.debug_line = "export name=Ilyasse Aldidi";
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
