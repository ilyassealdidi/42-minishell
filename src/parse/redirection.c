/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:14:37 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/20 18:58:11 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	open_fd(t_string filename, t_token_type type)
{
	if (type == REDIR_IN || type == HEREDOC)
		return (open(filename, O_RDONLY));
	else if (type == APPEND)
		return (open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

static void	close_fd(int fd, int default_fd)
{
	if (fd != default_fd)
		close(fd);
}

int	redir_init(t_list *node, t_command *command)
{
	t_token			*token;
	t_string		filename;

	token = get_token(node);
	filename = get_token(node->next)->content;
	if (token->type == REDIR_IN || token->type == HEREDOC)
	{
		close_fd(command->in, STDIN_FILENO);
		command->in = open_fd(filename, token->type);
		if (token->type == HEREDOC)
			unlink(filename);
	}
	else
	{
		close_fd(command->out, STDOUT_FILENO);
		command->out = open_fd(filename, token->type);
	}
	if (isnull(filename))
		return (ft_error(NULL, NULL, EMAMBR), FAILURE);
	if (command->in == -1 || command->out == -1)
		return (ft_error(NULL, filename, NULL), FAILURE);
	return (SUCCESS);
}
