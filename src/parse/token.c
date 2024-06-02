/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:22:32 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/02 21:23:48 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static t_token_type	get_token_type(char *str)
{
	t_token_type	type;

	type = is_sep(str);
	if (type != -1)
		return (type);
	if (*str == '\0')
		return (0);
	if (ft_strchr("'\"", *str) && ft_strchr(str + 1, *str))
		return (QUOTED);
	if (*str == ' ')
		return (SPACE);
	if (ft_isprint(*str))
		return (TEXT);
	return (0);
}

static int	get_token_length(char *line, t_token_type type)
{
	if (type == TEXT)
		return (strcspn(line, " |><'\""));
	else if (type == SPACE)
		return (ft_strspn(line, " "));
	else if (type == PIPE || type == REDIR_IN || type == REDIR_OUT)
		return (1);
	else if (type == HEREDOC || type == APPEND)
		return (2);
	else
		return (ft_strchr(line + 1, *line) - line - 1);
}

static int	set_token(char *line, t_token *token)
{
	char	*str;

	if (*line == '\0')
		return 1;
	token->type = get_token_type(line);
	token->len = get_token_length(line, token->type);
	if (token->type == SPACE)
		return (1);
	if (token->type == QUOTED)
		line++;
	str = ft_substr(line, 0, token->len);
	if (str == NULL)
		return (0);
	token->content = join(token->content, str);
	free(str);
	return (1);
}

static int	set_next_token(char **line, t_token **token)
{
	static t_token		buffer;
	static t_token_type	prev_type = 0;

	if (set_token(*line, &buffer) == 0)
		return (free(buffer.content), -1);
	*line += buffer.len;
	if (buffer.type == QUOTED)
		*line += 2;
	if (buffer.content == NULL && **line == '\0')
		return (prev_type = 0);
	else if (buffer.type == SPACE && buffer.content == NULL)
		prev_type = SPACE;
	else if ((buffer.type == TEXT || buffer.type == QUOTED)
		&& ((int)get_token_type(*line) == TEXT || (int)get_token_type(*line) == QUOTED))
		*token = NULL;
	else
	{
		*token = malloc(sizeof(t_token));
		if (*token == NULL)
			return (free(buffer.content), -1);
		ft_memcpy(*token, &buffer, sizeof(t_token));
		prev_type = buffer.type;
		ft_bzero(&buffer, sizeof(t_token));
	}
	return (1);
}

int	tokens_init(t_object *obj, char *line)
{
	int		ret;
	t_token	*token;

	token = NULL;
	while (1)
	{
		ret = set_next_token(&line, &token);
		if (ret <= 0)
		{
			// if (ret == -1)
			break ;
		}
		if (token != NULL)
		{
			if (ft_appendtoken(&obj->tokens, token) == 0)
				return (free(token), 0);
			token = NULL;
		}
	}
	if (is_valid_syntax(obj->tokens) == 0)
		return (0);
	return (1);
}
