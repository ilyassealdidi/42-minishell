/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/09 21:42:37 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>


#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(int ac, char **av)
{
  errno = ENOMEM;
  perror(NULL);
  return 0;
}
