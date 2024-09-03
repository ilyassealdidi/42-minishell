/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:09:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/03 05:47:00 by aaitelka         ###   ########.fr       */
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
	if (ft_strcmp(command->argv[0], "exit") == SUCCESS)
		status = builtin_exit(obj, command);
	else if (ft_strcmp(command->argv[0], "echo") == SUCCESS)
		status = builtin_echo(command);
	else if (ft_strcmp(command->argv[0], "export") == SUCCESS)
		status = builtin_export(obj, command);
	else if (ft_strcmp(command->argv[0], "cd") == SUCCESS)
		status = builtin_cd(obj, command);
	else if (ft_strcmp(command->argv[0], "pwd") == SUCCESS)
		status = builtin_pwd(obj);
	else if (ft_strcmp(command->argv[0], "env") == SUCCESS)
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

bool is_herdoc(t_command *command)
{
	if (command->herdoc != -1)
		return (true);
	return (false);
}

int	execute_commands(t_object *obj)
{
	t_list	*commands;
	t_list	*node;
	pid_t	pid;
	int		fd;

	node = obj->commands;
	commands = obj->commands;
	int i = 0;
	t_command	*cmd;

	while (commands)
	{
		pid = fork();
		cmd = node->content;
		if (i > 0)
		{

			//print something useful
			printf("dup2 pfd[0] to stdin\n");
			dup2(obj->pfd[0], STDIN_FILENO);
			close(obj->pfd[0]);
		}
		if (commands->next != NULL)
		{
			printf("pipe\n");
			pipe(obj->pfd);
		}
		if (i == 0)
		{
			if (pid == 0)
			{
				printf("first command\n");
				if (is_herdoc(cmd))
					fd = cmd->herdoc;
				else
					fd = cmd->in;
				dup2(fd, STDIN_FILENO);
				close(fd);
				close(obj->pfd[0]);
				dup2(obj->pfd[1], STDOUT_FILENO);
				close(obj->pfd[1]);
				execve(cmd->cmd, cmd->argv, cmd->envp);
			}
		}
		else if (commands->next == NULL)
		{
			if (pid == 0)
			{
				printf("last command\n");
				close(obj->pfd[0]);
				dup2(obj->pfd[1], STDOUT_FILENO);
				close(obj->pfd[1]);
				execve(cmd->cmd, cmd->argv, cmd->envp);
			}
		}
		else
		{
			if (pid == 0)
			{
				printf("middle command\n");
				if (is_herdoc(cmd))
					fd = cmd->herdoc;
				else
					fd = cmd->out;
				dup2(fd, STDOUT_FILENO);
				close(fd);
				execve(cmd->cmd, cmd->argv, cmd->envp);
			}
		}
		if (commands->next != NULL)
			close(obj->pfd[1]);
		commands = commands->next;
		i++;
	}
	return (SUCCESS);
}
