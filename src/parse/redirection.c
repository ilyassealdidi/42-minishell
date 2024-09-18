/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:14:37 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/18 19:54:57 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	close_fd(int fd, int default_fd)
{
	if (fd != default_fd)
		close(fd);
}

int	redir_init(t_list *node, t_command *command)
{
	t_token			*token;
	string			filename;

	token = get_token(node);
	filename = get_token(node->next)->content;
	if (token->type == REDIR_IN || token->type == HEREDOC)
	{
		close_fd(command->in, STDIN_FILENO);
		command->in = open(filename, O_RDONLY);
		if (token->type == HEREDOC)
			unlink(filename);
	}
	else
	{
		close_fd(command->out, STDOUT_FILENO);
		if (token->type == APPEND)
			command->out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			command->out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (filename == NULL)
		return (ft_error(NULL, NULL, EMAMBR), FAILURE);
	if (command->in == -1 || command->out == -1)
		return (ft_error(NULL, filename, NULL), FAILURE);
	return (SUCCESS);
}
