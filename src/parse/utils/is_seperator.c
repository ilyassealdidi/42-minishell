/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_seperator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:25:13 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/31 18:54:05 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token_type	is_separator(char	*str)
{
	static char	*seps[] = {"|", ">>", "<<", ">", "<", NULL};
	static int	values[] = {PIPE, APPEND, HEREDOC, REDIR_OUT, REDIR_IN, -1};
	int			i;

	i = -1;
	while (seps[++i] != NULL)
		if (ft_strncmp(str, seps[i], strlen(seps[i])) == 0)
			return (values[i]);
	return (-1);
}
