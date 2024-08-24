/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:45:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/24 16:26:17 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_env(t_list *head)
{
	t_list			*node;
	t_environment	*env;
	int				list_size;
	int				i;

	i = 1;
	list_size = ft_lstsize(head) - 1;
	node = head;
	while (i <= list_size)
	{
		env = node->content;
		if (env->hidden == false && env->index == i)
		{
			printf("%d declare -x %s", env->index, env->element.key);
			if (env->element.value != NULL)
				printf("=\"%s\"", env->element.value);
			printf("\n");
			i++;
		}
		node = node->next;
		if (node == NULL)
			node = head;
	}
}

static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!ft_isalpha(*str) && *str != '_')
		return (INVALID);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=' || ft_strncmp(&str[i], "+=", 2) == 0)
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (INVALID);
		i++;
	}
	return (VALID);
}

static int	set_dict(t_dictionnary *dict, char *env, char *equal) //update the function's name
{
	if (equal == NULL)
	{
		dict->key = ft_strdup(env);
		if (dict->key == NULL)
			return (FAILURE);
		dict->value = NULL;
	}
	else
	{
		dict->key = ft_substr(env, 0, equal - (equal[-1] == '+') - env);
		dict->value = ft_strdup(ft_strchr(env, '=') + 1);
		if (dict->key == NULL || dict->value == NULL)
			return (destroy_dictionnary(dict), FAILURE);
	}
	return (SUCCESS);
}

static int	export_env(t_object *obj, char *arg)
{
	t_dictionnary	dict;
	char			*equal;

	equal = ft_strchr(arg, '=');
	if (set_dict(&dict, arg, equal) == FAILURE)
		return (FAILURE);
	if (equal != NULL && equal[-1] == '+' && append_env(&obj->env, dict) == FAILURE)
			return (destroy_dictionnary(&dict), FAILURE);
	else if (set_env(&obj->env, dict) == FAILURE)
			return (destroy_dictionnary(&dict), FAILURE);
	destroy_dictionnary(&dict);
	return (SUCCESS);
}

int	builtin_export(t_object *obj, t_command *cmd)
{
	int				i;

	i = 0;
	if (cmd->argc == 1)
		return (print_env(obj->env), SUCCESS);
	while (cmd->args[++i])
	{
		if (is_valid_identifier(cmd->args[i]) == INVALID)
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			obj->exit_status = 1;
			continue ;
		}
		if (export_env(obj, cmd->args[i]) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
