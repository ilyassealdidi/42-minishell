/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/13 15:57:58 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*Delete me*/
//ft_lstiter(obj->tokens, display_token);

// char	*get_command(t_list *tokens)
// {
// 	t_token	*token;
// 	char	*command;

// 	command = NULL;
// 	while (tokens)
// 	{
// 		token = (t_token *)tokens->content;
// 		if (token->type == PIPE)
// 			return (NULL);
// 		if (token->type == CMD || token->type == BUILTIN)
// 			return (token);
// 		tokens = tokens->next;
// 	}
// 	return (command);
// }

// char	**get_args(t_list **tokens)
// {
// 	t_token	*token;
// 	char	**args;
// 	int		count;
// 	int		i;

// 	count = count_args(*tokens);
// 	args = malloc(sizeof(char *) * (count + 1));
// 	if (args == NULL)
// 		return (NULL);
// 	args[count] = NULL;
// 	i = 0;
// 	while (1)
// 	{
// 		token = (t_token *)(*tokens)->content;
// 		if (token->type == PIPE || (*tokens)->next == NULL)
// 			break ;
// 		if (token->type == ARG)
// 		{
// 			args[i] = ft_strdup(token->content);
// 			if (args[i++] == NULL)
// 				return (free_array(args), NULL);
// 		}
// 		*tokens = (*tokens)->next;
// 	}
// 	return (args);
// }

// static int	commands_init(t_object *obj)
// {
// 	t_command	command;
// 	t_list		*tokens;
// 	t_token		*token;

// 	tokens = obj->tokens;
// 	while (1)
// 	{
// 		token = get_command(tokens);
// 		if (token != NULL)
// 		{
// 			command.cmd = ft_strdup(token->content);
// 			if (command.cmd == NULL)
// 				return (FAILURE);
// 		}
// 		command.args = get_args(&tokens);
// 		if (command.args == NULL)
// 			return (free(command.cmd), FAILURE);
// 		ft_lstadd_back(&obj->commands, ft_lstnew(&command));
// 	}
// 	return (SUCCESS);
// }

// int	write_line(int fd, char *line)
// {
// 	static int	tmp;

// 	if (tmp != fd)
// 	{
// 		if (tmp != 0)
// 			close(tmp);
// 		tmp = open(line, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 		if (tmp == -1)
// 		{
// 			perror(strerror(errno));
// 			return (FAILURE);
// 		}
// 	}
// 	ft_putendl_fd(line, tmp);
// 	return (SUCCESS);
// }

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


int	heredoc(t_object *obj, t_list *node)
{
	t_token	*token;
	char	*line;
	int		fd;
	int		writer;

	token = node->content;
	fd = open("heredoc", O_CREAT | O_RDONLY, 0644);
	unlink("heredoc");
	if (fd == -1)
	{
		perror(strerror(errno));
		return (FAILURE);
	}
	writer = open("heredoc", O_WRONLY, 0644);
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
		write_line(writer, line);
		free(line);
	}
	close(writer);
	return (SUCCESS);
}

void	redirections(t_object *obj)
{
	t_list	*tmp;
	t_token	*token;

	tmp = obj->tokens;
	while (tmp)
	{
		token = tmp->content;
		if (token->type == DELIMITER)
		{
			heredoc(obj, tmp);
		}
		// else if (token->type == REDIR_IN)
		// {
		// 	redir_in(obj, tmp);
		// }
		// else if (token->type == REDIR_OUT)
		// {
		// 	redir_out(obj, tmp);
		// }
		// else if (token->type == APPEND)
		// {
		// 	append_out(obj, tmp);
		
		// }
		tmp = tmp->next;
	}
}

int	generate_commands(t_object *obj)
{
	obj->exit_status = parse(obj);
	if (obj->exit_status != SUCCESS)
		return (FAILURE);
	redirections(obj);
	ft_lstiter(obj->tokens, display_token);
	return (SUCCESS);
}
