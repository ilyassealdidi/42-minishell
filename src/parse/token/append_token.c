/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:27:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/06 17:50:26 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	is_cmd_exists(char *ptr, char *path,char *cmd)
{
	int		path_len;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	path_len = ft_strlen(path);
	ft_strlcat(ptr, path, path_len + 1);
	ft_strlcat(ptr, "/", path_len + 2);
	ft_strlcat(ptr, cmd, path_len + cmd_len + 2);
	return (access(ptr, X_OK) == 0);
}

static int	set_cmd_path(t_list *head, t_token *token)
{
	char	**paths;
	char	*ptr;
	int		i;

	i = -1;
	if (ft_strlen(token->content) == 0/* || token->type == CMD*/)
		return (SUCCESS);
	ptr = getenv("PATH");
	if (ptr == NULL)
		return (SUCCESS);
	paths = ft_split(ptr, ':');
	if (paths == NULL)
		return (FAILURE);
	if (*paths == NULL)
		return (free(*paths), SUCCESS);
	while (paths[++i] != NULL)
	{
		ptr = malloc(ft_strlen(paths[i]) + ft_strlen(token->content) + 2);
		if (ptr == NULL)
			return (free(paths), FAILURE);
		if (is_cmd_exists(ptr, paths[i], token->content))
			return (free_array(paths), free(token->content),
				token->content = ptr, SUCCESS);
		free(ptr);
	}
	free_array(paths);
	return (SUCCESS);
}

static int	insert_token(t_list **head, t_token *new)
{
	t_list	*node;
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (FAILURE);
	ft_memcpy(token, new, sizeof(t_token));
	node = ft_lstnew(token);
	if (node == NULL)
		return (free(token), FAILURE);
	ft_lstadd_back(head, node);
	return (SUCCESS);
}

static int	count_words(const char *s, int c)
{
	int	cnt;
	int	pre;

	cnt = 0;
	pre = 1;
	while (*s)
	{
		if (*s == c)
			pre = 1;
		else if (pre)
		{
			pre = 0;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static int	is_valid_redirection(t_list *tokens, t_token *new)
{
	t_token	*prev;
	int		len;

	prev = get_last_token(tokens);
	if (prev == NULL || prev->type != REDIR_OUT && prev->type != OUTFILE)
		return (SUCCESS);
	if (!new->is_quoted && new->is_expandable)
	{
		len = ft_strlen(new->content);
		if (count_words(new->content, ' ') > 1)
			return (FAILURE);
		if (new->content[0] == ' ' && prev->type == OUTFILE
			&& prev->content[0] != '\0')
			return (FAILURE);
		
		if (new->content[len - 1] == ' ' && new->is_joinable) //!
			return (FAILURE);
		if (len == 0 && !new->is_joinable && prev->type == REDIR_OUT
			// || prev->type == OUTFILE && prev->content[ft_strlen(prev->content) - 1] == ' '	
			|| count_words(new->content, ' ') > 1
			|| new->is_joinable && new->content[len - 1] == ' '
			// || new->content[0] == ' ' && prev->type == OUTFILE
			)
			return (FAILURE);
	}
	if (prev->type == OUTFILE && prev->is_expandable && !prev->is_quoted)
		if (prev->content[ft_strlen(prev->content) - 1] == ' ')
			return (FAILURE);
	return (SUCCESS);
}

int	split_variable(t_object *obj, t_token *token)
{
	t_token	new;
	int		i;
	char 	**strs;

	if (is_valid_redirection(obj, token) == FAILURE)
		return (ft_printf(AMBIGUOUS_REDIRECT, token->original), FAILURE);
	if (token->content == NULL)
		return (SUCCESS);
	strs = ft_split(token->content, ' ');
	if (strs == NULL)
		return (FAILURE);
	if (*strs == NULL)
		return (free(*strs), SUCCESS);
	i = 0;
	while (strs[i])
	{
		ft_memset(&new, 0, sizeof(t_token));
		new.content = strs[i];
		new.type = ARG;
		if (strs[i + 1] == NULL && token->is_joinable)
			new.is_joinable = true;
		ft_appendtoken(obj, &new);
		i++;
	}
	return (SUCCESS);
}

int	ft_appendtoken(t_object *obj, t_token *new)
{
	t_list	*node;
	t_token	*token;
	int		i;

	if (new->is_expandable && !new->is_quoted)
		return (split_variable(obj, new));
	update_token_type(obj->tokens, new);
	if (set_cmd_path(obj->tokens, new) == FAILURE)
		return (FAILURE);
	if (obj->tokens != NULL && get_last_token(obj->tokens)->is_joinable)
	{
		token = get_last_token(obj->tokens);
		token->content = join(token->content, new->content);
		if (token->content == NULL)
			return (FAILURE);
		token->is_joinable = new->is_joinable;
	}
	else
	{
		if (insert_token(&obj->tokens, new) == FAILURE)
			return (free(new->content), FAILURE);
		if (!new->is_joinable)
			ft_memset(new, 0, sizeof(t_token));
	}
	return (SUCCESS);
}
