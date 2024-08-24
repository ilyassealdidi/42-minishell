/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:21 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/24 22:44:56 by ialdidi          ###   ########.fr       */
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
# include <types.h>
# include <fcntl.h>

extern int		g_received_signal;

/*		Errors Management		*/
void			print_error(int status, char *arg);

/*		Utilities				*/
char			*ft_strjoin_free(char *s1, char *s2, int to_free);
char			*join(char *str1, char *str2);				//! to be removed
int				is_valid_syntax(t_list *tokens);
void			free_array(char **strs);
bool			is_builtin(char *str);

/*		Token utils				*/
t_token			*get_token(t_list *list);
t_token			*get_last_token(t_list *list);

bool			is_quoted(t_token *token);
bool			is_expandable(t_token *token);
bool			is_joinable(t_token *token);

void			set_token_state(t_token *token, int flag, bool value);
int				ft_appendtoken(t_object *obj, t_token *token);
void			update_token(t_list *head, t_token *new);
void			destroy_token(void *content);
int				tokens_init(t_object *obj, char *line);

/*		Expanding				*/
int				expand_vars(t_object *obj, t_token *token);

/*		Parsing					*/
int				generate_commands(t_object *obj);

/*		Dictionnary				*/
void			destroy_dictionnary(void *content);
t_environment	*create_env(t_dictionnary dict, bool hidden);

/*		Environment				*/
char			*get_env(t_list *env, char *key);
int				insert_env(t_list **env_list, t_dictionnary dict, bool hidden);
int 			append_env(t_list **env_list, t_dictionnary dict);
int				set_env(t_list **env_list, t_dictionnary dict);
int				unset_env(t_list **env_list, char *key);
void			destroy_env(void *content);
int				init_env(t_list **env, char **envp);

/*		Signals	Mangement		*/
void			init_signals(void);
void			exit_shell(t_object *obj);

/*		TO BE REMOVED			*/
void			print_content(void *content);
void			display_token(void *content);
void			leaks_func(void);
void			display_command(void *content);

/*		Builtins				*/
int				builtin_echo(t_command *cmd);
int				builtin_cd(t_object *obj, t_command *cmd);
int				builtin_pwd(t_object *obj);
int				builtin_export(t_object *obj, t_command *cmd);
int				builtin_unset(t_object *obj, t_command *cmd);
int				builtin_env(t_object *obj);
int				builtin_exit(t_object *obj, t_command *command);

/*		Command					*/
int				new_command(t_object *obj, t_list *tokens, t_command *command);
void			destroy_command(void *content);
char			**generate_envp(t_list *list);
int				commands_init(t_object *obj);

/*		Exit status				*/
int				update_exit_status(t_object *obj);
int				set_exit_status(t_object *obj);

void			exec(t_object *obj);

#endif
