/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:07:10 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/19 13:06:09 by ialdidi          ###   ########.fr       */
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

static char	**get_args(t_list *tokens, int num_args)
{
	t_token	*token;
	char	**args;
	bool	is_cmd;

	args = malloc(sizeof(char *) * (num_args + 1));
	if (args == NULL)
		return (NULL);
	args[num_args] = NULL;
	num_args = 1;
	while (tokens)
	{
		token = get_token(tokens);
		is_cmd = token->type == CMD || token->type == BUILTIN;
		if (token->type == ARG || is_cmd)
		{
			args[num_args * !is_cmd] = ft_strdup(token->content);
			if (args[num_args * !is_cmd] == NULL)
				return (free_array(args), NULL);
			num_args += !is_cmd;
		}
		else if (token->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (args);
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
	int			number_args;

	number_args = count_args(tokens);
	if (number_args > 0)
	{
		command->args = get_args(tokens, number_args);
		if (command->args == NULL)
			return (FAILURE);
		command->cmd = command->args[0];
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
