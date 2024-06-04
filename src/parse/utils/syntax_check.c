/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:24:19 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/04 11:28:59 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid_syntax(t_list *tokens)
{
	t_token	*current;
	t_token	*next;

	if (is_sep(((t_token *)(ft_lstlast(tokens)->content))->content) != NONE
		|| ((t_token *)(tokens->content))->type == PIPE
		|| (ft_strchr((char []){REDIR_IN, REDIR_OUT, APPEND, HEREDOC , 0},
			((t_token *)(tokens->content))->type) && tokens->next == NULL))
		return (ERROR);
	while (tokens->next)
	{
		current = tokens->content;
		next = tokens->next->content; 
		if (ft_strchr((char []){REDIR_IN, REDIR_OUT, APPEND, HEREDOC, PIPE, 0},
			current->type) && next->type == PIPE)
			return (ERROR);
		if (ft_strchr((char []){REDIR_IN, REDIR_OUT, APPEND, HEREDOC, 0},
			current->type) && ft_strchr((char []){REDIR_IN, REDIR_OUT, APPEND, \
			HEREDOC, 0}, next->type))
			return (ERROR);
		tokens = tokens->next;
	}
	return (SUCCESS);
}
