/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:27:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/26 07:05:01 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h> 

static bool	is_built_in(char *str)
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

static bool	is_cmd_exists(char *ptr, char *cmd)
{
	int		path_len;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	path_len = ft_strlen(ptr);
	ft_strlcat(ptr, ptr, path_len + 1);
	ft_strlcat(ptr, "/", path_len + 2);
	ft_strlcat(ptr, cmd, path_len + cmd_len + 2);
	return (access(ptr, X_OK) == 0);
}

static int	set_cmd_path(t_list *head, t_token *token)
{
	char	**paths;
	char	*ptr;
	int		i;

	if (ft_strlen(token->content) == 0 || token->type == CMD)
		return (SUCCESS);
	ptr = getenv("PATH");
	if (ptr == NULL)
		return (SUCCESS);
	paths = ft_split(ptr, ':');
	if (paths == NULL || paths[0] == NULL)
		return (free(paths), FAILURE);
	while (paths[++i] != NULL)
	{
		ptr = malloc(ft_strlen(paths[i]) + ft_strlen(token->content) + 2);
		if (ptr == NULL)
			return (free(paths), FAILURE);
		if (is_cmd_exists(ptr, token->content))
			return (free_array(paths), free(token->content), token->content = ptr, SUCCESS);
		free(ptr);
	}
	free_array(paths);
	return (SUCCESS);
}

static void	update_token_type(t_list *head, t_token *new)
{
	t_token	*last_token;

	last_token = get_last_token(head);
	if (is_built_in(new->content))
	{
		new->type = BUILTIN;
		return ;
	}
	if ((head == NULL || last_token->type == PIPE) && new->type == ARG)
		new->type = CMD;
	if (head != NULL && last_token->type == REDIR_OUT)
		new->type = FFILE;
	if (head != NULL && last_token->type == BUILTIN)
		if (*new->content == '-')
			new->type = OPTION;
}

int	ft_appendtoken(t_list **head, t_token *new)
{
	t_list	*node;
	t_token	*token;

	update_token_type(*head, new);
	set_cmd_path(*head, new);
	if (ft_lstlast(*head) != NULL && get_last_token(*head)->is_joinable)
	{
		token = get_last_token(*head);
		token->content = join(token->content, new->content);
		if (token->content == NULL)
			return (FAILURE);
		token->is_joinable = new->is_joinable;
	}
	else
	{
		token = malloc(sizeof(t_token));
		if (token == NULL)
			return (FAILURE);
		ft_memcpy(token, new, sizeof(t_token));
		node = ft_lstnew(token);
		if (node == NULL)
			return (free(token), FAILURE);
		ft_lstadd_back(head, node);
	}
	return (SUCCESS);
}
