#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int test = 5;
	while( test-- )
	{
		pid_t cpid = fork();

		if( cpid < 0 )
		{
			// code to handle fork fail goes here, but it's so unlikely that it can wait
			return -1;
		}
		if( cpid == 0 )
		{
			char* cmd [] = {"./sched", "&"};
			execv( cmd[0], cmd );

			// code to handle execv fail goes here, but again it's so unlikely...
			return -1;
		}
		if( cpid > 0 )
		{
			int rawExitReturn = 0x0, exitSuccess;
			waitpid(cpid, &rawExitReturn, 0x0);

			exitSuccess = ( WIFEXITED( rawExitReturn ) );

			if( !exitSuccess )
			{
				// code to handle child process failure should go here.  This should be done ASAP!
			}
			sleep(1);	// to avoid overdriving the CPU
		}
	}

	return 0;
}
