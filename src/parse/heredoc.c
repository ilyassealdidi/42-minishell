/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:17:19 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/16 23:57:05 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*generate_filename(void)
{
	static int		i;
	char			*number;
	char			*name;

	number = ft_itoa(i);
	if (number == NULL)
		return (i = 0, NULL);
	name = ft_strjoin("/tmp/heredoc_", number);
	free(number);
	if (name == NULL)
		return (i = 0, NULL);
	i++;
	return (name);
}

void	heredoc_signal_handler(int signum)
{
	g_received_signal++;
	close(0);
}

int	write_line(t_object *obj, t_token *token, int fd, char *line)
{
	if (is_quoted(token))
	{
		ft_dprintf(fd, "%s\n", line);
	}
	else
	{
		if (expand_str(obj, &line) == FAILURE)
			return (FAILURE);
		if (line != NULL)	
			ft_dprintf(fd, "%s", line);
		ft_dprintf(fd, "\n");
		free(line);
	}
	return (SUCCESS);
}

static int	heredoc(t_object *obj, t_token *token, char *filename)
{
	int				fd;
	char			*line;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (FAILURE);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, token->content) == 0)
		{
			free(line);
			if (g_received_signal != obj->received_signals)
				return (close(fd), FAILURE);
			break ;
		}
		if (write_line(obj, token, fd, line) == FAILURE)
			return (free(line), close(fd), FAILURE);
		free(line);
	}
	close(fd);
	return (SUCCESS);
}

int	heredocs_init(t_object *obj)
{
	t_list			*tmp;
	t_token			*token;
	char			*filename;
	int				f;

	tmp = obj->tokens;
	f = dup(0);
	signal(SIGINT, heredoc_signal_handler);
	while (tmp)
	{
		token = tmp->content;
		if (token->type == DELIMITER)
		{
			filename = generate_filename();
			if (filename == NULL)
				return (FAILURE);
			if (heredoc(obj, tmp->content, filename) == FAILURE)
				return (init_signals(), dup2(f, 0), FAILURE); //! print error
			free(token->content);
			token->content = filename;
		}
		tmp = tmp->next;
	}
	init_signals();
	dup2(f, 0);
	return (SUCCESS);
}
