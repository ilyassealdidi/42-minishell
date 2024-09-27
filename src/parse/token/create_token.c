/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:22:32 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/27 18:36:07 by ialdidi          ###   ########.fr       */
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

static bool	contains_env(t_string original, t_string str)
{
	t_string		ptr;

	if (*original == '\'')
		return (false);
	if (*str == '"')
		return (true);
	ptr = ft_strchr(str, '$');
	if (isset(ptr))
	{
		original = ft_strchr(original, '$');
		if (isnull(ft_strchr(" |><'\"\t", original[1]))
			&& (ft_isalpha(original[1])
				|| original[1] == '_' || original[1] == '?'))
			return (true);
	}
	return (false);
}

static int	get_token_length(t_token *token, char *line)
{
	int				len;

	if (is_operator(token))
		return (1 + (token->type == HEREDOC || token->type == APPEND));
	else if (*line == '"' || *line == '\'')
		return (ft_strchr(line + 1, *line) - line - 1);
	else if (*line == '$')
	{
		if (!ft_isalpha(line[1]) && line[1] != '_')
			return (ft_strcspn(line + 1, " |><'\"\t$") + 1);
		len = 1;
		while (ft_isalnum(line[len]) || line[len] == '_')
			len++;
		return (len);
	}
	else
		return (ft_strcspn(line, " |><'\"\t$"));
}

int	set_token(char **line, t_token *token)
{
	int				len;

	ft_memset(token, 0, sizeof(t_token));
	token->type = get_token_type(*line);
	if (token->type == NONE)
		return (ERROR);
	len = get_token_length(token, *line);
	if (token->type == ARG)
	{
		set_token_state(token, QUOTED, **line == '"' || **line == '\'');
		token->content = ft_substr(*line, is_quoted(token), len);
		if (isnull(token->content))
			return (FAILURE);
		set_token_state(token, EXPANDABLE, contains_env(*line, token->content));
	}
	*line += len + 2 * is_quoted(token);
	if (isnull(ft_strchr(" <>|\t", **line))
		&& **line != '\0'
		&& token->type == ARG)
		set_token_state(token, JOINABLE, true);
	return (SUCCESS);
}
