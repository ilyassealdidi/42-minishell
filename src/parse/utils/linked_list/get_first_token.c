/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:31:53 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/05 12:33:05 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

t_token	*get_first_token(t_list *list)
{
	if (list == NULL)
		return (NULL);
	return ((t_token *)list->content);
}
