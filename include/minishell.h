/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:21 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/31 04:59:26 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <types.h>
# include <fcntl.h> 

// Consider to use seperate header files, one for parsing, one for executing

/*		Errors Management		*/
void			print_error(char *str);

/*		Utilities		*/
char			*join(char *str1, char *str2);
int				is_valid_syntax(t_list *tokens);
void			free_array(char **strs);

/*		Tokens utils	*/
int				ft_appendtoken(t_object *obj, t_token *token);
void			update_token_type(t_list *head, t_token *new);
t_token			*get_first_token(t_list *list);
t_token			*get_last_token(t_list *list);
void			free_token(void *content);

/*		Tokenization	*/
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

/*		Signals			*/
void			terminate(int sig);

/*		TO BE REMOVED	*/
void			print_content(void *content);
void			display_token(void *content);
void			leaks_func(void);
void			print_env(void *content);

void			exec(t_object *obj);

#endif
