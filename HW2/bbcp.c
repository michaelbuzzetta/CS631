#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int source;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s source target\n", argv[0]);
		return EXIT_FAILURE;
	}
    source=open(argv[1], O_RDONLY);
    if(source==-1){
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    if(close(source)==-1){
        perror(argv[1]);
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}