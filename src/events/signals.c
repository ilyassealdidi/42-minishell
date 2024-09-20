/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:45:48 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/20 19:04:18 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc_interrupt_handler(int sig)
{
	g_received_signal++;
	close(0);
}

static void	interrupt_handler(int sig)
{
	g_received_signal++;
	(void)sig;
	ft_printf("\n%s", FAILURE_PROMPT);
	rl_replace_line("", 0);
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, SIG_IGN);
}
