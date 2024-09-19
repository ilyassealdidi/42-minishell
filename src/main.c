/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/19 09:32:32 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int					g_received_signal = 0;



void	f(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_object		obj;
	struct termios	term;

	if (argc != 1 || !isatty(STDIN_FILENO))
		return (ft_putstr_fd("Usage: ./minishell\n", 2), EXIT_FAILURE);
	obj = (t_object){0};
	init_signals();
	if (init_env(&obj.env, env) == FAILURE)
		return (ft_error(NULL, NULL, NULL), EXIT_FAILURE);
	tcgetattr(STDIN_FILENO, &term);
	while (true)
	{

		if (generate_commands(&obj) == FAILURE)
			continue ;
		execute_commands(&obj);
		ft_lstclear(&obj.commands, destroy_command);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	return ((void)argv, EXIT_SUCCESS);
}
