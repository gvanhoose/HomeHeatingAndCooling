#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int createIPCSocket( char* sockName )
{
	struct sockaddr sock;
	memset( &sock, '\0', sizeof(sock) );

	int sockFD;

	if( (sockFD = socket( AF_LOCAL, SOCK_STREAM, 0 )) < 0 )
	{
		perror("createIPCSocket>socket");
		return -1;
	}

	sock.sa_family = AF_LOCAL;
	strcpy( sock.sa_data, sockName );

	if( bind( sockFD, &sock, sizeof(sock) ) < 0 )
	{
		perror( "createIPCSocket>socket" );
		return -1;
	}

	int one = 1;
	setsockopt( sockFD, SOL_SOCKET, SO_REUSEADDR, &one, sizeof( one ) );

	return sockFD;
}

int writeToSocket( char* sockName, char* value )
{
	return 0;
}


int main() // for testing only!
{
	createIPCSocket( "TEST_SOCKET" );

	return 0;
}
