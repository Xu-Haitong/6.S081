#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    int duration; // 变量声明一定要写在最前面。。否则会报看不懂的错。。
    if (argc <= 1) {
        fprintf(2, "usage: sleep NUMBER\n");
        exit(1);
    }
    duration = atoi(argv[1]);
    sleep(duration);
    exit(0);
}