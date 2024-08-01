/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:04:50 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/01 02:06:34 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*new_command(t_list *tokens)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->command = get_command(tokens);
	if (command->command == NULL)
		return (free(command), NULL);
	command->args = get_args(&tokens);
	if (command->args == NULL)
		return (free(command), NULL);
	return (command);
}

void	free_command(t_command *command)
{
	free(command->command);
	free_array(command->args);
	free(command);
}

void	build_command(t_list *tokens)
{
	t_command	*command;

	while (tokens)
	{
		command = new_command(tokens);
		if (command == NULL)
			return ;
		ft_lstadd_back(&g_data->commands, ft_lstnew(command));
	}
}
