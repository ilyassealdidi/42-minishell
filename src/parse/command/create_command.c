/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:07:10 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/25 12:45:05 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_args(t_list *tokens)
{
	t_token			*token;
	int				i;

	i = 0;
	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == PIPE)
			break ;
		if (token->type == ARG || token->type == CMD || token->type == BUILTIN)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

static int	set_args(t_list *tokens, t_command *command)
{
	t_token			*token;
	bool			is_cmd;
	int				i;

	command->argv = ft_calloc(command->argc + 1, sizeof(char *));
	if (isnull(command->argv))
		return (FAILURE);
	i = 1;
	while (tokens)
	{
		token = get_token(tokens);
		is_cmd = token->type == CMD || token->type == BUILTIN;
		if (token->type == ARG || is_cmd)
		{
			command->argv[i * !is_cmd] = ft_strdup(token->content);
			if (isnull(command->argv[i * !is_cmd]))
				return (free_array(command->argv), FAILURE);
			i += !is_cmd;
		}
		else if (token->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (SUCCESS);
}

static char	*dict_toenv(t_dictionnary *dict)
{
	t_string			key;
	t_string			env;

	key = ft_strjoin(dict->key, "=");
	if (isnull(key))
		return (NULL);
	env = ft_strjoin_free(key, dict->value, LEFT);
	if (isnull(env))
		return (free(key), NULL);
	return (env);
}

static int	set_envp(t_list *list, t_command *command)
{
	int				i;
	int				count;
	t_environment	*env;

	count = env_size(list);
	command->envp = ft_calloc(count + 1, sizeof(char *));
	if (isnull(command->envp))
		return (FAILURE);
	command->envp[count] = NULL;
	i = 0;
	while (list)
	{
		env = list->content;
		if (env->hidden == false && !isnull(env->element.value))
		{
			command->envp[i] = dict_toenv(&env->element);
			if (isnull(command->envp[i]))
				return (free_array(command->envp), FAILURE);
			i++;
		}
		list = list->next;
	}
	return (SUCCESS);
}

int	set_command(t_object *obj, t_list *tokens, t_command **command)
{
	t_token			*token;

	*command = ft_calloc(1, sizeof(t_command));
	if (isnull(*command))
		return (FAILURE);
	(*command)->out = STDOUT_FILENO;
	(*command)->argc = count_args(tokens);
	if ((*command)->argc > 0 && set_args(tokens, (*command)) == FAILURE)
		return (destroy_command((*command)), FAILURE);
	token = get_token(tokens);
	while (tokens && token->type != PIPE)
	{
		token = get_token(tokens);
		if (is_redir(token) && redir_init(tokens, (*command)) == FAILURE)
			break ;
		tokens = tokens->next;
	}
	if ((*command)->argc > 0 && set_envp(obj->env, (*command)) == FAILURE)
		return (destroy_command((*command)), FAILURE);
	return (SUCCESS);
}
