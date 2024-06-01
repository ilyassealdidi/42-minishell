/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/01 20:45:12 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
# define is_sep is_separator

// echo "Hello World"

t_token_type	get_token_type(char *str)
{
	t_token_type	type;

	type = is_sep(str);
	if (type != -1)
		return (type);
	if (ft_strchr("'\"", *str) && ft_strchr(str + 1, *str))
		return (QUOTED);
	if (ft_isprint(*str))
		return (TEXT);
	return (SPACE);
}

int	get_token_length(char *line, t_token_type type)
{
	if (type == TEXT)
		return (strcspn(line, " |><"));
	else if (type == SPACE)
		return (ft_strspn(line, " "));
	else if (type == PIPE || type == REDIR_IN || type == REDIR_OUT)
		return (1);
	else if (type == HEREDOC || type == APPEND)
		return (2);
	else
		return (ft_strchr(line + 1, *line) - line - 1);
}

int	set_token(char *line, t_token *token)
{
	char	*str;

	if (*line == '\0')
		return 1;
	token->type = get_token_type(line);
	token->len = get_token_length(line, token->type);
	if (token->type == SPACE)
		return (1);
	str = ft_substr(line, 0, token->len);
	if (str == NULL)
		return (0);
	token->content = join(token->content, str);
	free(str);
	return (1);
}

int	set_next_token(char **line, t_token **token)
{
	static t_token	buffer;

	if (set_token(*line, &buffer) == 0)
		return (free(buffer.content), -1);
	*line += buffer.len;
	if (ft_strchr(" ", **line) || is_separator(*line))
	{
		*token = malloc(sizeof(t_token));
		if (*token == NULL)
			return (free(buffer.content), -1);
		ft_memcpy(*token, &buffer, sizeof(t_token));
		ft_bzero(&buffer, sizeof(t_token));
	}
	else
		*token = NULL;
	return (1);
}

/*
Make the function set_next_token returns:
	-1	: on failure
	0	: on adding a token
	1	: on success
*/
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
			// break ;
		}
		if (token != NULL)
			if (ft_appendtoken(&obj->tokens, token) == 0)
				return (free(token), 0);
	}
	return (1);
}

void	print_content(void *content)
{
	ft_printf("%s\n", ((t_token *)content)->content);
}

int	parse(char *line, t_object *obj)
{
	line = ft_strtrim(line, " ");
	if (line == NULL)
		return (0);
	if (tokens_init(obj, line) == 0)
		return (ft_printf("Syntax Error"), ft_lstclear(&obj->tokens, free),
			free(line), 0);
	free(line);
	ft_lstiter(obj->tokens, print_content);
	return (1);
}
