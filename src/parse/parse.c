/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:18:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/05 23:48:45 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expand_var(t_token *token, char **env)
{
	// Name is : $ARG
	char	*var;
	char	*dollar_sign;

	dollar_sign = ft_strchr(token->content, '$') + 1;
	var = ft_substr(dollar_sign, 0, ft_strcspn(dollar_sign, " "));
	if (var == NULL)
		return (FAILURE);/**/
	var = getenv(var);
	if (var == NULL)
		return (ERROR);
	
}

void	expand_vars(t_list *tokens, char **env)
{
	t_list	*node;
	t_token	*token;

	node = tokens;
	while (node)
	{
		token = node->content;
		if (token->is_expandable)
			expand_var(token, env);
		node = node->next;
	}
}

int	parse(char *line, t_object *obj, char **env)
{
	int		status;

	line = ft_strtrim(line, " ");
	if (line == NULL)
		return (FAILURE);
	status = tokens_init(&obj->tokens, line);
	free(line);
	if (status == ERROR)
		return (print_error(SYNTAX_ERR), 258);
	if (status == FAILURE)
		return (print_error(MEMORY_ERR), 1);
	ft_lstiter(obj->tokens, display_token); //tskrt
	expand_vars(obj->tokens, env);
	return (SUCCESS);
}
