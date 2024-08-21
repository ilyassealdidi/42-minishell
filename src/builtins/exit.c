/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:35:37 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/21 22:52:28 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

long	ft_atol(const char *str)
{
	size_t	num;
	int		sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = 1 - 2 * (*str++ == '-');
	while (ft_isdigit(*str))
	{
		if (num >= LONG_MAX / 10) 
		{
			if (((num == LONG_MAX / 10 && *str - '0' > 7)
					|| num > LONG_MAX / 10) && sign == -1)
				return (errno = ERANGE, LONG_MIN);
			if (((num == LONG_MAX / 10 && *str - '0' <= 7)
					|| num > LONG_MAX / 10) && sign == 1)
				return (errno = ERANGE, LONG_MAX);
		}
		num = num * 10 + *str++ - '0';
	}
	if (*str && !ft_isdigit(*str))
		errno = EINVAL;
	return (num * sign);
}

void	print_exit_error(char *arg)
{
	if (errno == ERANGE || errno == EINVAL)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	else
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
}

int	builtin_exit(t_object *obj, t_command *command)
{
	unsigned char	nb;
	char			*value;

	nb = 0;
	// ft_lstclear(&obj->env, destroy_env);
	// ft_lstclear(&obj->commands, destroy_command);
	printf("exit\n");
	if (command->args_count >= 2)
	{
		value = ft_strtrim(command->args[1], " \t");
		if (!value)
			return (obj->exit_status = 1, FAILURE);
		errno = 0;
		nb = ft_atol(value);
		if (errno == ERANGE || errno == EINVAL)
		{
			print_exit_error(command->args[1]);
			exit(255);
		}
		if (command->args_count > 2)
			return (print_exit_error(NULL), obj->exit_status = 1, SUCCESS);
	}
	exit(nb);
}
