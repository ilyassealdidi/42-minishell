/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/08 15:28:27 by ialdidi          ###   ########.fr       */
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

// h

static int	parse(t_object *obj)
{
	t_list	*list;
	int		status;
	char	*line;

	line = ft_strtrim(obj->line, " ");
	if (line == NULL)
		return (print_error(MEMORY_ERR), 1);
	status = tokens_init(obj, line);
	free(line);
	if (status == ERROR)
	{
		set_env(obj, ft_strdup("?"), ft_strdup("258"));
		return (print_error(SYNTAX_ERR), 258);
	}
	if (status == FAILURE)
	{
		set_env(obj, ft_strdup("?"), ft_strdup("1"));
		return (print_error(MEMORY_ERR), 1);
	}
	return (SUCCESS);
}

int	generate_commands(t_object *obj)
{
	obj->exit_status = parse(obj);
	if (obj->exit_status != SUCCESS)
		return (FAILURE);
	ft_lstiter(obj->tokens, display_token);
	return (SUCCESS);
}
