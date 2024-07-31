/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/31 11:14:36 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*Delete me*/
//ft_lstiter(obj->tokens, display_token);

// t_token	*get_command(t_list *tokens)
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

// static int	commands_init(t_object *obj)
// {
// 	t_command	command;

// 	while (1)
// 	{
// 		command.cmd = obj
// 	}
// 	return (SUCCESS);
// }

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
		return (print_error(SYNTAX_ERR), 258);
	if (status == FAILURE)
		return (print_error(MEMORY_ERR), 1);
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
