/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:21 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/17 16:14:12 by ialdidi          ###   ########.fr       */
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

extern int	g_received_signal;
// Consider to use seperate header files, one for parsing, one for executing

/*		Errors Management		*/
void			print_error(int status);

/*		Utilities				*/
char			*join(char *str1, char *str2);
int				is_valid_syntax(t_list *tokens);
void			free_array(char **strs);

/*		Tokens utils			*/
t_token			*get_token(t_list *list);
t_token			*get_first_token(t_list *list);
t_token			*get_last_token(t_list *list);

bool			is_quoted(t_token *token);
bool			is_expandable(t_token *token);
bool			is_joinable(t_token *token);

int				ft_appendtoken(t_object *obj, t_token *token);
void			update_token_type(t_list *head, t_token *new);
void			destroy_token(void *content);
int				tokens_init(t_object *obj, char *line);


/*		Expanding	*/
int				expand_vars(t_object *obj, t_token *token);

/*		Parsing			*/
int				generate_commands(t_object *obj);

/*		Dictionnary		*/
t_dictionnary	*create_element(char *key, char *value);

/*		Envirement		*/
int				init_env(t_object *obj, char **env);
char			*get_env(t_object *obj, char *key);
int				set_env(t_object *obj, char *key, char *value);

/*		Signals			*/
void			init_signals(void);
void			exit_shell(t_object *obj);

/*		TO BE REMOVED	*/
void			print_content(void *content);
void			display_token(void *content);
void			leaks_func(void);
void			display_command(void *content);
void			print_env(void *content);

/*		Command			*/
int				new_command(t_list *tokens, t_command *command);
void			destroy_command(void *content);
int				commands_init(t_object *obj);

void			update_exit_status(t_object *obj);

void			exec(t_object *obj);

#endif
