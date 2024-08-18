/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionnary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:48:18 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/18 11:49:11 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	destroy_dictionnary(void *content)
{
	t_dictionnary	*dict;

	dict = (t_dictionnary *)content;
	free(dict->key);
	free(dict->value);
}
