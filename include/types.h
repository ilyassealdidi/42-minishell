/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/08 15:20:41 by ialdidi          ###   ########.fr       */
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
	char			*content;
	bool			is_joinable;
	bool			is_expandable;
	bool			is_quoted;
	t_token_type	type;
}	t_token;

typedef struct s_redir
{
	int				fd;	
	char			*file;
	t_token_type	type;
}				t_redir;

typedef struct s_command
{
	char			*cmd;
	char			**args;
	t_list			*redirs;
}	t_command;

typedef struct s_dictionnary
{
	char			*key;
	char			*value;
}	t_dictionnary;

typedef struct s_object
{
	char			*line;
	t_list			*tokens;
	t_list			*commands;
	t_list			*env;
	int				exit_status;
	int				received_signals;
}	t_object;

#endif
