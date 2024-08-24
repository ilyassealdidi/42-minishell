/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:59:45 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/24 16:12:42 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	free_array(char **strs, int size)
// {
// 	int	i;

// 	if (!strs)
// 		return ;
// 	i = 0;
// 	while (i < size)
// 		free(strs[i++]);
// 	free(strs);
// }

void	free_array(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
}
