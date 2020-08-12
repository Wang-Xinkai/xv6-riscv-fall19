#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void 
source ()
{
    int i;
    for(i=2;i<36;i++) {
        write(1, &i, sizeof(i));
    }
}
void 
divide(int p)
{
    int n;
    while(read(0, &n, sizeof(n))){
        if(n%p!=0){
            write(1, &n, sizeof(n));
        }
    }

}

void 
redirect(int k, int p[]) 
{
    close(k);
    dup(p[k]);
    close(p[0]);
    close(p[1]);
}

void sink() 
{
    int pd[2];
    int p;
    if(read(0, &p, sizeof(p))) {
        printf("prime %d\n", p);
        pipe(pd);
        if(fork()){
            redirect(0, pd);
            sink();
        }
        else {
            redirect(1, pd);
            divide(p);
        }
    }
}

int 
main(int argc, char *argv[]) 
{
    int p[2];
    pipe(p);
    if(fork()){
        redirect(0, p);
        sink();
    }
    else {
        redirect(1, p);
        source();
    }
    exit();
}