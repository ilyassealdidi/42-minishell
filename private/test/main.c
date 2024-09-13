/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/13 12:15:53 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>


#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int func(int a, int b)
{
	return (a + b);
}

int main(int ac, char **av)
{
	int	i;

	printf("%ld\n", func);
	printf("%ld\n", main);
	printf("%ld\n", &i);
	printf("%ld\n", &ac);
	printf("%ld\n", &av);
}


// int main(int ac, char **av)
// {
// 	int fd[2];

// 	pipe(fd);

// 	int id = fork();
// 	if (id == 0)
// 	{
// 		printf("%d\n", fd[0]);
// 		printf("%d\n", fd[1]);
// 		printf("child\n");
// 	}
// 	else
// 	{
// 		printf("%d\n", fd[0]);
// 		printf("%d\n", fd[1]);
// 		wait(NULL);
// 		printf("parent\n");
// 	}
// 	return 0;
// }
