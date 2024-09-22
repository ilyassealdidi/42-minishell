/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:19:55 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/22 11:35:19 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_part_len(t_string str, int *len)
{
	if (*str == '$' && *(str + 1) != '\0')
	{
		str++;
		if (!ft_isalpha(*str) && *str != '_')
			return (*len = 1, true);
		*len = 0;
		while (ft_isalnum(str[*len]) || str[*len] == '_')
			(*len)++;
		return (true);
	}
	*len = ft_strcspn(str, "$") + (*str == '$');
	return (false);
}

static int	set_next_part(t_object *obj, char **str, char **ptr)
{
	int				len;
	int				is_var;
	t_string		variable;
	t_string		value;

	is_var = set_part_len(*str, &len);
	if (!is_var)
		*ptr = ft_substr(*str, 0, len);
	else
	{
		variable = ft_substr(*str, 1, len);
		if (isnull(variable))
			return (FAILURE);
		value = get_env(obj->env, variable);
		free(variable);
		if (value != NULL)
			*ptr = ft_strdup(value);
		else
			*ptr = NULL;
	}
	*str += len + (is_var);
	if (isnull(*ptr) && (!is_var || value != NULL))
		return (FAILURE);
	return (SUCCESS);
}

int	expand_str(t_object *obj, char **str)
{
	t_string		new;
	t_string		ptr;

	new = NULL;
	while (**str != '\0')
	{
		if (set_next_part(obj, str, &ptr) == FAILURE)
			return (FAILURE);
		if (isnull(ptr))
			continue ;
		new = ft_strjoin_free(new, ptr, BOTH);
		if (isnull(new))
			return (FAILURE);
	}
	*str = new;
	return (SUCCESS);
}

int	expand(t_object *obj, t_token *token)
{
	t_string			original;

	if (obj->tokens && get_last_token(obj->tokens)->type == HEREDOC)
		return (SUCCESS);
	original = token->content;
	if (expand_str(obj, &token->content) == FAILURE)
		return (FAILURE);
	if (is_quoted(token) && token->content == NULL)
	{
		token->content = ft_strdup("");
		if (isnull(token->content))
			return (FAILURE);
	}
	free(original);
	return (SUCCESS);
}
