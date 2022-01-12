
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int i, rc;
    int fileDesc[2];
    char buf[2000];
    int lineNo = 1;

    alarm(90);

    pipe(fileDesc);
    if ( (rc = fork()) == -1)
    {
        printf("fork failed\n");
        exit(-1);
    }

    else if (rc == 0)  /* child */
    {
        alarm(90);
        close(fileDesc[0]);

        dup2(fileDesc[1],STDOUT_FILENO);
        close(fileDesc[1]);

        rc = execve("/usr/bin/shuf", argv, NULL);

        perror("exec failed");
        exit(-1);
    }
    /* parent */
    close(fileDesc[1]);
    while ((i = read(fileDesc[0],buf,2000)) > 0)
    {
	buf[i] = '\0';
    }

    cout << lineNo << ": ";
    lineNo++;

    for(int i = 0; i<2000; i++)
    {	    
    	if(buf[i] == '\0')
	{
		break;
	}

	cout << buf[i];
	if(buf[i] == '\n' && buf[i+1]!='\0')
	{
		cout << lineNo << ": ";
    		lineNo++;
	}
    }
    return 0;
}
