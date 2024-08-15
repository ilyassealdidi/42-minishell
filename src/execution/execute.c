/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 03:18:42 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/10 17:28:10 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_args(t_list *tokens)
{
	t_list	*node;
	t_token	*token;
	char	**args;
	int		i;

	i = 0;
	args = malloc(ft_lstsize(tokens) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	node = tokens;
	while (node != NULL)
	{
		if (((t_token *)node)->type == PIPE)
			break ;
		if (((t_token *)node)->type != ARG)
		{
			node = node->next;	
			continue ;
		}
		token = node->content;
		args[i] = ft_strdup(token->content);
		if (args[i] == NULL)
			return (free_array(args), NULL);
		node = node->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	exec(t_object *obj)
{
	t_list	*tokens;
	t_token	*token;

	tokens = obj->tokens;
	int pid = fork();

	if (pid == 0)
	{
		//get_args(tokens);
		execve(token->content, get_args(tokens), NULL);
	}
	else
	{
		//wait(NULL);
	}
}
