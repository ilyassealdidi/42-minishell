/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/21 22:00:47 by ialdidi          ###   ########.fr       */
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
  char *ptr;
  unsigned char num = atol(av[1]);
  printf("Errno :%d\nNum :%d\n", errno, num);
  return 0;
}
