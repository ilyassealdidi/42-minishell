/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:09:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/13 12:45:40 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_run(t_list *cmds, t_command *cmd)
{
	if (execve(cmd->cmd, cmd->argv, cmd->envp) == FAILED)
	{
		if (cmd->cmd[0] == '.')
			ft_error(NULL, cmd->cmd, NULL);
		else
			ft_error(NULL, cmd->cmd, EMCNF);
	}
	exit(127);
}

static int	ft_child(t_object *obj, t_list *cmds, t_command *cmd)
{
	pid_t			pid;
	int				status;

	pid = ft_fork(cmd);
	if (pid == FAILED)
		return (FAILED);
	if (is_child(pid))
	{
		ft_pipe_out(cmds, cmd);
		if (has_redirection(cmd))
			ft_redirect(cmd);
		if (is_builtin(cmd->cmd))
			exit(execute_builtin(obj, cmds));
		else
			ft_run(cmds, cmd);
	}
	else if (is_parent(pid))
	{
		ft_pipe_in(cmds, cmd);
		ft_close_redirections(cmd);
	}
	return (pid);
}

static int	ft_exec_bin(t_object *obj)
{
	t_command		*cmd;
	t_list			*cmds;
	pid_t			pid;

	cmds = obj->commands;
	while (cmds)
	{
		cmd = cmds->content;
		if (has_next(cmds))
			ft_pipe(cmd->pipefd);
		if (ft_child(obj, cmds, cmd) == FAILED)
		{
			ft_close(cmd->pipefd[POUT]);	
			break ;
		}
		cmds = cmds->next;
	}
	if (has_next(obj->commands))
		ft_close(cmd->pipefd[PIN]);
	ft_wait(&obj->exit_status);
	return (SUCCESS);
}

static int	exec_builtin(t_object *obj, t_list *cmds)
{
	t_command		*cmd;
	int				status;
	int				fd_out;

	cmd = cmds->content;
	if (has_redirection(cmd))
	{
		ft_save_fd(&fd_out, STDOUT_FILENO);
		ft_dup(cmd->out, STDOUT_FILENO, NOTHING);
	}
	status = execute_builtin(obj, cmds);
	if (has_redirection(cmd))
		ft_dup(fd_out, STDOUT_FILENO, NOTHING);
	return (status);
}

int	execute_commands(t_object *obj)
{
	t_list			*node;
	t_command		*cmd;
	int				status;
	int				fd_in;

	if (obj->commands == NULL)
		return (SUCCESS);
	node = obj->commands;
	cmd = node->content;
	if (!cmd->cmd)
		return (SUCCESS);
	if (has_next(node) || has_redirection(cmd))
		ft_save_fd(&fd_in, STDIN_FILENO);
	if (is_builtin(cmd->cmd) && !has_next(node))
		status = exec_builtin(obj, node);
	else
		status = ft_exec_bin(obj);
	if (has_next(node) || has_redirection(cmd))
		ft_dup(fd_in, STDIN_FILENO, NOTHING);
	return (status);
}
