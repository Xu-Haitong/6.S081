#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    // read a line
    char buf[1024];
    // store full argv
    char* full_argv[MAXARG];

    if (argc < 2) {
        fprintf(2, "usage: xargs <command>\n");
        exit(1);
    }
    if (argc + 1 > MAXARG) {
        fprintf(2, "too mang args\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        full_argv[i - 1] = argv[i];
    }

    while (1) {
        int i = 0;
        while (1) {
            // read a char
            int len = read(0, &buf[i], 1);
            if (len == 0 || buf[i] == '\n') break;
            i++;
        }
        if (i == 0) break;
        // add terminating 0
        buf[i] = 0;
        full_argv[argc - 1] = buf;
        if (fork() == 0) {
            exec(full_argv[0], full_argv);
            exit(1);
        }
        else {
            wait(0);
        }
    }
    exit(0);
}