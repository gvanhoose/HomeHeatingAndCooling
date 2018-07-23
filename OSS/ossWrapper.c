#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	while(1)
	{
		pid_t cpid = fork();

		if( cpid < 0 )
		{
			return -1;
		}
		if( cpid == 0 )
		{
			char* cmd [] = {"./oss", "&"};
			execv( cmd[0], cmd );

			return -1;
		}
		if( cpid > 0 )
		{
			int rawExitReturn = 0x0, exitSuccess;
			waitpid( cpid, &rawExitReturn, 0x0 );

			exitSuccess = (WIFEXITED( rawExitReturn ));

			if( !exitsuccess )
			{
				// code to handle a failed child process should go here
			}
			sleep(1);
		}
	}

	return 0;
