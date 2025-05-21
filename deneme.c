#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int id = fork();
    if(id == 0)
        printf("a--%d b--%d\n",getpid(), getppid());
    else
        printf("1--%d 2--%d\n",getpid(), getppid());
    wait(NULL);
    return 0;
}