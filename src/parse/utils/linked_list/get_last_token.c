/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:33:22 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/05 12:35:22 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

t_token	*get_last_token(t_list *list)
{
	if (list == NULL)
		return (NULL);
	return ((t_token *)(ft_lstlast(list)->content));
}
