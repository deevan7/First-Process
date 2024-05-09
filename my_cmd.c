#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int option;
    char *executable = NULL;
    char *options = NULL;
    int background = 0; // 0 for foreground, 1 for background

    while ((option = getopt(argc, argv, "e:o:bf")) != -1) {
        switch (option) {
            case 'e':
                executable = optarg;
                break;
            case 'o':
                options = optarg;
                break;
            case 'b':
                background = 1;
                break;
            case 'f':
                background = 0;
                break;
            default:
                fprintf(stderr, "Usage: %s -e <pathname of an executable> -o \"String of command line options\" [-b | -f]\n", argv[0]);
                return 1;
        }
    }

    if (executable == NULL) {
        fprintf(stderr, "Executable path is required (-e option)\n");
        return 1;
    }

    char *cmd[100];
    int i = 0;
    cmd[i++] = executable;

    char *token = strtok(options, " ");
    while (token != NULL) {
        cmd[i++] = token;
        token = strtok(NULL, " ");
    }
    cmd[i] = NULL;

    printf("Command Line: ");
    for (int j = 0; j < i; j++) {
        printf("%s ", cmd[j]);
    }
    printf("\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        char *new_env[] = {"PATH=/usr/bin",NULL };
        if (execve(executable, cmd, new_env) == -1) {
            perror("Exec failed");
            return 1;
        }
    } else {
        if (background) {
            printf("Running in the background with PID: %d\n", pid);
        } else {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                int exitCode = WEXITSTATUS(status);
                if (exitCode != 0) {
                    printf("Exit Code of Child: %d\n", exitCode);
                } else {
                    printf("Child Process exited normally with status 0\n");
                }
            } else {
                printf("Child Process did not exit normally\n");
            }
            printf("Child Process ID: %d\n", pid);
        }
    }


    printf("Error Code of your C program: %d\n", errno);

    return 0;
}
