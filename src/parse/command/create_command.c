/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:07:10 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/29 11:11:02 by ialdidi          ###   ########.fr       */
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

	command->argv = ft_calloc(command->argc + 1, sizeof(char *));
	if (command->argv == NULL)
		return (FAILURE);
	command->argv[command->argc] = NULL;
	i = 1;
	while (tokens)
	{
		token = get_token(tokens);
		is_cmd = token->type == CMD || token->type == BUILTIN;
		if (token->type == ARG || is_cmd)
		{
			command->argv[i * !is_cmd] = ft_strdup(token->content);
			if (command->argv[i * !is_cmd] == NULL)
				return (free_array(command->argv), FAILURE);
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

static char	*dict_toenv(t_dictionnary *dict)
{
	char	*key;
	char	*env;

	key = ft_strjoin(dict->key, "=");
	if (key == NULL)
		return (NULL);
	env = ft_strjoin_free(key, dict->value, LEFT);
	if (env == NULL)
		return (free(key), NULL);
	return (env);
}

static int	set_envp(t_list *list, t_command *command)
{
	int				i;
	int				count;
	t_environment	*env;

	count = ft_lstsize(list);
	command->envp = ft_calloc(count + 1, sizeof(char *));
	if (command->envp == NULL)
		return (FAILURE);
	command->envp[count] = NULL;
	i = 0;
	while (list)
	{
		env = list->content;
		if (env->hidden == false)
		{
			command->envp[i] = dict_toenv(&env->element);
			if (command->envp[i] == NULL)
				return (free_array(command->envp), FAILURE);
			i++;
		}
		list = list->next;
	}
	return (SUCCESS);
}

t_command	*new_command(t_object *obj, t_list *tokens)
{
	t_command	*command;
	t_token		*token;

	command = ft_calloc(1, sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->out = STDOUT_FILENO;
	command->argc = count_args(tokens);
	if (command->argc > 0)
	{
		if (set_args(tokens, command) == FAILURE)
			return (destroy_command(command), NULL);
		command->is_builtin = is_builtin(command->argv[0]);
	}
	while (tokens && token->type != PIPE)
	{
		token = get_token(tokens);
		if ((token->type == REDIR_IN || token->type == REDIR_OUT || token->type == APPEND)
			&& redir_init(tokens, command) == FAILURE)
				return (destroy_command(command), NULL); // Check if it's the right way to handle the error
		tokens = tokens->next;
	}
	if (set_envp(obj->env, command) == FAILURE)
		return (destroy_command(command), NULL);
	return (command);
}
