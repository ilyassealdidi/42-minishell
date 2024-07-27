/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionnary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:11:56 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/27 01:42:43 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_dictionnary	*create_element(char *key, char *value)
{
	t_dictionnary	*element;

	element = (t_dictionnary *)malloc(sizeof(t_dictionnary));
	if (element == NULL)
		return (NULL);
	element->key = key;
	element->value = value;
	return (element);
}
