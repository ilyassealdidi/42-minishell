/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:19:55 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/06 17:34:10 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expand_vars(t_token *token, int exit_status)
{
	char	*ptr;
	char	*var;
	char	*value;
	char	*dollar_sign;

	ptr = "";
	// echo "$HOME $USER $PWD $?"
	// echo "$HOME$USER"
	// echo "$HOME$USER$"
	while (1)
	{
		dollar_sign = ft_strchr(token->content, '$');
		if (dollar_sign != NULL)
		{	
			dollar_sign++;
			if (*dollar_sign == '?')
			{
				dollar_sign++;
				var = ft_itoa(exit_status); 
				if (var == NULL)
					return (FAILURE);
			}
			else if (ft_isalpha(*dollar_sign))
			{
				var = ft_substr(dollar_sign, 0, ft_strcspn(dollar_sign, " $"));
				if (var == NULL)
					return (FAILURE);
				value = getenv(var);
				free(var);		
			}
		}
	}
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
			expand_vars(token, obj->exit_status);
		node = node->next;
	}
}
