#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int option;
    char *word = "World";
    
    while ((option = getopt(argc, argv, "h")) !=-1) {
        switch (option) {
        case 'h':
            printf("usage: everett [-h] [-n num] [-w word]\n");
            return EXIT_SUCCESS;
        default:
            return EXIT_FAILURE;
        }
    }

    printf ("Hеllo, %s!\n", word);
}