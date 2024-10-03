/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:19:55 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/28 20:39:45 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_part_len(t_string str, int *len)
{
	if (*str == '$' && isnull(ft_strchr(" |><'\"\t", str[1])))
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
		value = get_env_value(obj->env, variable);
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

int	expand_var(t_object *obj, char **dest, char *src)
{
	t_string		new;
	t_string		ptr;

	new = NULL;
	ptr = get_env_value(obj->env, src);
	if (ptr != NULL)
	{
		new = ft_strdup(ptr);
		if (isnull(new))
			return (FAILURE);
	}
	*dest = new;
	return (SUCCESS);
}

int	expand_str(t_object *obj, char **dest, char *src)
{
	t_string		new;
	t_string		ptr;

	new = NULL;
	while (*src != '\0')
	{
		if (set_next_part(obj, &src, &ptr) == FAILURE)
			return (FAILURE);
		if (isnull(ptr))
			continue ;
		new = ft_strjoin_free(new, ptr, BOTH);
		if (isnull(new))
			return (FAILURE);
	}
	*dest = new;
	return (SUCCESS);
}

int	expand(t_object *obj, t_token *token)
{
	t_string		expanded;

	if (!is_expandable(token)
		|| (isset(obj->tokens) && get_last_token(obj->tokens)->type == HEREDOC))
		return (SUCCESS);
	if (!is_quoted(token))
	{
		if (expand_var(obj, &expanded, token->content + 1) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (expand_str(obj, &expanded, token->content) == FAILURE)
			return (FAILURE);
		expanded = ft_strjoin_free(expanded, "", LEFT);
		if (isnull(expanded))
			return (FAILURE);
	}
	free(token->content);
	token->content = expanded;
	return (SUCCESS);
}
