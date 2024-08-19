/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:20:01 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/18 09:21:44 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_quoted(t_token *token)
{
	return ((token->state & QUOTED) != 0);
}

bool	is_expandable(t_token *token)
{
	return ((token->state & EXPANDABLE) != 0);
}

bool	is_joinable(t_token *token)
{
	return ((token->state & JOINABLE) != 0);
}

void	set_token_state(t_token *token, int flag, bool value)
{
	if (value)
		token->state |= flag;
	else
		token->state &= ~flag;
}
