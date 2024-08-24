/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:49:41 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/24 16:25:30 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*dict_toenv(t_dictionnary *dict)
{
	char	*key;
	char	*env;

	key = ft_strjoin(dict->key, "=");
	if (key == NULL)
		return (NULL);
	env = ft_strjoin_free(key, dict->value, LEFT);
	if (env == NULL)
		return (free(key), NULL);
	return (env);
}

static int	set_envp(t_list *list, t_command *command)
{
	int				i;
	int				count;
	t_environment	*env;

	count = ft_lstsize(list);
	command->envp = malloc(sizeof(char *) * (count + 1));
	if (command->envp == NULL)
		return (FAILURE);
	command->envp[count] = NULL;
	i = 0;
	while (list)
	{
		env = list->content;
		if (env->hidden == false)
		{
			command->envp[i] = dict_toenv(&env->element);
			if (command->envp[i] == NULL)
				return (free_array(command->envp), FAILURE);
			i++;
		}
		list = list->next;
	}
	return (SUCCESS);		
}

int	commands_init(t_object *obj)
{
	t_command	*command;
	t_list		*tokens;
	t_list		*new;

	tokens = obj->tokens;
	while (tokens)
	{
		command = malloc(sizeof(t_command));
		if (command == NULL)
			return (FAILURE);
		ft_memset(command, 0, sizeof(t_command));
		if (new_command(tokens, command) == FAILURE)
			return (FAILURE);
		if (set_envp(obj->env, command) == FAILURE)
			return (destroy_command(command), FAILURE);
		new = ft_lstnew(command);
		if (new == NULL)
			return (destroy_command(command), FAILURE);
		ft_lstadd_back(&obj->commands, new);
		while (tokens && get_token(tokens)->type != PIPE)
			tokens = tokens->next;
		if (tokens && get_token(tokens)->type == PIPE)
			tokens = tokens->next;
	}
	return (SUCCESS); 
}
