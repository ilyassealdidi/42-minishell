/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:19:55 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/12 09:44:51 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TODO : Escape dollar sign

static int	get_part_len(char *str, bool is_var)
{
	int	len;

	len = 0;
	if (is_var == false)
		return (ft_strcspn(str, "$") + (*str == '$'));
	while (ft_isalnum(str[++len]))
		;
	return (len - 1);
}

// NORM
static int	next_part(char **str, char **ptr, int exit_status)
{
	char	*tmp;
	char	*var;

	if (**str == '$' && ft_isalpha(*(*str + 1)))
	{
		tmp = ft_substr(*str + 1, 0, get_part_len(*str, true));
		if (tmp == NULL)
			return (FAILURE);
		if (getenv(tmp) == NULL)
			return (free(tmp), *str += get_part_len(*str, true) + 1,
				*ptr = "", SUCCESS);
		*ptr = ft_strdup(getenv(tmp));
		if (*ptr == NULL)
			return (free(tmp), FAILURE);
		return (*str += get_part_len(*str, true) + 1, free(tmp), SUCCESS);
	}
	else if (**str == '$' && *(*str + 1) == '?')
	{
		*ptr = ft_itoa(exit_status);
		if (*ptr == NULL)
			return (FAILURE);
		return (*str += 2, SUCCESS);
	}
	// else if (**str == '$' && *(*str + 1) == '\0')
	// 	return (*ptr = "", *str += 1, SUCCESS);
	*ptr = ft_substr(*str, 0, get_part_len(*str, false));
	if (*ptr == NULL)
		return (*str += 1, FAILURE);
	return (*str += get_part_len(*str, false), SUCCESS);
}

int	expand_vars(t_object *obj, t_token *token)
{
	char	*new;
	char	*old;
	char	*ptr;

	if (token->is_expandable == false
		|| get_last_token(obj->tokens)->type == HEREDOC)
		return (SUCCESS);
	new = NULL;
	old = token->content;
	while (*token->content != '\0')
	{
		if (next_part(&token->content, &ptr, obj->exit_status) == FAILURE)
			return (FAILURE);
		new = join(new, ptr);
		if (new == NULL)
			return (FAILURE);
	}
	free(old);
	token->content = new;
	return (SUCCESS);
}
