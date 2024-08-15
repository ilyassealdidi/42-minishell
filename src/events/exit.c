/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:40:28 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/14 15:43:26 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_shell(t_object *obj)
{
	ft_lstclear(&obj->tokens, destroy_token);
	ft_printf("\033[F\033[3Cexit\n");
	exit(0);
}
