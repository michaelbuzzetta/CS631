#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int option;
    char *word = "World";
    
    while ((option = getopt(argc, argv, "hw:")) !=-1) {
        switch (option) {
        case 'h':
            printf("usage: everett [-h] [-n num] [-w word]\n");
            break;
        case 'w':
            word = optarg;
            break;
        default:
            return EXIT_FAILURE;
        }
    }

    printf ("Hеllo, %s!\n", word);
}