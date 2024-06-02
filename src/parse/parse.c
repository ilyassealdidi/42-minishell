/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/02 21:45:10 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse(char *line, t_object *obj)
{
	line = ft_strtrim(line, " ");
	if (line == NULL)
		return (0);
	if (tokens_init(obj, line) == 0)
		return (ft_printf("Syntax Error\n"),
			free(line), 0);
	free(line);
	ft_lstiter(obj->tokens, print_content);
	return (1);
}
