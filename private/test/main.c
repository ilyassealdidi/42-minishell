/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/09/15 13:21:45 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>


int	main(int ac, char **av)
{
	char	str[100];

	int fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	int fd2 = open("heredoc", O_RDONLY, 0644);
	unlink("heredoc");


	write(fd, "hello", 5);

	read(fd2, str, 5);
	printf("%s\n", str);
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
