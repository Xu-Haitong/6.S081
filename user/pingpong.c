#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    int p[2];
    char content;
    int pid;
    if (argc > 1) {
        fprintf(2, "usage : pingpong\n");
        exit(1);
    }
    pipe(p);
    if (fork() == 0) {
        // child
        pid = getpid();
        // blocking wait 1 byte from parent
        read(p[0], &content, 1);
        close(p[0]);
        printf("%d: received ping\n", pid);
        // send 1 byte to parent
        write(p[1], "0", 1);
        close(p[1]);
    }
    else {
        // parent
        pid = getpid();
        // send 1 byte to child
        write(p[1], "0", 1);
        close(p[1]);
        wait(0);
        // receive 1 byte from child
        read(p[0], &content, 1);
        close(p[0]);
        printf("%d: received pong\n", pid);
    }
    exit(0);
}