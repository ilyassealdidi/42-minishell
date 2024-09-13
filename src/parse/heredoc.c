/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:17:19 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/11 00:18:17 by ialdidi          ###   ########.fr       */
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

static int	heredoc(t_object *obj, t_list *node)
{
	t_token			*token;
	int				fd;
	char			*line;
	char			*filename;

	token = node->content;
	filename = generate_filename();
	if (filename == NULL)
		return (FAILURE);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(filename);
		perror(strerror(errno));
		return (FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL && g_received_signal != obj->received_signals)
		{
			update_exit_status(obj);
			free(line);
			break ;
		}
		if (line == NULL || ft_strcmp(line, token->content) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	free(token->content);
	token->content = filename;
	token->type = INFILE;
	((t_token *)(node->previous->content))->type = REDIR_IN;
	return (SUCCESS);
}

int	heredocs_init(t_object *obj)
{
	t_list			*tmp;
	t_token			*token;

	tmp = obj->tokens;
	while (tmp)
	{
		token = tmp->content;
		if (token->type == DELIMITER)
			heredoc(obj, tmp);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
