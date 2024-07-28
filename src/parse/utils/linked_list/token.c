/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 08:47:03 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/28 12:30:33 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*get_first_token(t_list *list)
{
	if (list == NULL)
		return (NULL);
	return ((t_token *)list->content);
}

t_token	*get_last_token(t_list *list)
{
	if (list == NULL)
		return (NULL);
	return ((t_token *)(ft_lstlast(list)->content));
}

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->content);
	free(token);
}

static bool	is_built_in(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len == 4 && ft_strncmp(str, "echo", 4) == 0)
		return (true);
	if (len == 2 && ft_strncmp(str, "cd", 2) == 0)
		return (true);
	if (len == 3 && ft_strncmp(str, "pwd", 3) == 0)
		return (true);
	if (len == 6 && ft_strncmp(str, "export", 6) == 0)
		return (true);
	if (len == 5 && ft_strncmp(str, "unset", 5) == 0)
		return (true);
	if (len == 3 && ft_strncmp(str, "env", 3) == 0)
		return (true);
	if (len == 4 && ft_strncmp(str, "exit", 4) == 0)
		return (true);
	return (false);
}

static bool	does_cmd_exits(t_list *head)
{
	t_token	*last;
	t_list	*tmp;

	tmp = head;
	while (tmp)
	{
		last = get_last_token(tmp);
		if (last == NULL)
			return (false);
		if (last->type == CMD || last->type == BUILTIN)
			return (true);
		if (last->type == PIPE)
			return (false);
		tmp = tmp->previous;
	}
	return (false);
}

void	update_token_type(t_list *head, t_token *new)
{
	t_token	*last;

	last = get_last_token(head);
	if (head != NULL && (last->type == REDIR_OUT || last->type == APPEND))
		new->type = FFILE;
	else if (is_built_in(new->content) && does_cmd_exits(head) == false)
		new->type = BUILTIN;
	else if (new->type == ARG && does_cmd_exits(head) == false)
		new->type = CMD;
	else if ((head == NULL || last->type == PIPE) && new->type == ARG)
		new->type = CMD;
	else if (head != NULL && last->type == HEREDOC)
		new->type = DELIMITER;
}
