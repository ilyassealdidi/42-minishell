/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:43:31 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/21 16:48:20 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_redir(t_token *token)
{
	return (token->type == REDIR_OUT || token->type == APPEND
		|| token->type == REDIR_IN || token->type == HEREDOC);
}

bool	is_operator(t_token *token)
{
	return (token->type == PIPE || is_redir(token));
}
