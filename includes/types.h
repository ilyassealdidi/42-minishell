/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:46:04 by ialdidi           #+#    #+#             */
/*   Updated: 2024/06/01 17:02:13 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

typedef enum e_token_type
{
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
	int				len;
}	t_token;

typedef struct s_object
{
	t_list	*tokens;
}	t_object;

#endif
