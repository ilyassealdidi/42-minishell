/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:49:41 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/03 21:56:55 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	join_path(char **paths, t_command *command)
{
	int		i;
	char	*ptr;
	int		path_len;
	int		cmd_len;

	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(paths[i]);
		cmd_len = ft_strlen(command->argv[0]);
		ptr = ft_calloc(path_len + cmd_len + 2, sizeof(char));
		if (ptr == NULL)
			return (FAILURE);
		ft_strlcat(ptr, paths[i], path_len + 1);
		ft_strlcat(ptr, "/", path_len + 2);
		ft_strlcat(ptr, command->argv[0], path_len + cmd_len + 2);
		if (access(ptr, X_OK) == 0)
			return (free(command->argv[0]), command->argv[0] = ptr,  SUCCESS);
		free(ptr);
		i++;
	}
	return (SUCCESS);
}

static int	set_cmd_path(t_object *obj, t_command *command)
{
	char	**paths;
	char	*ptr;

	if (ft_strchr("/", **command->argv))
		return (SUCCESS);
	ptr = get_env(obj->env, "PATH");
	if (ptr == NULL)
		return (SUCCESS);
	paths = ft_split(ptr, ':');
	if (paths == NULL)
		return (FAILURE);
	if (*paths == NULL)
		return (free(paths), SUCCESS);
	if (join_path(paths, command) == FAILURE)
		return (free_array(paths), FAILURE);
	free_array(paths);
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
		command = new_command(obj, tokens);
		if (command == NULL)
			return (FAILURE);
		if (command->argc != 0 && !command->is_builtin
			&& set_cmd_path(obj, command) == FAILURE)
			return (destroy_command(command), FAILURE);
		if (command->argc > 0)
			command->cmd = command->argv[0];
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
