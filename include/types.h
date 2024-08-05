/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/05 07:18:35 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define YELLOW "\033[0;33m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define WHITE "\033[1;97m"
# define RESET "\033[0m"

# define TRUE GREEN"true"RESET
# define FALSE RED"false"RESET

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

# define VALID 1
# define INVALID 0

# define MEMORY_ERR "Failed to allocate memory\n"
# define SYNTAX_ERR "Syntax error\n"
# define CMD_NOT_FOUND "Command not found\n"
# define AMBIGUOUS_REDIRECT "minishell: %s: ambiguous redirect\n"

typedef enum e_token_type
{
	NONE,
	CMD,
	BUILTIN,
	ARG,
	DELIMITER,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	OUTFILE,
}	t_token_type;

typedef struct s_token
{
	char			*original;
	char			*content;
	bool			is_joinable;
	bool			is_expandable;
	bool			is_quoted;
	t_token_type	type;
}	t_token;

// typedef struct s_token
// {
// 	char			*original;
// 	char			*content;
// 	t_token_type	type;
// 	t_list			*parts;
// }	t_token;

// typedef struct s_part
// {
// 	char			*content;
// 	bool			is_joinable;
// 	bool			is_expandable;
// 	bool			is_quoted;
// 	t_token			*container;
// }	t_part;

typedef struct s_command
{
	char			*cmd;	// think about changing to t_token
	char			**args; // think about changing to t_token
	int				in;
	int				out;
}	t_command;

typedef struct s_dictionnary
{
	char			*key;
	char			*value;
}	t_dictionnary;

typedef struct s_object
{
	char			*line;
	int				num_of_cmds;
	t_list			*tokens;
	t_list			*commands;
	t_list			*env;
	int				exit_status;
}	t_object;

#endif
