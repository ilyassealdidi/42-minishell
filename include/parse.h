/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:45:46 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/25 12:51:11 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/*		Tokenization			*/
t_token			*get_token(t_list *list);
t_token			*get_last_token(t_list *list);
bool			is_redir(t_token *token);
bool			is_operator(t_token *token);

bool			is_quoted(t_token *token);
bool			is_expandable(t_token *token);
bool			is_joinable(t_token *token);

void			set_token_state(t_token *token, int flag, bool value);
int				ft_appendtoken(t_object *obj, t_token *token);
void			update_token(t_list *head, t_token *new);
void			destroy_token(void *content);
int				set_token(char **line, t_token *token);
int				tokens_init(t_object *obj, t_string line);

/*		Expanding				*/
int				expand_str(t_object *obj, char **dest, t_string src);
int				expand(t_object *obj, t_token *token);

/*		Parsing					*/
int				generate_commands(t_object *obj);

/*		Environment				*/
char			**generate_envp(t_list *list);
t_dictionnary	*get_env(t_list *env_list, t_string key);
char			*get_env_value(t_list *env, t_string key);
int				insert_env(t_list **env_list, t_dictionnary dict, bool hidden);
int				append_env(t_list **env_list, t_dictionnary dict);
int				set_env(t_list **env_list, t_dictionnary dict);
void			unset_env(t_list **env_list, t_string key);
void			destroy_env(void *content);
int				init_env(t_list **env, char **envp);

/*		Environment utils		*/
void			destroy_dictionnary(void *content);
int				env_size(t_list *env_list);
t_environment	*create_env(t_dictionnary dict, bool hidden);

/*		Builtins				*/
void			builtin_echo(t_command *cmd);
int				builtin_cd(t_object *obj, t_command *cmd);
int				builtin_pwd(t_object *obj);
int				builtin_export(t_object *obj, t_command *cmd);
int				builtin_unset(t_object *obj, t_command *cmd);
void			builtin_env(t_object *obj);
int				builtin_exit(t_object *obj, t_command *command);

/*		Signals	Management		*/
void			init_signals(void);
void			heredoc_interrupt_handler(int sig);
void			exit_shell(t_object *obj);

/*		Redirections			*/
int				redir_init(t_list *node, t_command *command);

/*		Heredoc					*/
int				heredocs_init(t_object *obj);

/*		Command					*/
int				set_command(t_object *obj, t_list *tokens, t_command **command);
t_command		*get_command(t_list *list);
void			destroy_command(void *content);
int				commands_init(t_object *obj);

#endif
