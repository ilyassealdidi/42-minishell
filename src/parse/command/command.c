/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:49:41 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/15 12:49:06 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	commands_init(t_object *obj)
{
	t_command	*command;
	t_list		*tokens;
	t_list		*new;

	tokens = obj->tokens;
	while (tokens)
	{
		command = malloc(sizeof(t_command));
		if (command == NULL)
			return (FAILURE);
		ft_memset(command, 0, sizeof(t_command));
		if (new_command(tokens, command) == FAILURE)
			return (FAILURE);
		new = ft_lstnew(command);
		if (new == NULL)
			return (destroy_command(command), FAILURE);
		ft_lstadd_back(&obj->commands, new);
		while (tokens && get_token(tokens)->type != PIPE)
			tokens = tokens->next;
		if (tokens && get_token(tokens)->type == PIPE)
			tokens = tokens->next;
	}
	return (SUCCESS); 
}
