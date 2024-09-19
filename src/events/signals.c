/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:45:48 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/19 15:33:53 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	interrupt(int sig)
{
	g_received_signal++;
	(void)sig;
	ft_printf("\n%s", FAILURE_PROMPT);
	rl_replace_line("", 0);
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, interrupt);
	signal(SIGQUIT, SIG_IGN);
}
