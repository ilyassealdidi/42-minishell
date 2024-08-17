/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/16 21:01:03 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define UKN "\033[1;30m"
# define WHITE "\033[1;97m"
# define RESET "\033[0m"

# define TRUE GREEN"true"RESET
# define FALSE RED"false"RESET

# define SUCCESS 0
# define FAILURE 1
# define ERROR 258

# define JOINABLE 0b00000001
# define EXPANDABLE 0b00000010
# define QUOTED 0b00000100

# define VALID 1
# define INVALID 0

# define MEMORY_ERR "3ata failat malloc\n"
# define SYNTAX_ERR "Syntax error\n"
# define CMD_NOT_FOUND "Command not found\n"
# define AMBIGUOUS_REDIRECT "minishell: %s: ambiguous redirect\n"

typedef enum e_token_type
{
	NONE,
	CMD,
	BUILTIN,
	ARG,
	PIPE,
	DELIMITER,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	INFILE,
	OUTFILE,
}	t_token_type;

typedef struct s_token
{
	char			*content;
	int				state;
	bool			is_joinable;
	bool			is_expandable;
	bool			is_quoted;
	t_token_type	type;
}	t_token;

typedef struct s_cmd_type
{
	// char			*cmd;
	// int				(*func)(t_object *obj, t_list *node);
	// t_token_type	type;
	
}	t_cmd_type;

typedef struct s_command
{
	char			*cmd;
	char			**args;
	int				in;
	int				out;
}	t_command;

typedef struct s_dictionnary
{
	char			*key;
	char			*value;
}	t_dictionnary;

// typedef struct s_env
// {
// 	t_dictionnary	*element;
// 	bool			is_hidden;
// }	t_env;

typedef struct s_object
{
	char			*line;
	t_list			*tokens;	// To be removed later
	t_list			*commands;
	t_list			*env;
	int				exit_status;
	int				received_signals;
}	t_object;

#endif
