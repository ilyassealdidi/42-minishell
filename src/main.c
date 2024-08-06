/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:25 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/06 14:28:57 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **env)
{
	t_object			obj;
	int					status;
	// if (argc != 1)
	// 	return (ft_printf("Usage: ./minishell\n"), 1);
	ft_memset(&obj, 0, sizeof(t_object));
	signal(SIGINT, terminate);
	if (init_env(&obj, env) == FAILURE)
		return (ft_printf("Error: failed to initialize environment\n"), 1);
	// ft_lstiter(obj.env, print_env);
	set_env(&obj, "var", "ls -l");
	while (1)
	{
		if (argv[1])
			obj.line = ft_strdup("$var");
		else
			obj.line = readline(YELLOW"Minishell$ "RESET);
		if (!obj.line)
			continue ;
		if (obj.line[0] != '\0')
			add_history(obj.line);
		status = generate_commands(&obj);
		free(obj.line);
		ft_lstclear(&obj.tokens, free_token);
		if (status != SUCCESS)
			continue ;
		exec(&obj);
	}
	return ((void)argc, 0);
}
