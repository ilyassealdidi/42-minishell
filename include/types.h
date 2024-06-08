/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/06 02:07:17 by ialdidi          ###   ########.fr       */
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

# define END_OF_LINE 8

# define VALID 1
# define INVALID 0

# define MEMORY_ERR "Failed to allocate memory\n"
# define SYNTAX_ERR "Syntax error\n"
# define CMD_NOT_FOUND "Command not found\n"

typedef enum e_token_type
{
	NONE,
	CMD,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}	t_token_type;

typedef struct s_token
{
	char			*content;
	bool			is_joinable;
	bool			is_expandable;
	t_token_type	type;
}	t_token;

typedef struct s_object
{
	t_list	*tokens;
	int		exit_status;
}	t_object;

#endif
