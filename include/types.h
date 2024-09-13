/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/03 18:29:41 by aaitelka         ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H



/*		Debug - start		*/
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
/*		Debug - end		*/

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

# define PROMPT "\033[0;32m↪\033[0m "

# define EXIT "exit"
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"

# define EMBASE "minishell"
# define EMNVI "not a valid identifier"
# define EMHNS "HOME not set"
# define EMNAR "numeric argument required"
# define EMTMA "too many arguments"
# define EMRCD "error retrieving current directory"
# define SYNTAX_ERR "syntax error\n"
# define EMCNF "command not found"

//FDS
# define NOTHING -1
# define PIN 0
# define POUT 1
//
# define CHILD 0

//ERRORS
# define FAILED -1
# define ECMDNTFND 127


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
	unsigned 		state;
	t_token_type	type;
}	t_token;

typedef struct s_command
{
	int				in;
	int				out;
	int				argc;
	int				herdoc;
	int				pipefd[2];
	pid_t			pid;
	char			*cmd;
	char			**argv;
	char			**envp;
	bool			has_redir;	//* if has redirection set it to true.
	bool			is_builtin;
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
	// Add the read line by readline here: char *line;
	t_list			*tokens;	//!~ To be removed later
	t_list			*commands;
	t_list			*env;
	int				exit_status;
	int				received_signals;
}	t_object;

#endif
