/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:19:55 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/19 14:23:35 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_part_len(string str, int *len)
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
	int				len;
	int				is_var;
	string			variable;
	string			value;

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

 //! check leaks
int	expand_str(t_object *obj, char **str)
{
	string			new;
	string			ptr;

	if (**str == '\0')
		return (*str = ft_strdup(""), isnull(*str));
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
	string			original;

	if (obj->tokens && get_last_token(obj->tokens)->type == HEREDOC)
		return (SUCCESS);
	original = token->content;
	if (expand_str(obj, &token->content) == FAILURE)
		return (FAILURE);
	free(original);
	return (SUCCESS);
}
