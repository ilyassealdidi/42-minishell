/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:45:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/22 12:42:28 by ialdidi          ###   ########.fr       */
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
			ft_printf("declare -x %s", env->element.key);
			if (env->element.value != NULL)
				ft_printf("=\"%s\"", env->element.value);
			ft_printf("\n");
			i++;
		}
		node = node->next;
		if (isnull(node))
			node = head;
	}
}

static bool	is_valid_identifier(char *str)
{
	int				i;

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

//update the function's name
static int	set_dict(t_dictionnary *dict, char *env, char *equal)
{
	if (isnull(equal))
	{
		dict->key = ft_strdup(env);
		if (isnull(dict->key))
			return (FAILURE);
		dict->value = NULL;
	}
	else
	{
		dict->key = ft_substr(env, 0, equal - (equal[-1] == '+') - env);
		dict->value = ft_strdup(ft_strchr(env, '=') + 1);
		if (isnull(dict->key) || isnull(dict->value))
			return (destroy_dictionnary(dict), FAILURE);
	}
	return (SUCCESS);
}

static int	export_env(t_object *obj, char *arg)
{
	t_dictionnary	dict;
	char			*equal;
	int				status;

	equal = ft_strchr(arg, '=');
	if (set_dict(&dict, arg, equal) == FAILURE)
		return (FAILURE);
	if (equal != NULL && equal[-1] == '+')
		status = append_env(&obj->env, dict);
	else
		status = set_env(&obj->env, dict);
	destroy_dictionnary(&dict);
	return (status);
}

int	builtin_export(t_object *obj, t_command *cmd)
{
	int				i;
	int				status;

	i = 1;
	status = SUCCESS;
	if (cmd->argc == 1)
		return (print_env(obj->env), status);
	while (cmd->argv[i])
	{
		if (is_valid_identifier(cmd->argv[i]) == INVALID)
		{
			status = FAILURE;
			ft_error(B_EXPORT, cmd->argv[i], EMNVI);
		}
		else
		{
			status = export_env(obj, cmd->argv[i]);
			if (status == FAILURE)
				break ;
		}
		i++;
	}
	return (status);
}
