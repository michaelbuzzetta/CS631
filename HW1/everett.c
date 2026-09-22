#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int option;
    char *word = "World";
    int count = 1;
    
    while ((option = getopt(argc, argv, "hn:w:")) !=-1) {
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
        
    return EXIT_SUCCESS;
}