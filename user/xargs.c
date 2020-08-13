#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
    if(argc <= 2) {
        printf("You need to type in at least one parameter.\n");
        exit();
    }
    char param[512];
    char buf[32][32];
    char *pass[32];
    int i, n;
    for(i=0;i<32;i++){
        pass[i] = buf[i];
    }
    for(i=1;i<argc;i++) {
        strcpy(buf[i-1], argv[i]);
    }

    while ((n = read(0, param, sizeof(param))) > 0) {
        int pos = argc - 1;
        char *c = buf[pos];
        for (char *p = param; *p; p++) {
            if (*p == ' ' || *p == '\n') {
            *c = '\0';
            pos++;
            c = buf[pos];
            } else
                *c++ = *p;
        }
        *c = '\0';
        //memset(param, 0, sizeof(param)/sizeof(char));
        pos++;
        pass[pos] = 0;

        if (fork()) {
            wait();
        } else
            exec(pass[0], pass);
  }

  if (n < 0) {
    printf("xargs: read error\n");
    exit();
  }
  exit();
}