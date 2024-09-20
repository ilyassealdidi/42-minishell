/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/20 18:55:39 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define SUCCESS 0
# define FAILURE 1
# define ERROR 258

# define JOINABLE 0b00000001
# define EXPANDABLE 0b00000010
# define QUOTED 0b00000100

# define LEFT 0
# define RIGHT 1
# define BOTH 2

# define VALID 1
# define INVALID 0

# define SUCCESS_PROMPT "\033[0;32m➜\033[0m "
# define FAILURE_PROMPT "\033[0;31m➜\033[0m "

# define B_EXIT "exit"
# define B_ECHO "echo"
# define B_CD "cd"
# define B_PWD "pwd"
# define B_EXPORT "export"
# define B_UNSET "unset"
# define B_ENV "env"

# define EMBASE "minishell"
# define EMNVI "not a valid identifier"
# define EMHNS "HOME not set"
# define EMNAR "numeric argument required"
# define EMTMA "too many arguments"
# define EMRCD "error retrieving current directory"
# define EMCNF "command not found"
# define EMISDIR "is a directory"
# define EMSYNTAX "syntax error"
# define EMAMBR "ambiguous redirect"

//FDS
# define NOTHING -1
# define PIN 0
# define POUT 1
//
# define CHILD 0

//ERRORS
# define FAILED -1
# define ECMDNTFND 127

typedef char*	t_string;

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
	FILENAME
}	t_token_type;

typedef struct s_token
{
	char			*content;
	unsigned int	state;
	t_token_type	type;
}	t_token;

typedef struct s_command
{
	int				in;
	int				out;
	int				argc;
	int				pfd[2];
	pid_t			pid;
	char			*cmd;
	char			**argv;
	char			**envp;
}	t_command;

typedef struct s_dictionnary
{
	char			*key;
	char			*value;
}	t_dictionnary;

typedef struct s_environment
{
	t_dictionnary	element;
	bool			hidden;
	int				index;
}	t_environment;

typedef struct s_object
{
	t_list			*tokens;
	t_list			*commands;
	t_list			*env;
	int				exit_status;
	int				received_signals;
}	t_object;

#endif
