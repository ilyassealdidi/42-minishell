/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:27:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/05 22:11:50 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	update_token_type(t_list *head, t_token *token)
{
	if ((ft_lstlast(head) == NULL || get_last_token(head)->type == PIPE)
		&& token->type == ARG)
		token->type = CMD;
}

int	ft_appendtoken(t_list **head, t_token *token)
{
	t_list	*node;
	t_token	*new;

	update_token_type(*head, token);
	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (FAILURE);
	ft_memcpy(new, token, sizeof(t_token));
	node = ft_lstnew(new);
	if (!node)
		return (free(new), FAILURE);
	ft_lstadd_back(head, node);
	return (SUCCESS);
}
