/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:22:32 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/23 19:12:40 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token_type	get_token_type(t_string str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(str, ">", 1) == 0)
		return (REDIR_OUT);
	if (ft_strncmp(str, "<", 1) == 0)
		return (REDIR_IN);
	if (((*str == '\'' || *str == '"') && ft_strchr(str + 1, *str))
		|| (*str != '\'' && *str != '"'))
		return (ARG);
	return (NONE);
}

bool	contains_env(t_string str)
{
	t_string		ptr;

	ptr = ft_strchr(str, '$');
	if (isset(ptr) && (*(ptr + 1) != '\0'))
		return (true);
	return (false);
}

static int	get_token_length(t_string line, t_token_type type)
{
	int				len;

	if (type == PIPE || type == REDIR_IN || type == REDIR_OUT)
		return (1);
	else if (type == HEREDOC || type == APPEND)
		return (2);
	else if (*line == '"' || *line == '\'')
		return (ft_strchr(line + 1, *line) - line - 1);
	else if (*line == '$')
	{
		if (!ft_isalpha(line[1]) && !ft_strchr("_ |><'\"\t$", line[1]))
			return (2);
		len = 1;
		while (ft_isalnum(line[len]) || line[len] == '_')
			len++;
		return (len);
	}
	else
		return (ft_strcspn(line, " |><'\"\t$"));
}

int	set_token(t_object *obj, char **line, t_token *token)
{
	int				len;

	ft_memset(token, 0, sizeof(t_token));
	token->type = get_token_type(*line);
	if (token->type == NONE)
		return (ERROR);
	len = get_token_length(*line, token->type);
	if (token->type == ARG)
	{
		set_token_state(token, QUOTED, **line == '"' || **line == '\'');
		token->content = ft_substr(*line, is_quoted(token), len);
		if (isnull(token->content))
			return (FAILURE);
		set_token_state(token, EXPANDABLE,
			**line != '\'' && contains_env(token->content));
	}
	*line += len + 2 * is_quoted(token);
	if (isnull(ft_strchr(" <>|\t", **line))
		&& **line != '\0' && token->type == ARG)
		set_token_state(token, JOINABLE, true);
	return (SUCCESS);
}
