/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/04 12:46:51 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

# define END_OF_LINE 8

# define VALID 1
# define INVALID 0

# define MEMORY_ERR "Failed to allocate memory\n"
# define SYNTAX_ERR "Syntax error\n"

typedef enum e_token_type
{
	NONE,
	SPACE,
	QUOTED,
	TEXT,
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
	t_token_type	type;
}	t_token;

typedef struct s_object
{
	t_list	*tokens;
}	t_object;

#endif
