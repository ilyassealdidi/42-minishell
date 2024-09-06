/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:09:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/06 02:04:49 by aaitelka         ###   ########.fr       */
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
	fd[STDIN] = dup(STDIN_FILENO);
	fd[STDOUT] = dup(STDOUT_FILENO);
}

void	restore_fd(int *fd)
{
	dup2(fd[STDIN], STDIN_FILENO);
	close(fd[STDIN]);
	dup2(fd[STDOUT], STDOUT_FILENO);
	close(fd[STDOUT]);
}

void	ft_redirect(t_command *cmd)
{
	//2 means another file are opened
	//so we need to duplicate it to the std{in||out}
	if (cmd->in > 2)
	{
		if (dup2(cmd->in, STDIN_FILENO) == FAILED)
			perror("dup2");
		if (close(cmd->in) == FAILED)
			perror("close");
	}
	if (cmd->out > 2)
	{
		if (dup2(cmd->out, STDOUT_FILENO) == FAILED)
			perror("dup2");
		if (close(cmd->out) == FAILED)
			perror("close");
	}
}

int	run_command(t_object *obj, t_command *cmd)
{
	ft_redirect(cmd);
	if (execve(cmd->cmd, cmd->argv, cmd->envp) == FAILED)
		ft_error("command not found", cmd->argv[0], 126);
	exit(126);
	return (SUCCESS);
}


bool	has_next(t_list *node)
{
	return (node->next != NULL);
}

int execute_external(t_object *obj)
{
    t_command *cmd;
    t_list *cmds;
    pid_t pid;
    int index = 0;

	init_signals();
    cmds = obj->commands;
    while (cmds)
	{
        cmd = cmds->content;
        if (has_next(cmds)) {
            if (pipe(obj->pipefd) == FAILED) {
                perror("minishell: pipe");
                return (FAILURE);
            }
        }

        if ((pid = fork()) == FAILED) {
            perror("minishell: fork");
            return (FAILURE);
        }

        if (pid == 0)
		{
            if (has_next(cmds)) {
                if (dup2(obj->pipefd[1], STDOUT_FILENO) == FAILED) {
                    perror("minishell: dup2");
                    exit(FAILURE);
                }
                close(obj->pipefd[0]);
            }
            ft_redirect(cmd);
			if (execve(cmd->cmd, cmd->argv, cmd->envp) == FAILED)
				ft_error("command not found", cmd->argv[0], 126);
			exit(126);
        }
		else 
		{
			if (cmd->in > 2)
				close(cmd->in);
			if (cmd->out > 2)
				close(cmd->out);
            if (has_next(cmds)) {
                close(obj->pipefd[1]);
                if (dup2(obj->pipefd[0], STDIN_FILENO) == FAILED) {
                    perror("minishell: dup2");
                    return (FAILURE);
                }
                close(obj->pipefd[0]);
            }
            waitpid(pid, &obj->exit_status, 0);
            if (WIFEXITED(obj->exit_status) && WEXITSTATUS(obj->exit_status) != SUCCESS) {
                return (FAILURE);
            }
            index++;
            cmds = cmds->next;
        }
    }
    return (SUCCESS);
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
	if (has_next(obj->commands)) // we dont need to save fd if we have only one command
		save_fd(obj->saved_fds);
	node = obj->commands;
	cmd = node->content;
	if (is_builtin(cmd->cmd))
		execute_builtin(obj, obj->commands);
	else
		execute_external(obj);
	if (has_next(obj->commands))
		restore_fd(obj->saved_fds);
	return (SUCCESS);
}
