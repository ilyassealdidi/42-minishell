/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:27:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/07 12:02:15 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h> 

// Warning : don't upate the token content until joining the joinable 
// tokens is accomplished
static int	update_token(t_list *head, t_token *token)
{
	char	**paths;
	char	*var;
	char	*ptr;
	int		i;

	i = -1;
	if ((ft_lstsize(head) == 0 || get_last_token(head)->type == PIPE)
		&& token->type == ARG)
	{
		token->type = CMD;
		// var = getenv("PATH");
		// if (var == NULL)
		// 	return (SUCCESS);
		// paths = ft_split(var, ':');
		// if (paths == NULL)
		// 	return (FAILURE);
		// while (paths[++i] != NULL)
		// {
		// 	ptr = ft_strjoin(paths[i], "/");
		// 	if (ptr == NULL)
		// 		return (free_array(paths), FAILURE);
		// 	ptr = join(ptr, token->content);
		// 	if (ptr == NULL)
		// 		return (free_array(paths), FAILURE);
		// 	if (access(ptr, X_OK) != -1)
		// 	{
		// 		free(token->content);	
		// 		token->content = ptr;
		// 		return (SUCCESS);
		// 	}
		// 	free(ptr);
		// }
		// free_array(paths);
	}
	return (SUCCESS);
}

int	ft_appendtoken(t_list **head, t_token *token)
{
	t_list	*node;
	t_token	*new;

	update_token(*head, token);
	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (FAILURE);
	ft_memcpy(new, token, sizeof(t_token));
	node = ft_lstnew(new);
	if (!node)
		return (free(new), FAILURE);
	ft_lstadd_back(head, node);
	return (SUCCESS);
}
