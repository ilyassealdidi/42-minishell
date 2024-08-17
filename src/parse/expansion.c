/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:19:55 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/17 16:12:39 by ialdidi          ###   ########.fr       */
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
	int		is_var;
	char	*variable;
	char	*value;

	is_var = set_part_len(*str, &len);
	if (!is_var)
		*ptr = ft_substr(*str, 0, len);
	else
	{
		variable = ft_substr(*str, 1, len);
		if (variable == NULL)
			return (FAILURE);
		value = get_env(obj, variable);
		free(variable);
		if (value != NULL)
			*ptr = ft_strdup(value);
		else
			*ptr = NULL;
	}
	*str += len + (is_var);
	if (*ptr == NULL && (!is_var || is_var && value != NULL))
		return (FAILURE);
	return (SUCCESS);
}

int	expand_vars(t_object *obj, t_token *token)
{
	char	*new;
	char	*old;
	char	*ptr;

	if (!is_expandable(token)
		|| obj->tokens && get_last_token(obj->tokens)->type == HEREDOC)
		return (SUCCESS);
	new = NULL;
	old = token->content;
	while (*token->content != '\0')
	{
		if (set_next_part(obj, &token->content, &ptr) == FAILURE)
			return (FAILURE);
		if (ptr == NULL)
			continue ;
		new = join(new, ptr);
		if (new == NULL)
			return (FAILURE);
	}
	free(old);
	token->content = new;
	if (token->content == NULL && is_expandable(token))
		return (token->content = ft_strdup(""), token->content == NULL);
	return (SUCCESS);
}
