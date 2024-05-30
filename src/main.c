/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/28 22:32:26 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **av, char **env)
{
	char		*rl;
	t_object	obj;

	ft_memset(&obj, 0, sizeof(t_object));
	while (1)
	{
		if (av[1]) 
			rl = av[1];
		else
			rl = readline(YELLOW"Minishell$ "RESET);
		if (!rl)
			return (1);
		if (parse(rl, &obj) == 0)
			return (free(rl), 1);
		free(rl);
		ft_lstclear(&obj.tokens, free);
	}
	return (0);
}
