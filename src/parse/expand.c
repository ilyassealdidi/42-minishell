/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:19:55 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/28 07:33:47 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_part_len(char *str, int *len)
{
	if (*str == '$')
	{
		str++;
		if (*str == '?')
			return (*len = 1);
		*len = 0;
		if (ft_isdigit(*str))
			return (0);
		while (ft_isalnum(str[*len]) || str[*len] == '_')
			(*len)++;
		if (*len == 0)
			return (*len = 1, 0);
		return (1);
	}
	else
		return (*len = ft_strcspn(str, "$"), 0);
}

static int	set_next_part(t_object *obj, char **str, char **ptr)
{
	int		len;
	int		is_env;
	char	*substring;

	is_env = set_part_len(*str, &len);
	if (!is_env)
		*ptr = ft_substr(*str, 0, len);
	else
	{
		substring = ft_substr(*str, 1, len);
		if (substring == NULL)
			return (FAILURE);
		*ptr = ft_strdup(get_env(obj, substring));
		free(substring);
	}
	*str += len + (is_env);
	if (*ptr == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	expand_vars(t_object *obj, t_token *token)
{
	char	*new;
	char	*old;
	char	*ptr;

	if (!token->is_expandable
		|| obj->tokens && get_last_token(obj->tokens)->type == HEREDOC)
		return (SUCCESS);
	new = NULL;
	old = token->content;
	while (*token->content != '\0')
	{
		if (set_next_part(obj, &token->content, &ptr) == FAILURE)
			return (FAILURE);
		new = join(new, ptr);
		if (new == NULL)
			return (FAILURE);
	}
	free(old);
	token->content = new;
	return (SUCCESS);
}
