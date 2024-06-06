#include <stdlib.h>
#include <stdio.h>

int main()
{
	if (getenv("XYZ") == NULL)
		printf("(null)\n");
}
