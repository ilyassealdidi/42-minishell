/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:24:19 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/02 21:24:29 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid_syntax(t_list *tokens)
{
	t_token	*current;
	t_token	*next;

	if (((t_token *)(tokens->content))->type == PIPE)
		return (0);
	if (ft_strchr((char []){REDIR_IN, REDIR_OUT, APPEND, HEREDOC , 0},
			((t_token *)(tokens->content))->type) && tokens->next == NULL)
		return (0);
	while (tokens->next)
	{
		current = tokens->content;
		next = tokens->next->content; 
		if (ft_strchr((char []){REDIR_IN, REDIR_OUT, APPEND, HEREDOC, PIPE, 0},
			current->type) && next->type == PIPE)
			return (0);
		if (ft_strchr((char []){REDIR_IN, REDIR_OUT, APPEND, HEREDOC, 0},
			current->type) && ft_strchr((char []){REDIR_IN, REDIR_OUT, APPEND, \
			HEREDOC, 0}, next->type))
			return (0);		
		tokens = tokens->next;
	}
	return (1);
}
