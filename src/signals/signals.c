/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:48:09 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/08 15:10:25 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	exit_shell(t_object *obj)
{
	ft_lstclear(&obj->tokens, free_token);
	ft_printf("\033[F\033[3Cexit\n");
	exit(0);
}

static void	terminate(int sig)
{
	g_received_signal++;
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, terminate);
	signal(SIGQUIT, SIG_IGN);
}
