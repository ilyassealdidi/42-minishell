/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:17:19 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/22 09:20:33 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*generate_filename(void)
{
	static int		i;
	t_string		number;
	t_string		name;

	number = ft_itoa(i);
	if (isnull(number))
		return (i = 0, NULL);
	name = ft_strjoin("/tmp/heredoc_", number);
	free(number);
	if (isnull(name))
		return (i = 0, NULL);
	i++;
	return (name);
}

static int	write_line(t_object *obj, t_token *token, int fd, t_string line)
{
	if (is_quoted(token))
	{
		ft_dprintf(fd, "%s\n", line);
	}
	else
	{
		if (contains_env(line) && expand_str(obj, &line) == FAILURE)
			return (FAILURE);
		else
		{
			line = ft_strdup(line);
			if (isnull(line))
				return (FAILURE);
		}
		if (line != NULL)
			ft_dprintf(fd, "%s", line);
		ft_dprintf(fd, "\n");
		free(line);
	}
	return (SUCCESS);
}

static int	open_heredoc(t_object *obj, t_token *token, t_string filename)
{
	int				fd;
	t_string		line;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(EMBASE), FAILURE);
	while (1)
	{
		line = readline("> ");
		if (isnull(line) || ft_strcmp(line, token->content) == 0)
		{
			free(line);
			if (g_received_signal != obj->received_signals)
				return (close(fd), FAILURE);
			break ;
		}
		if (write_line(obj, token, fd, line) == FAILURE)
			return (perror(EMBASE), free(line), close(fd), FAILURE);
		free(line);
	}
	close(fd);
	return (SUCCESS);
}

static int	open_heredocs(t_object *obj)
{
	t_list			*tmp;
	t_token			*token;
	t_string		filename;

	tmp = obj->tokens;
	while (tmp)
	{
		token = tmp->content;
		if (token->type == DELIMITER)
		{
			filename = generate_filename();
			if (isnull(filename))
				return (perror(EMBASE), FAILURE);
			if (open_heredoc(obj, tmp->content, filename) == FAILURE)
				return (free(filename), FAILURE);
			free(token->content);
			token->content = filename;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	heredocs_init(t_object *obj)
{
	int				stdin_fd;
	int				status;

	stdin_fd = dup(STDIN_FILENO);
	if (stdin_fd == -1)
		return (perror(EMBASE), FAILURE);
	signal(SIGINT, heredoc_interrupt_handler);
	status = open_heredocs(obj);
	init_signals();
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
		return (perror(EMBASE), close(stdin_fd), FAILURE);
	close(stdin_fd);
	return (status);
}
