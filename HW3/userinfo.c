#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int option;
    int e_flag = 0;
    int n_flag = 0;
    struct passwd *pwd;
    struct group *grp;
    gid_t groups[128];
    int found = 128;

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

    printf("login\t%s\n", pwd->pw_name);
    printf("passwd\t%s\n", pwd->pw_passwd);
    printf("uid\t%ju\n", (uintmax_t)pwd->pw_uid);

    if (getgrouplist(pwd->pw_name, pwd->pw_gid, groups, &found) == -1)
    {
        fprintf(stderr, "Too many groups\n");
        return EXIT_FAILURE;
    }

    printf("groups\t");

    for (int i = 0; i < found; i++)
    {
        grp = getgrgid(groups[i]);

        if (grp != NULL)
        {
            printf("%s ", grp->gr_name);
        }
        else
        {
            printf("%ju ", (uintmax_t)groups[i]);
        }
    }

    printf("\n");

    if (pwd->pw_change == 0)
    {
        printf("change\tNEVER\n");
    }
    else
    {
        char *date = ctime(&pwd->pw_change);

        if (date == NULL)
        {
            fprintf(stderr, "Unable to convert change date\n");
            return EXIT_FAILURE;
        }

        printf("change\t%s", date);
    }

    printf("class\t%s\n", pwd->pw_class);
    printf("gecos\t%s\n", pwd->pw_gecos);
    printf("dir\t%s\n", pwd->pw_dir);
    printf("shell\t%s\n", pwd->pw_shell);

    if (pwd->pw_expire == 0)
    {
        printf("expire\tNEVER\n");
    }
    else
    {
        char *date = ctime(&pwd->pw_change);

        if (date == NULL)
        {
            fprintf(stderr, "Unable to convert expiration date\n");
            return EXIT_FAILURE;
        }

        printf("change\t%s", date);
    }

    return EXIT_SUCCESS;
}
