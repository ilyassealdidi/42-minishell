/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:07:10 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/24 16:25:04 by ialdidi          ###   ########.fr       */
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

static int	set_args(t_list *tokens, t_command *command)
{
	t_token	*token;
	bool	is_cmd;
	int		i;

	command->args = malloc(sizeof(char *) * (command->args_count + 1));
	if (command->args == NULL)
		return (FAILURE);
	command->args[command->args_count] = NULL;
	i = 1;
	while (tokens)
	{
		token = get_token(tokens);
		is_cmd = token->type == CMD || token->type == BUILTIN;
		if (token->type == ARG || is_cmd)
		{
			command->args[i * !is_cmd] = ft_strdup(token->content);
			if (command->args[i * !is_cmd] == NULL)
				return (free_array(command->args), FAILURE);
			i += !is_cmd;
		}
		else if (token->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (SUCCESS);
}

static int	redir_init(t_list *node, t_command *command)
{
	int		fd;
	t_token *token;

	token = get_token(node);
	if (token->type == REDIR_IN)
	{
		if (command->in != 0)
			close(command->in);
		fd = open(get_token(node->next)->content, O_RDONLY);
		command->in = fd;
	}
	if (token->type == APPEND || token->type == REDIR_OUT)
	{
		if (command->out != 1)
			close(command->out);
		if (token->type == APPEND)
			fd = open(get_token(node->next)->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(get_token(node->next)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		command->out = fd;
	}
	if (fd == -1)
		return (print_error(errno, NULL), FAILURE); //! Check if it's the right way to handle the error
	return (SUCCESS);
}

int	new_command(t_list *tokens, t_command *command)
{
	t_token		*token;

	command->out = STDOUT_FILENO;
	command->args_count = count_args(tokens);
	if (command->args_count > 0)
	{
		if (set_args(tokens, command) == FAILURE)
			return (FAILURE);
		command->cmd = command->args[0];
		command->is_builtin = is_builtin(command->cmd);
	}
	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == APPEND)
		{
			if (redir_init(tokens, command) == FAILURE)
				return (FAILURE); // Check if it's the right way to handle the error
		}
		else if (token->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (SUCCESS);
}
