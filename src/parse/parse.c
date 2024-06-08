/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/08 21:21:38 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse(char *line, t_object *obj)
{
	int		status;
	t_list	*list;

	line = ft_strtrim(line, " ");
	if (line == NULL)
		return (FAILURE);
	status = tokens_init(obj, line);
	free(line);
	if (status == ERROR)
		return (print_error(SYNTAX_ERR), 258);
	if (status == FAILURE)
		return (print_error(MEMORY_ERR), 1);
	ft_lstiter(obj->tokens, display_token); //DELETE_ME
	return (SUCCESS);
}
