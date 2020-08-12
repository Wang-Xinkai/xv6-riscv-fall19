#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(2 != argc) {
        printf("You need to type in a parameter.\n");
        exit();
    }
    int x = atoi(argv[1]);
    sleep(x);
    exit();
}