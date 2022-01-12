//Matthew Wells

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

bool done = false;
int exitCode = 0;
int sigCount = 0;

//NOTE: I tried both sigabbrev_np() and sys_signame[], both of which did not work on this system. As a result,
//I have split the signals into 4 separate handler functions. I could have also made my own custom array but for
//this few signals, this seemed appropriate.
void hupHandler(int signum)
{
    printf("received SIGHUP\n");
    sigCount++;
}

void user1Handler(int signum)
{
    printf("received SIGUSR1\n");
    sigCount++;
}


void user2Handler(int signum)
{
    printf("received SIGUSR2\n");
    sigCount++;
}

void termHandler(int signum)
{
    printf("received SIGTERM\n");
    done = true;
    exitCode = 222;
    sigCount++;
}

int main(int argc, char **argv)
{
    alarm(90);
    siggy();
    signal(SIGHUP,hupHandler);
    signal(SIGTERM,termHandler);
    signal(SIGUSR1,user1Handler);
    signal(SIGUSR2,user2Handler);

    while(!done)
    {
	sleep(1);
    }

    printf("TOTAL HANDLED %i", sigCount);
    return exitCode;
}
