/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:09:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/08 04:42:51 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	ft_error(char *str, char *arg, int status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	// exit(status);
}

void	save_fd(int *fd)
{
	fd[PIN] = dup(STDIN_FILENO);
	fd[POUT] = dup(STDOUT_FILENO);
}

void	restore_fd(int *fd)
{
	ft_dupme(fd[PIN], STDIN_FILENO, NOTHING);
	ft_dupme(fd[POUT], STDOUT_FILENO, NOTHING);
}

void	ft_redirect(t_command *cmd)
{
	//2 means another file are opened
	//so we need to duplicate it to the std{in||out}
	if (cmd->in > 2)
		ft_dupme(cmd->in, STDIN_FILENO, NOTHING);
	if (cmd->out > 2)
		ft_dupme(cmd->out, STDOUT_FILENO, NOTHING);
}

void	ft_close_redirections(t_command *cmd)
{
	if (cmd->in > 2)
		ft_close(cmd->in);
	if (cmd->out > 2)
		ft_close(cmd->out);
}

static bool	has_next(t_list *node)
{
	return (node->next != NULL);
}

int	run_command(t_object *obj, t_list *cmds, t_command *cmd)
{
	if (execve(cmd->cmd, cmd->argv, cmd->envp) == FAILED)
		ft_error("command not found", cmd->argv[0], 126);
	exit(126);
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

int	create_child(t_object *obj, t_list *cmds, t_command *cmd)
{
	pid_t	pid;

	pid = ft_forkme(obj);
	if (pid == FAILED)
		return (FAILED);
	if (pid == 0)
	{
		//! should check if has redirection or pipe to do the right thing
		if (has_next(cmds))
			ft_dupme(obj->pipefd[POUT], STDOUT_FILENO, obj->pipefd[PIN]);
		ft_redirect(cmd);
		//!---------------------------------------------------------------------
		if (is_builtin(cmd->cmd))
			exit(execute_builtin(obj, cmds));
		else
			run_command(obj, cmds, cmd);
	}
	else
	{
		if (has_next(cmds))
			ft_dupme(obj->pipefd[PIN], STDIN_FILENO, obj->pipefd[POUT]);
		ft_close_redirections(cmd);
	}
	return (pid);
}

int execute_external(t_object *obj)
{
    t_command	*cmd;
    t_list		*cmds;
    pid_t		pid;

    cmds = obj->commands;
    while (cmds)
	{
        cmd = cmds->content;
        if (has_next(cmds))
			ft_pipeme(obj->pipefd);
		if (create_child(obj, cmds, cmd) == FAILED)
			break;
		cmds = cmds->next;
    }
	ft_close(PIN);
	while (wait(NULL) > 0)
		;
    return (SUCCESS);
}

int	execute_command(t_object *obj, t_list *node)
{
	t_command	*command;
	int			status;

	command = node->content;
	if (command->is_builtin)
		status = execute_builtin(obj, node);
	else
		status = execute_external(obj);
	return (status);
}

int	execute_commands(t_object *obj)
{
	t_list		*node;
	t_command	*cmd;

	if (obj->commands == NULL)
		return (SUCCESS);
	// if (has_next(obj->commands)) // we dont need to save fd if we have only one command
	save_fd(obj->saved_fds);
	node = obj->commands;
	cmd = node->content;
	if (is_builtin(cmd->cmd) && !has_next(node))
		execute_builtin(obj, obj->commands);
	else
		execute_external(obj);
	restore_fd(obj->saved_fds);
	return (SUCCESS);
}
