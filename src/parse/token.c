/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:22:32 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/04 14:54:47 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token_type	get_token_type(char *str)
{
	t_token_type		type;

	type = is_sep(str);
	if (type != NONE)
		return (type);
	if (*str == ' ')
		return (SPACE);
	if ((*str == '\'' || *str == '"') && ft_strchr(str + 1, *str))
		return (QUOTED);
	if (ft_isprint(*str) && (*str != '\'' && *str != '"'))
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

static int	set_token(char **line, t_token *token)
{
	char				*str;
	int					len;

	if (**line == '\0')
		return (SUCCESS);
	token->type = get_token_type(*line);
	if (token->type == NONE)
		return (ERROR);
	len = get_token_length(*line, token->type);
	if (token->type != SPACE)
	{
		if (token->type == QUOTED)
			(*line)++;
		str = ft_substr(*line, 0, len);
		if (str == NULL)
			return (FAILURE);
		token->content = join(token->content, str);
		if (token->content == NULL)
			return (FAILURE);
		free(str);
	}
	*line += len + (token->type == QUOTED);
	return (SUCCESS);
}

/**
 * Sets the next token by parsing the given line.
 *
 * @param line The line to be parsed.
 * @param token A pointer to the token structure to store the parsed token.
 * @return Returns `SUCCESS` on success, `ERROR` on error, `FAILURE` on memory 
 * allocation failure, and `END_OF_LINE` if the end of the line is reached.
 */
static int	set_next_token(char **line, t_token **token)
{
	static t_token		buffer;
	static t_token_type	prev_type = 0;
	int					status;

	if (!line || !token)
		return (free(buffer.content), ERROR);
	status = set_token(line, &buffer);
	if (status != SUCCESS)
		return (free(buffer.content), status);
	if (buffer.content == NULL && **line == '\0')
		return (prev_type = 0, END_OF_LINE);
	else if (buffer.type == SPACE && buffer.content == NULL)
		prev_type = SPACE;
	else if ((buffer.type == TEXT || buffer.type == QUOTED)
		&& ((int)get_token_type(*line) == TEXT || (int)get_token_type(*line) == QUOTED))
		*token = NULL;
	else
	{
		*token = malloc(sizeof(t_token));
		if (*token == NULL)
			return (free(buffer.content), FAILURE);
		ft_memcpy(*token, &buffer, sizeof(t_token));
		prev_type = buffer.type;
		ft_bzero(&buffer, sizeof(t_token));
	}
	return (SUCCESS);
}

int	tokens_init(t_object *obj, char *line)
{
	int					ret;
	t_token				*token;	//use this instead of static variable

	token = NULL;
	while (1)
	{
		ret = set_next_token(&line, &token);
		if (ret == END_OF_LINE)
			break ;
		if (ret != SUCCESS)
			return (ret);
		if (token != NULL)
		{
			if (ft_appendtoken(&obj->tokens, token) == FAILURE)
				return (free(token), set_next_token(NULL, NULL), FAILURE);
			token = NULL;
		}
	}
	if (is_valid_syntax(obj->tokens) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
