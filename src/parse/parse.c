/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/14 11:39:55 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	parse(t_object *obj)
{
	t_list	*list;
	int		status;
	char	*line;

	line = ft_strtrim(obj->line, " \t");
	if (line == NULL)
		return (print_error(FAILURE), 1);
	status = tokens_init(obj, line);
	free(line);
	set_env(obj, ft_strdup("?"), ft_itoa(status));
	if (status != SUCCESS)
		print_error(status);
	return (status);
}

char	*generate_filename(void)
{
	static int	i;
	char		*number;
	char		*name;

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

int	heredoc(t_object *obj, t_list *node)
{
	t_token	*token;
	int		fd;
	char	*line;
	char	*filename;

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
		// if (line == NULL && g_received_signal != obj->received_signals)
		// {
		// 	update_exit_status(obj);
		// 	free(line);
		// 	break ;
		// }
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

int	open_heredocs(t_object *obj)
{
	t_list	*tmp;
	t_token	*token;

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

int	generate_commands(t_object *obj)
{
	obj->exit_status = parse(obj);
	if (obj->exit_status != SUCCESS)
		return (FAILURE);
	if (open_heredocs(obj) == FAILURE)
		return (FAILURE);
	// if (commands_init(obj) == FAILURE)
	// 	return (FAILURE);
	ft_lstiter(obj->tokens, display_token);
	return (SUCCESS);
}
