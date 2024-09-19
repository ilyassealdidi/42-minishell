/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:09:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/19 09:15:40 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_run(t_list *cmds, t_command *cmd)
{
	struct stat		path_stat;

	if (cmd->argc == 0)
		exit (SUCCESS);
	if (ft_strchr(cmd->cmd, '/') && stat(cmd->cmd, &path_stat) == SUCCESS)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_error(NULL, cmd->cmd, EMISDIR);
			exit(126);
		}
	}
	if (execve(cmd->cmd, cmd->argv, cmd->envp) == FAILED)
	{
		if (cmd->cmd[0] == '.')
			ft_error(NULL, cmd->cmd, NULL);
		else if (ft_strchr(cmd->cmd, '/') == NULL)
			ft_error(NULL, cmd->cmd, EMCNF);
		else
			ft_error(NULL, cmd->cmd, NULL);
	}
	exit(127);
}

static int	ft_child(t_object *obj, t_list *cmds, t_command *cmd)
{
	signal(SIGINT, SIG_IGN);
	cmd->pid = ft_fork();
	if (cmd->pid == FAILED)
		return (FAILED);
	if (is_child(cmd->pid))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_pipe_out(cmds, cmd);
		if (has_redirection(cmd))
			ft_redirect(cmd);
		if (is_builtin(cmd->cmd))
			exit(execute_builtin(obj, cmds));
		else
			ft_run(cmds, cmd);
	}
	else if (is_parent(cmd->pid))
	{
		ft_pipe_in(cmds, cmd);
		ft_close_redirections(cmd);
	}
	return (SUCCESS);
}

static void	ft_exec_bin(t_object *obj)
{
	t_command		*cmd;
	t_list			*cmds;

	cmds = obj->commands;
	while (cmds)
	{
		cmd = cmds->content;
		if (has_next(cmds))
			ft_pipe(cmd->pfd);
		if (ft_child(obj, cmds, cmd) == FAILED)
		{
			ft_close(cmd->pfd[POUT]);
			break ;
		}
		cmds = cmds->next;
	}
	if (has_next(obj->commands))
		ft_close(cmd->pfd[PIN]);
	ft_wait(obj);
}

static void	exec_builtin(t_object *obj, t_list *cmds)
{
	t_command		*cmd;
	int				fd_out;

	cmd = cmds->content;
	if (has_redirection(cmd))
	{
		ft_save_fd(&fd_out, STDOUT_FILENO);
		ft_dup(cmd->out, STDOUT_FILENO, NOTHING);
	}
	obj->exit_status = execute_builtin(obj, cmds);
	if (has_redirection(cmd))
		ft_dup(fd_out, STDOUT_FILENO, NOTHING);
}

void	execute_commands(t_object *obj)
{
	t_list			*node;
	t_command		*cmd;
	int				fd_in;

	if (obj->commands == NULL)
		return ;
	node = obj->commands;
	cmd = node->content;
	if (cmd->in == FAILED || cmd->out == FAILED)
	{
		obj->exit_status = 1;
		return ;
	}
	if (has_next(node) || has_redirection(cmd))
		ft_save_fd(&fd_in, STDIN_FILENO);
	if (is_builtin(cmd->cmd) && !has_next(node))
		exec_builtin(obj, node);
	else
		ft_exec_bin(obj);
	if (has_next(node) || has_redirection(cmd))
		ft_dup(fd_in, STDIN_FILENO, NOTHING);
}
