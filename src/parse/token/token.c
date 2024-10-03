/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:46:33 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/28 20:34:57 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid_syntax(t_list *tokens)
{
	t_token			*current;
	t_token			*next;

	if (is_operator(get_last_token(tokens)) || get_token(tokens)->type == PIPE)
		return (ERROR);
	while (tokens->next)
	{
		current = tokens->content;
		next = tokens->next->content;
		if (is_operator(current) && is_operator(next))
			return (ERROR);
		tokens = tokens->next;
	}
	return (SUCCESS);
}

int	tokens_init(t_object *obj, t_string line)
{
	int				status;
	t_token			token;

	status = SUCCESS;
	while (*line != '\0')
	{
		status = set_token(&line, &token);
		if (status != SUCCESS)
			return (status);
		if (expand(obj, &token) == FAILURE
			|| ft_appendtoken(obj, &token) == FAILURE)
			return (free(token.content), FAILURE);
		while (*line != '\0' && (*line == ' ' || *line == '\t'))
			line++;
	}
	if (obj->tokens)
		status = is_valid_syntax(obj->tokens);
	return (status);
}
