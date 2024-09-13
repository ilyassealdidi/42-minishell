/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:40:28 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/13 11:16:00 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_shell(t_object *obj)
{
	ft_lstclear(&obj->commands, destroy_command);
	printf("\033[F\033[3Cexit\n");
	exit(EXIT_SUCCESS);
}
