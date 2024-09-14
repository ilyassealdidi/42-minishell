/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:17:19 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/14 22:05:34 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*generate_filename(void)
{
	static int		i;
	char			*number;
	char			*name;

	number = ft_itoa(i);
	if (number == NULL)
		return (i = 0, NULL);
	name = ft_strjoin("/tmp/heredoc_", number);
	free(number);
	if (name == NULL)
		return (i = 0, NULL);
	i++;
	return (name);
}

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_received_signal = 1;
		// g_data.exit_status = 1;
		// g_data.sig = 1;
		// g_data.sigflag = 1;
		rl_replace_line("", 0);
		printf("\n");
		close(0);
	}
}

static int	heredoc(t_object *obj, t_list *node)
{
	t_token			*token;
	int				write_fd;
	int				read_fd;
	char			*line;
	char			*filename;

	token = node->content;
	filename = generate_filename();
	if (filename == NULL)
		return (FAILURE);
	write_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	read_fd = open(filename, O_RDONLY);
	if (read_fd == -1 || write_fd == -1)
	{
		close(read_fd);//!
		free(filename);
		perror(strerror(errno));
		return (FAILURE);
	}
	unlink(filename);
	free(filename);
	while (1)
	{
		// signal(SIGINT, heredoc_signal_handler);
		line = readline("> ");
		// if (line == NULL && /*g_received_signal != obj->received_signals*/)
		// {
		// 	// update_exit_status(obj);
		// 	free(line);
		// 	break ;
		// }
		if (line == NULL || ft_strcmp(line, token->content) == 0)
		{
			free(line);
			break ;
		}
		ft_dprintf(write_fd, "%s\n", line);
		free(line);
	}
	close(write_fd);
	free(token->content);
	token->content = ft_itoa(read_fd); //! malloc ya weldi
	if (token->content == NULL)
		return (close(read_fd), FAILURE);
	token->type = INFILE;
	return (SUCCESS);
}

// static int	heredoc(t_object *obj, t_list *node)
// {
// 	t_token			*token;
// 	int				write_fd;
// 	int				read_fd;
// 	char			*line;
// 	char			*filename;

// 	token = node->content;
// 	filename = generate_filename();
// 	if (filename == NULL)
// 		return (FAILURE);
// 	write_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	read_fd = open(filename, O_RDONLY);
	
// 	if (write_fd == -1)
// 	{
// 		free(filename);
// 		perror(strerror(errno));
// 		return (FAILURE);
// 	}
// 	while (1)
// 	{
// 		// signal(SIGINT, heredoc_signal_handler);
// 		line = readline("> ");
// 		// if (line == NULL && /*g_received_signal != obj->received_signals*/)
// 		// {
// 		// 	// update_exit_status(obj);
// 		// 	free(line);
// 		// 	break ;
// 		// }
// 		if (line == NULL || ft_strcmp(line, token->content) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_dprintf(write_fd, "%s\n", line);
// 		free(line);
// 	}
// 	close(write_fd);
// 	free(token->content);
// 	token->content = filename;
// 	token->type = INFILE;
// 	return (SUCCESS);
// }

int	heredocs_init(t_object *obj)
{
	t_list			*tmp;
	t_token			*token;

	tmp = obj->tokens;
	while (tmp)
	{
		token = tmp->content;
		if (token->type == DELIMITER)
			heredoc(obj, tmp);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
