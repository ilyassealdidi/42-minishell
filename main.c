#include <libc.h>


int main()
{
	int fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    write(fd, "\f\n\v\n\r", 5);
	return 0;
}