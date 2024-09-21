/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:24:19 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/21 16:28:54 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid_syntax(t_list *tokens)
{
	t_token			*current;
	t_token			*next;

	if (is_operator(get_last_token(tokens)) || get_token(tokens)->type == PIPE)
		return (ERROR);
	while (tokens->next)
	{
		current = tokens->content;
		next = tokens->next->content;
		if (current->type != PIPE)
		{
			if (is_operator(current) || is_operator(next))
				return (ERROR);
		}
		tokens = tokens->next;
	}
	return (SUCCESS);
}
