#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) 
{
    int parent_fd[2], child_fd[2];
    pipe(parent_fd);
    pipe(child_fd);
    char buf[64];
    if(fork()) {
        // parent
        write(parent_fd[1], "ping", strlen("ping"));
        read(child_fd[0], buf, 64);
        printf("%d: received %s\n", getpid(), buf);
    }
    else {
        // child
        read(parent_fd[0], buf, 64);
        printf("%d: received %s\n", getpid(), buf);
        write(child_fd[1], "pong", strlen("pong"));
    }
    exit();
}