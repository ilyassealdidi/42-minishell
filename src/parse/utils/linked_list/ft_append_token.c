/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:27:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/08 21:27:15 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h> 

static bool is_built_in(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len == 4 && ft_strncmp(str, "echo", 4) == 0)
		return (true);
	if (len == 2 && ft_strncmp(str, "cd", 2) == 0)
		return (true);
	if (len == 3 && ft_strncmp(str, "pwd", 3) == 0)
		return (true);
	if (len == 6 && ft_strncmp(str, "export", 6) == 0)
		return (true);
	if (len == 5 && ft_strncmp(str, "unset", 5) == 0)
		return (true);
	if (len == 3 && ft_strncmp(str, "env", 3) == 0)
		return (true);
	if (len == 4 && ft_strncmp(str, "exit", 4) == 0)
		return (true);
	return (false);
}

// NORM
static int	set_cmd_path(t_list *head, t_token *token)
{
	char	**paths;
	char	*var;
	char	*ptr;
	int		i;

	i = -1;
	if ((head == NULL || get_last_token(head)->type == PIPE)
		&& token->type == ARG && is_built_in(token->content) == false)
	{
		token->type = CMD;
		var = getenv("PATH");
		if (var == NULL)
			return (SUCCESS);
		paths = ft_split(var, ':');
		if (paths == NULL || paths[0] == NULL)
			return (free(paths), FAILURE);
		while (paths[++i] != NULL)
		{
			ptr = ft_strjoin(paths[i], "/");
			if (ptr == NULL)
				return (free_array(paths), FAILURE);
			ptr = join(ptr, token->content);
			if (ptr == NULL)
				return (free_array(paths), FAILURE);
			if (access(ptr, X_OK) != -1)
				return (free(token->content), token->content = ptr, SUCCESS);
			free(ptr);
		}
		free_array(paths);
	}
	return (SUCCESS);
}

int	ft_appendtoken(t_list **head, t_token *new)
{
	t_list	*node;
	t_token	*token;

	set_cmd_path(*head, new);
	if (ft_lstlast(*head) != NULL && get_last_token(*head)->is_joinable)
	{
		token = get_last_token(*head);
		token->content = join(token->content, new->content);
		if (token->content == NULL)
			return (FAILURE);
		free(new->content);
		token->is_joinable = new->is_joinable;
	}
	else
	{
		token = malloc(sizeof(t_token));
		if (token == NULL)
			return (FAILURE);
		ft_memcpy(token, new, sizeof(t_token));
		node = ft_lstnew(token);
		if (!node)
			return (free(token), FAILURE);
		ft_lstadd_back(head, node);
	}
	return (SUCCESS);
}
