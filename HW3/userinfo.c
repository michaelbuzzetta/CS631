#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int option;
    int e_flag = 0;
    int n_flag = 0;
    struct passwd *pwd;

    while ((option = getopt(argc, argv, "en")) != -1)
    {
        switch (option)
        {
        case 'e':
            e_flag = 1;
            break;
        case 'n':
            n_flag = 1;
            break;
        default:
            fprintf(stderr, "Usage: %s [-en] user\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (optind != argc - 1)
    {
        fprintf(stderr, "Usage: %s [-en] user\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *user = argv[optind];
    char *end;
    uintmax_t uid;

    pwd = NULL;
    errno = 0;

    if (!n_flag)
    {
        pwd = getpwnam(user);
        if (pwd == NULL && errno != 0)
        {
            if (!e_flag)
                perror("getpwnam");
            return EXIT_FAILURE;
        }
    }

    if (pwd == NULL)
    {
        errno = 0;
        uid = strtoumax(user, &end, 10);

        if (*user != '\0' && *user != '-' && *end == '\0' &&
            errno == 0 && (uintmax_t)(uid_t)uid == uid)
        {
            errno = 0;
            pwd = getpwuid((uid_t)uid);

            if (pwd == NULL && errno != 0)
            {
                if (!e_flag)
                    perror("getpwuid");
                return EXIT_FAILURE;
            }
        }
    }

    if (pwd == NULL)
    {
        if (!e_flag)
        {
            fprintf(stderr, "User '%s' not found\n", user);
        }
        return EXIT_FAILURE;
    }

    if (e_flag)
    {
        return EXIT_SUCCESS;
    }

    printf("Username: %s\n", pwd->pw_name);
    printf("Home directory: %s\n", pwd->pw_dir);
    printf("Login shell: %s\n", pwd->pw_shell);
    printf("Gecos: %s\n", pwd->pw_gecos);
    printf("UID: %ju\n", (uintmax_t)pwd->pw_uid);
    printf("GID: %ju\n", (uintmax_t)pwd->pw_gid);

    return EXIT_SUCCESS;
}
