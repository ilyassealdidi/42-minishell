/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/05 22:16:16 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse(char *line, t_object *obj, char **env)
{
	int		status;

	line = ft_strtrim(line, " ");
	if (line == NULL)
		return (FAILURE);
	status = tokens_init(&obj->tokens, line);
	free(line);
	if (status == ERROR)
		return (print_error(SYNTAX_ERR), 258);
	if (status == FAILURE)
		return (print_error(MEMORY_ERR), 1);
	ft_lstiter(obj->tokens, display_token); //tskrt
	expand();
	return (SUCCESS);
}
