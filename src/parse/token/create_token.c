/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:22:32 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/03 19:40:10 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token_type	get_token_type(char *str)
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

static bool	contains_env(char *str)
{
	char			*ptr;

	if (*str == '\'')
		return (false);
	while (1)
	{
		ptr = ft_strchr(str + (*str == '"'), '$');
		if (ptr == NULL
			|| (*str == '"' && ft_strchr(str + 1, '"') < ptr)
			|| (*str != '"' && str + ft_strcspn(str, " |><'\"") < ptr))
			return (false);
		if (ft_isalpha(*(ptr + 1)) || *(ptr + 1) == '?')
			return (true);
		str = ptr + 1;
	}
}

static int	get_token_length(char *line, t_token_type type)
{
	if (type == PIPE || type == REDIR_IN || type == REDIR_OUT)
		return (1);
	else if (type == HEREDOC || type == APPEND)
		return (2);
	else if (*line == '"' || *line == '\'')
		return (ft_strchr(line + 1, *line) - line - 1);
	else
		return (ft_strcspn(line, " |><'\"\t"));
}

static int	set_next_token(char **line, t_token *token)
{
	int				len;

	ft_memset(token, 0, sizeof(t_token));
	token->type = get_token_type(*line);
	if (token->type == NONE)
		return (ERROR);
	len = get_token_length(*line, token->type);
	token->state |= EXPANDABLE * contains_env(*line);
	token->state |= QUOTED * (**line == '"' || **line == '\'');
	if (token->type == ARG)
	{
		token->content = ft_substr(*line, is_quoted(token), len);
		if (token->content == NULL)
			return (FAILURE);
	}
	else
		token->content = NULL;
	*line += len + 2 * is_quoted(token);
	token->state |= JOINABLE * (ft_strchr(" <>|\t", **line) == NULL
			&& **line != '\0' && token->type == ARG);
	return (SUCCESS);
}

int	tokens_init(t_object *obj, char *line)
{
	int				ret;
	t_token			token;

	while (1)
	{
		while (*line != '\0' && (*line == ' ' || *line == '\t'))
			line++;
		if (*line == '\0')
			break ;
		ret = set_next_token(&line, &token);
		if (ret != SUCCESS)
			return (ft_lstclear(&obj->tokens, destroy_token), ret);
		if (expand_vars(obj, &token) == FAILURE
			|| ft_appendtoken(obj, &token) == FAILURE)
			return (free(token.content), FAILURE);
	}
	if (is_valid_syntax(obj->tokens) == ERROR)
		return (ft_lstclear(&obj->tokens, destroy_token), ERROR);
	return (SUCCESS);
}
