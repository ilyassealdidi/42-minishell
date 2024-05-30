/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:27:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/30 10:43:28 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_appendtoken(t_list **head, char **buffer)
{
	t_list	*new;
	t_lexer	*lex;

	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return (free(*buffer), 0);
	lex->str = *buffer;
	new = ft_lstnew(lex);
	if (!new)
		return (free(*buffer), 0);
	ft_lstadd_back(head, new);
	*buffer = NULL;
	return (1);
}
