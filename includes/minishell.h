/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:21 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/04 12:46:44 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <types.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# define is_sep is_separator

// Consider to use seperate header files, one for parsing, one for executing

/*		Errors Management		*/
void	print_error(char *str);

/*		Utilities		*/
char			*join(char *str1, char *str2);
int				is_valid_syntax(t_list *tokens);
t_token_type	is_separator(char	*str);

/*		Tokens utils	*/
int				ft_appendtoken(t_list **head, t_token *token);
void			free_token(void *content);

/*		Tokenization	*/
int				tokens_init(t_object *obj, char *line);

/*		Barsing			*/
int 			parse(char *line, t_object *obj);

/*		tskrt			*/
void print_content(void *content);
void func();

#endif
