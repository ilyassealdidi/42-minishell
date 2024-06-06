/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:19:55 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/06 23:36:11 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// "Home: $HOME, USER: $USER"
// "$HOME$USER"
// "$HOME$USER$"
char	*next_part(char *str, int *index, int exit_status)
{
	int		len;

	len = 0;
	if (*str == '$' && isalpha(*(str + 1)))
	{
		while (isalnum(str[++len]))
			;
		*index += len;
		return (ft_substr(str, 0, len));
	}
	else if (*str == '$' && *(str + 1) == '?')
	{
		*index += 2;
		return (ft_itoa(exit_status));
	}
	else
	{
		len = strcspn(str, "$") + (*str == '$');
		*index += len;
		return (ft_substr(str, 0, len));
	}
}

int	expand_vars(t_token *token, int exit_status)
{
	char	*new;
	char	*ptr;
	int		i;

	i = 0;
	new = NULL;
	while (token->content[i] != '\0')
	{
		ptr = next_part(token->content, i, exit_status);
		if (ptr == NULL)
			return (FAILURE);
		new = join(new, ptr);
		free(ptr);
		if (new == NULL)
			return (FAILURE);
	}
	free(token->content);
	token->content = new;
	return (SUCCESS);
}

int	expand(t_object *obj)
{
	t_list	*node;
	t_token	*token;

	node = obj->tokens;
	while (node)
	{
		token = node->content;
		if (token->is_expandable)
			if (expand_vars(token, obj->exit_status) == FAILURE)
				return (FAILURE);
		node = node->next;
	}
}
