/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:21 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/19 14:09:41 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <exec.h>
# include <parse.h>

extern int		g_received_signal;

/*		Errors Management		*/
void			ft_error(char *location, char *cause, char *error);

/*		Utilities				*/
char			*ft_strjoin_free(char *s1, char *s2, int to_free);
int				is_valid_syntax(t_list *tokens);
void			free_array(char **strs);
bool			isnull(void *ptr);
bool			isset(void *ptr);
bool			isbuiltin(char *str);

#endif
