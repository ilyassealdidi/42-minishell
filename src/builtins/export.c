/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:45:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/19 15:28:47 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_env(void *content)
{
	t_environment	*env;

	env = content;
	if (env->hidden == false)
		printf("declare -x %s=%s\n", env->element.key, env->element.value);
}

static bool	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (INVALID);
	i++;
	while (str[i])
	{
		if (str[i] == '=' || str[i] == '+')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (INVALID);
		i++;
	}
	return (VALID);
}

int	export(t_object *obj, t_command *cmd)
{
	int				i;
	t_dictionnary	dict;

	i = 0;
	if (cmd->args[1] == NULL)
		return (ft_lstiter(obj->env, print_env), SUCCESS);
	while (cmd->args[++i]) // Handle appending to the environment variables
	{
		if (is_valid_identifier(cmd->args[i]) == INVALID)
		{
			obj->exit_status = 1;
			print_error(INVALID_IDENTIFIER, cmd->args[i]);
			continue ;
		}
		if (ft_strchr(cmd->args[i], '=') == NULL)
		{
			dict.key = ft_strdup(cmd->args[i]);
			dict.value = ft_strdup("");
		}
		else
		{
			dict.key = ft_substr(cmd->args[i], 0, ft_strchr(cmd->args[i], '=') - cmd->args[i]);
			dict.value = ft_strdup(ft_strchr(cmd->args[i], '=') + 1);
		}
		if (insert_env(&obj->env, dict, false) == FAILURE)
			return (destroy_dictionnary(&dict), FAILURE);
		destroy_dictionnary(&dict);
	}
	return (SUCCESS);
}
