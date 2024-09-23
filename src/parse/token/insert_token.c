/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:03:53 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/23 12:42:23 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	insert_token(t_list **head, t_token *new)
{
	t_list			*node;
	t_token			*token;

	token = ft_calloc(1, sizeof(t_token));
	if (isnull(token))
		return (FAILURE);
	ft_memcpy(token, new, sizeof(t_token));
	node = ft_lstnew(token);
	if (isnull(node))
		return (free(token), FAILURE);
	ft_lstadd_back(head, node);
	return (SUCCESS);
}

static int	split_variable(t_object *obj, t_token *token)
{
	t_token			new;
	int				i;
	char			**strs;

	ft_memset(&new, 0, sizeof(t_token));
	if (isnull(token->content))
		return (ft_appendtoken(obj, &new), SUCCESS);
	strs = ft_split(token->content, ' ');
	if (isnull(strs))
		return (FAILURE);
	free(token->content);
	if (isnull(*strs))
		return (free(strs), ft_appendtoken(obj, &new), SUCCESS);
	i = -1;
	while (strs[++i])
	{
		ft_memset(&new, 0, sizeof(t_token));
		new.content = strs[i];
		new.type = ARG;
		if (isnull(strs[i + 1]) && is_joinable(token))
			new.state |= JOINABLE;
		if (ft_appendtoken(obj, &new) == FAILURE)
			return (free_array(strs), token->content = NULL, FAILURE);
	}
	return (free(strs), SUCCESS);
}

int	ft_appendtoken(t_object *obj, t_token *new)
{
	t_token			*token;

	update_token(obj->tokens, new);
	if (is_expandable(new) && !is_quoted(new))
		return (split_variable(obj, new));
	if (obj->tokens != NULL && is_joinable(get_last_token(obj->tokens)))
	{
		token = get_last_token(obj->tokens);
		if (new->content)
		{
			token->content = ft_strjoin_free(token->content, new->content, BOTH);
			if (isnull(token->content))
				return (FAILURE);
		}
		set_token_state(token, JOINABLE, new->state & JOINABLE);
		set_token_state(token, QUOTED, new->state & QUOTED);
	}
	else
	{
		if (insert_token(&obj->tokens, new) == FAILURE)
			return (free(new->content), FAILURE);
	}
	return (SUCCESS);
}
