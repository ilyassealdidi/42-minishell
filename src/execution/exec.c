/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:09:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/24 18:12:52 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int execute_external(t_object *obj, t_list *node)
{
	t_command	*command;
	pid_t		pid;
	int			status;

	status = SUCCESS;
	command = node->content;
	pid = fork();
	if (pid == 0)
	{
		
		if (execve(command->cmd, command->argv, command->envp) == -1)
		{
			perror("minishell: execve");
			obj->exit_status = 127;
		}
	}
	else if (pid < 0)
	{
		ft_putendl_fd("minishell: fork: ", STDERR_FILENO);
		perror("fork");
	}
	else
		waitpid(pid, &obj->exit_status, 0);
	return (status);
}

int	execute_builtin(t_object *obj, t_list *node)
{
	t_command	*command;
	int			status;

	command = node->content;
	if (ft_strcmp(command->argv[0], "exit") == 0)
		status = builtin_exit(obj, command);
	else if (ft_strcmp(command->argv[0], "echo") == 0)
		status = builtin_echo(command);
	else if (ft_strcmp(command->argv[0], "export") == 0)
		status = builtin_export(obj, command);
	else if (ft_strcmp(command->argv[0], "cd") == 0)
		status = builtin_cd(obj, command);
	else if (ft_strcmp(command->argv[0], "pwd") == 0)
		status = builtin_pwd(obj);
	else if (ft_strcmp(command->argv[0], "env") == 0)
		status = builtin_env(obj);
	else
		status = builtin_unset(obj, command);
	return (status);
}

int	execute_command(t_object *obj, t_list *node)
{
	t_command	*command;
	int			status;

	command = node->content;
	if (command->argv[0] != NULL && command->is_builtin)
		status = execute_builtin(obj, node);
	else
		status = execute_external(obj, node);
	return (status);
}

int	execute_commands(t_object *obj)
{
	t_list	*commands;

	commands = obj->commands;
	int i = 0;
	while (commands)
	{
		if (i > 0)
		{
			dup2(obj->pipefd[0], STDIN_FILENO);
			close(obj->pipefd[0]);
		}
		if (commands->next != NULL)
		{
			if (pipe(obj->pipefd) == -1)
				return (FAILURE);
		}
		execute_command(obj, commands);
		if (commands->next != NULL)
			close(obj->pipefd[1]);
		commands = commands->next;
		i++;
	}
	return (SUCCESS);
}
