/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:19:55 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/07 20:21:20 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_part_len(char *str, bool is_var)
{
	int	len;

	len = 0;
	if (is_var == true)
	{
		while (ft_isalnum(str[++len]))
			;
		return (len - 1);
	}
	else
		return (ft_strcspn(str, "$") + (*str == '$'));
	
}

static int	next_part(char **str, char **ptr, int exit_status)
{
	char	*tmp;

 	if (**str == '$' && ft_isalpha(*(*str + 1)))
	{
		tmp = ft_substr(*str + 1, 0, get_part_len(*str, true));
		if (tmp == NULL)
			return (FAILURE);
		return (*str += get_part_len(*str, true), *ptr = getenv(tmp),
			free(tmp), SUCCESS);
	}
	else if (**str == '$' && *(*str + 1) == '?')
	{
		*ptr = ft_itoa(exit_status);
		if (*ptr == NULL)
			return (FAILURE);
		return (*str += 2, SUCCESS);
	}
	else
	{
		*ptr = ft_substr(*str, 0, get_part_len(*str, false));
		if (*ptr == NULL) 
			return (FAILURE);
		return (*str += get_part_len(*str, false), SUCCESS);
	}
}

int	expand_vars(t_token *token, int exit_status)
{
	char	*new;
	char	*old;
	char	*ptr;

	if (token->is_expandable == false)
		return (SUCCESS);
	new = NULL;
	old = token->content;
	while (*token->content != '\0')
	{
		if (next_part(&token->content, &ptr, exit_status) == FAILURE)
			return (FAILURE);
		new = join(new, ptr);
		free(ptr);
		if (new == NULL)
			return (FAILURE);
	}
	free(old);
	token->content = new;
	return (SUCCESS);
}
