/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:24:19 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/31 21:59:30 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_separator(t_token_type type)
{
	if (type == PIPE || type == REDIR_IN || type == REDIR_OUT || type == APPEND
		|| type == HEREDOC)
		return (1);
	return (0);
}

int	is_valid_syntax(t_list *tokens)
{
	t_token			*current;
	t_token			*next;

	if (tokens == NULL)
		return (SUCCESS);
	if (is_separator(get_last_token(tokens)->type)
		|| get_token(tokens)->type == PIPE
		|| (is_separator(get_token(tokens)->type) && tokens->next == NULL))
		return (ERROR);
	while (tokens->next)
	{
		current = tokens->content;
		next = tokens->next->content;
		if (is_separator(current->type) && is_separator(next->type))
			return (ERROR);
		tokens = tokens->next;
	}
	return (SUCCESS);
}
