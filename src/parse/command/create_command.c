/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:07:10 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/14 16:00:36 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_args(t_list *tokens)
{
	t_token	*token;
	int		i;

	i = 1;
	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == PIPE)
			break ;
		if (token->type == ARG)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

static char	**get_args(t_list *tokens)
{
	t_token	*token;
	char	**args;
	bool	is_cmd;
	int		i;

	i = count_args(tokens);
	args = malloc(sizeof(char *) * (i + 1));
	if (args == NULL)
		return (NULL);
	args[i] = NULL;
	i = 1;
	while (tokens)
	{
		token = get_token(tokens);
		is_cmd = token->type == CMD || token->type == BUILTIN;
		if (token->type == ARG || is_cmd)
		{
			args[i * !is_cmd] = ft_strdup(token->content);
			if (args[i * !is_cmd] == NULL)
				return (free_array(args), NULL);
			i++;
		}
		else if (token->type == PIPE)
			break ;
		tokens = (tokens)->next;
	}
	return (args);
}

static int	redir_init(t_token *token, t_command *command)
{
	int		fd;

	if (token->type == REDIR_IN)
	{
		if (command->in != 0)
			close(command->in);
		fd = open(token->content, O_RDONLY);
		command->in = fd;
	}
	if (token->type == APPEND || token->type == REDIR_OUT)
	{
		if (command->out != 1)
			close(command->out);
		if (token->type == APPEND)
			fd = open(token->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(token->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		command->out = fd;
	}
	if (fd == -1)
		return (print_error(errno), FAILURE);
	return (SUCCESS);
}

int	new_command(t_list *tokens, t_command *command)
{
	t_token		*token;

	command->out = 1;
	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == CMD || token->type == ARG || token->type == BUILTIN)
		{
			command->args = get_args(tokens);
			if (command->args == NULL)
				return (FAILURE);
			command->cmd = command->args[0];
		}
		else if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == APPEND)
		{
			if (redir_init(tokens->next->content, command) == FAILURE)
				return (FAILURE); // Check if it's the right way to handle the error
		}
		else if (token->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (SUCCESS);
}
