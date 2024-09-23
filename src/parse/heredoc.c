/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:17:19 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/23 12:37:50 by ialdidi          ###   ########.fr       */
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

static bool	contains_env(t_string str)
{
	t_string			ptr;

	if (*str == '\'')
		return (false);
	while (1)
	{
		ptr = ft_strchr(str + (*str == '"'), '$');
		if (isnull(ptr)
			|| (*str == '"' && ft_strchr(str + 1, '"') < ptr)
			|| (*str != '"' && str + ft_strcspn(str, " |><'\"\t$") < ptr))
			return (false);
		if (isset(ptr) && (*(ptr + 1) != '\0'))
			return (true);
		str = ptr + 1;
	}
}


static int	write_line(t_object *obj, t_token *token, int fd, t_string line)
{
	t_string		expanded;

	if (is_quoted(token))
		ft_dprintf(fd, "%s\n", line);
	else
	{
		if (expand_str(obj, &expanded, line) == FAILURE)
			return (FAILURE);
		ft_putendl_fd(expanded, fd);
		free(expanded);
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
