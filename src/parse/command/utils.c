/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:07:28 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/31 21:58:15 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*get_command(t_list *list)
{
	if (list == NULL)
		return (NULL);
	return ((t_command *)list->content);
}

void	destroy_command(void *content)
{
	t_command		*command;

	command = (t_command *)content;
	free_array(command->argv);
	free_array(command->envp);
	free(command);
}

