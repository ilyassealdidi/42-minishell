/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:49:41 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/24 22:59:16 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	is_cmd_exists(char *ptr, char *path, char *cmd)
{
	int		path_len;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	path_len = ft_strlen(path);
	ft_memset(ptr, 0, cmd_len + path_len + 2);
	ft_strlcat(ptr, path, path_len + 1);
	ft_strlcat(ptr, "/", path_len + 2);
	ft_strlcat(ptr, cmd, path_len + cmd_len + 2);
	return (access(ptr, X_OK) == 0);
}

static int	set_cmd_path(t_object *obj, t_command *command)
{
	char	**paths;
	char	*ptr;
	int		i;

	i = 0;
	if (command->cmd[0] == '\0' || command->cmd[0] == '/')
		return (SUCCESS);
	ptr = get_env(obj->env, "PATH");
	if (ptr == NULL)
		return (SUCCESS);
	paths = ft_split(ptr, ':');
	if (paths == NULL)
		return (FAILURE);
	if (*paths == NULL)
		return (free(paths), SUCCESS);
	while (paths[i] != NULL)
	{
		// ptr = ft_calloc(ft_strlen(paths[i]) + ft_strlen(token->content) + 2, sizeof(char));
		ptr = malloc(ft_strlen(paths[i]) + ft_strlen(command->cmd) + 2);
		if (ptr == NULL)
			return (free_array(paths), FAILURE);
		if (is_cmd_exists(ptr, paths[i], command->cmd))
			return (free_array(paths), free(command->cmd),
				command->cmd = ptr, command->argv[0] = ptr, SUCCESS);
		free(ptr);
		i++;
	}
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
		command = ft_calloc(1, sizeof(t_command));
		if (command == NULL)
			return (FAILURE);
		if (new_command(obj, tokens, command) == FAILURE)
			return (destroy_command(command), FAILURE);
		if (command->argc != 0 && !command->is_builtin
			&& set_cmd_path(obj, command) == FAILURE)
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
