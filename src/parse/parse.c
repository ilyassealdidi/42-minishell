/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/30 11:10:56 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
# define is_sep is_seperator

char	*join(char *str1, char *str2)
{
	char	*tmp;
	char	*joined;

	if (!str1)
	{
		tmp = ft_strdup(str2);
		if (tmp == NULL)
			free(str2);
		return (tmp);
	}
	tmp = str1;
	joined = ft_strjoin(str1, str2);
	free(tmp);
	if (joined == NULL)
		return (NULL);
	return (joined);
}

char	*handle_alpha(char **line, char *buffer)
{
	char	*extracted;
	char	*ptr;

	ptr = *line;
	while (ft_isalnum(*ptr))
		ptr++;
	extracted = ft_substr(*line, 0, ptr - *line);
	if (!extracted)
		return (free(buffer), NULL);
	*line = ptr;
	buffer = join(buffer, extracted);
	free(extracted);
	return (buffer);
}

char	*handle_quote(char **line, char *buffer)
{
	char	*extracted;
	char	*start;
	char	*end;

	start = (*line) + 1;
	end = ft_strchr(start, **line);
	if (!end)
		return (NULL);
	extracted = ft_substr(start, 0, end - start);
	if (!extracted)
		return (NULL);
	*line = end + 1;
	buffer = join(buffer, extracted);
	free(extracted);
	return (buffer);
}

int	handle_sep(char **line, char **buffer, t_list **list)
{
	*buffer = ft_strdup(is_seperator(*line));
	if (!*buffer)
		return (0);
	*line += ft_strlen(is_seperator(*line));
	if (ft_appendtoken(list, buffer) == 0)
		return (free(*buffer), 0);
	return (1);
}

// t_lexer	*create_token(char	*content, t_token_type type)
// {
// 	t_lexer	*lex;

// 	lex = malloc(sizeof(t_lexer));
// 	if (lex == NULL)
// 		return (NULL);
// 	lex->str = content;
// 	lex->type = type;
// 	return (lex);
// }

int	tokens_init(t_object *obj, char *line)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		if (buffer != NULL && ft_appendtoken(&obj->tokens, &buffer) == 0)
			return (0);
		if (*line == '\0')
			break ;
		if (is_sep(line) && !handle_sep(&line, &buffer, &obj->tokens))
			return (0);
		while (*line == ' ')
			line++;
		while (*line != '\0' && (ft_isalnum(*line) || ft_strchr("'\"", *line)))
		{
			if (ft_isalnum(*line))
				buffer = handle_alpha(&line, buffer);
			else
				buffer = handle_quote(&line, buffer);
			if (buffer == NULL)
				return (0);
		}
	}
	return 1;
}

void	print_content(void *content)
{
	ft_printf("%s\n", ((t_lexer *)content)->str);
}

int	parse(char *line, t_object *obj)
{
	line = ft_strtrim(line, " ");
	if (line == NULL)
		return (0);
	if (tokens_init(obj, line) == 0 || !obj->tokens)
		return (ft_printf("Syntax Error"), ft_lstclear(&obj->tokens, free),
			free(line), 0);
	free(line);
	ft_lstiter(obj->tokens, print_content);
	return (1);
}
