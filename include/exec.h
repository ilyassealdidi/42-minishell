/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:47:25 by aaitelka          #+#    #+#             */
/*   Updated: 2024/09/22 15:32:03 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*		Execution				*/
void				execute_commands(t_object *obj);
int					execute_builtin(t_object *obj, t_list *node);

void				ft_save_fd(int *fd, int src);

void				ft_redirect(t_command *cmd);
void				ft_close_redirections(t_command *cmd);

void				ft_pipe(int fields[2]);
void				ft_pipe_in(t_list *cmds, t_command *pipefd);
void				ft_pipe_out(t_list *cmds, t_command *cmd);

pid_t				ft_fork(void);
void				ft_wait(t_object *obj);

void				ft_dup(int from, int to, int to_close);
void				ft_close(int fd);

bool				has_redirection(int fd);
bool				has_next(t_list *node);
bool				is_child(pid_t pid);
bool				is_parent(pid_t pid);
void				is_directory(char *path);

#endif