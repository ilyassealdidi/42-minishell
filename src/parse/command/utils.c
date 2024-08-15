/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:07:28 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/15 14:19:09 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	destroy_command(void *content)
{
	t_command	*command;

	command = (t_command *)content;
	free_array(command->args);
	free(command);
}

