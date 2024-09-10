/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:35:37 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/10 14:05:18 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static long	get_number(const char *str)
{
	size_t	num;
	int		sign;
	int		i;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = 1 - 2 * (str[i++] == '-');
	while (ft_isdigit(str[i]))
	{
		if (((num == LONG_MAX / 10 && str[i] - '0' > 7)
				|| num > LONG_MAX / 10))
			return (errno = ERANGE, LONG_MAX + (sign == -1));
		num = num * 10 + str[i++] - '0';
	}
	if ((str[i] && !ft_isdigit(str[i]))
		|| (!ft_isdigit(str[i]) && !ft_isdigit(str[i - 1])))
		errno = EINVAL;
	return (num * sign);
}

int	builtin_exit(t_object *obj, t_command *command, bool is_child)
{
	unsigned char	nb;
	char			*value;

	nb = 0;
	// ft_lstclear(&obj->env, destroy_env);
	// ft_lstclear(&obj->commands, destroy_command);
	if (!is_child)
		printf("exit\n");
	if (command->argc >= 2)
	{
		value = ft_strtrim(command->argv[1], " \t");
		if (value == NULL)
			return (obj->exit_status = 1, FAILURE);
		errno = 0;
		nb = get_number(value);
		if (errno != 0)
		{
			ft_error(EXIT, command->argv[1], EMNAR);
			exit(255);
		}
		if (command->argc > 2)
			return (ft_error(EXIT, NULL, EMTMA), obj->exit_status = 1, SUCCESS);
	}
	exit(nb);
}
