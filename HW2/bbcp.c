#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s source target\n", argv[0]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}