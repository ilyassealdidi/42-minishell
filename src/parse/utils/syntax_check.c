/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:24:19 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/09 19:57:27 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_separator(t_token_type type)
{
	return (type == PIPE || type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

int	is_valid_syntax(t_list *tokens)
{
	t_token			*current;
	t_token			*next;

	if (is_separator(get_last_token(tokens)->type)
		|| get_token(tokens)->type == PIPE)
		return (ERROR);
	while (tokens->next)
	{
		current = tokens->content;
		next = tokens->next->content;
		if (current->type == PIPE && next->type != PIPE)
		{
			tokens = tokens->next;
			continue ;
		}
		if (is_separator(current->type) && is_separator(next->type))
			return (ERROR);
		tokens = tokens->next;
	}
	return (SUCCESS);
}
