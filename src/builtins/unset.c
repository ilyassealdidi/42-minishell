/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:30:50 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/22 12:47:14 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	is_valid_identifier(char *str)
{
	int				i;

	if (!ft_isalpha(*str) && *str != '_')
		return (INVALID);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (INVALID);
		i++;
	}
	return (VALID);
}

int	builtin_unset(t_object *obj, t_command *command)
{
	int				i;
	int				status;

	i = 1;
	status = SUCCESS;
	while (command->argv[i])
	{
		if (is_valid_identifier(command->argv[i]) == INVALID)
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: `%s': %s\n",
				EMBASE, B_UNSET, command->argv[i], EMNVI);
			status = FAILURE;
		}
		else
			unset_env(&obj->env, command->argv[i]);
		i++;
	}
	return (status);
}
