#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void 		print(char *s)
{
	write(1, s, strlen(s));
}

int 		main()
{
	char 	*addr;
	char 	*addr3;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjour\n");
	return (0);
}
