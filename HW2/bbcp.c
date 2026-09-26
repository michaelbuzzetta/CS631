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
    struct stat sb;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s source target\n", argv[0]);
		return EXIT_FAILURE;
	}
    source=open(argv[1], O_RDONLY);
    if(source==-1){
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    if(fstat(source, &sb)==-1){
        perror(argv[1]);
        close(source);
        return EXIT_FAILURE;
    }

    if(S_ISDIR(sb.st_mode)){
        fprintf(stderr, "%s is a directory\n", argv[1]);
        close(source);
        return EXIT_FAILURE;
    }

    if(sb.st_uid==0)
    {
        close(source);
        return EXIT_FAILURE;
    }

    if(close(source)==-1){
        perror(argv[1]);
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}