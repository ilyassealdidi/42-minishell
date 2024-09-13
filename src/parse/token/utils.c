/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 08:47:03 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/13 06:08:13 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*get_token(t_list *list)
{
	if (list == NULL)
		return (NULL);
	return ((t_token *)list->content);
}

t_token	*get_last_token(t_list *list)
{
	if (list == NULL)
		return (NULL);
	return ((t_token *)(ft_lstlast(list)->content));
}

bool	is_redir(t_token *token)
{
	return (token->type == REDIR_OUT || token->type == APPEND
		|| token->type == REDIR_IN);
}

void	destroy_token(void *content)
{
	t_token			*token;

	token = (t_token *)content;
	free(token->content);
	free(token);
}
