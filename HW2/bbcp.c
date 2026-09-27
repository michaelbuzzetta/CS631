#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#define BUFSIZE 4096

int main(int argc, char *argv[])
{
    int source;
    int destination;
    struct stat source_stat;
    struct stat target_stat;
    char target[PATH_MAX];
    char *filename;
    char buffer[BUFSIZE];
    ssize_t bytes_read;
    ssize_t bytes_written;
    ssize_t total_written;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s source target\n", argv[0]);
        return EXIT_FAILURE;
    }

    source = open(argv[1], O_RDONLY);
    if (source == -1)
    {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    if (fstat(source, &source_stat) == -1)
    {
        perror(argv[1]);
        close(source);
        return EXIT_FAILURE;
    }

    if (S_ISDIR(source_stat.st_mode))
    {
        fprintf(stderr, "%s is a directory\n", argv[1]);
        close(source);
        return EXIT_FAILURE;
    }

    if (source_stat.st_uid == 0)
    {
        close(source);
        return EXIT_FAILURE;
    }

    if (snprintf(target, sizeof(target), "%s", argv[2]) < 0)
    {
        close(source);
        return EXIT_FAILURE;
    }

    if (stat(argv[2], &target_stat) == 0 &&
        S_ISDIR(target_stat.st_mode))
    {
        filename = strrchr(argv[1], '/');

        if (filename == NULL)
            filename = argv[1];
        else
            filename++;

        if (snprintf(target, sizeof(target), "%s/%s",
                     argv[2], filename) < 0)
        {
            close(source);
            return EXIT_FAILURE;
        }
    }

    destination = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (destination == -1)
    {
        perror(target);
        close(source);
        return EXIT_FAILURE;
    }

    while ((bytes_read = read(source, buffer, sizeof(buffer))) > 0)
    {
        total_written = 0;

        while (total_written < bytes_read)
        {
            bytes_written = write(destination,
                                  buffer + total_written,
                                  bytes_read - total_written);

            if (bytes_written == -1)
            {
                perror(target);
                close(source);
                close(destination);
                return EXIT_FAILURE;
            }

            total_written += bytes_written;
        }
    }

    if (bytes_read == -1)
    {
        perror(argv[1]);
        close(source);
        close(destination);
        return EXIT_FAILURE;
    }

    if (close(source) == -1)
    {
        perror(argv[1]);
        close(destination);
        return EXIT_FAILURE;
    }

    if (close(destination) == -1)
    {
        perror(target);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}