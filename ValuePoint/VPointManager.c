
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include "ValuePoint.h"

int vPointName( char* target, char* source, int srcSize, int talloc )
{
	memset( target, '\0', talloc );

	char current;
	int i;
	for( i = 0; i < srcSize; i++ )
	{
		current = source[i];
		if( current == '>' )
		{
			break;
		}

		target[i] = source[i];
	}

	return i;
}

int vPointValu( char* target, char* source, int srcSize, int talloc )
{
	memset( target, '\0', talloc );

	char current;
	int i, demarkReached = 0, tsize = 0;
	for( i = 0; i < srcSize; i++ )
	{
		current = source[i];
		if( !demarkReached )
		{
			demarkReached = (current == '>')? 1 : 0;
			continue;
		}
		if( current == '\n' )
		{
			break;
		}

		target[ tsize++ ] = current;
	}
	target[--tsize] = '\0';		// BEWARE:  Depending on which OS sends this info, there may not be a second EOL char.  This line of code is only here because the client was running in Windos.
	return tsize;
}

int main()
{
	struct sockaddr_in insock;

	int listenerFD;

	if( (listenerFD = socket( AF_INET, SOCK_STREAM, 0 )) < 0 )
	{
		return -1;
	}

	memset(  (char*) &insock, '\0', sizeof( insock ) );
	insock.sin_family = AF_INET;
	insock.sin_addr.s_addr = htonl( INADDR_ANY );
	insock.sin_port = htons( 5000 );

	if( bind( listenerFD, (struct sockaddr*) &insock, sizeof( insock ) ) < 0 )
	{
		return -1;
	}

	listen( listenerFD, 10 );

	char recData [65];
	int recSize = 0;

	char vname [32];
	char vvalu [32];

	int nsize, vsize;

	while(1)
	{
		int clientFD = accept( listenerFD, (struct sockaddr*) NULL, NULL );

		memset( recData, '\0', 65 );

		recSize = read( clientFD, recData, 64 );

		nsize = vPointName( vname, recData, recSize, 32 );
		vsize = vPointValu( vvalu, recData, recSize, 32 );

		if( strcmp( "test", vname) == 0 && strcmp( "shutdown", vvalu ) == 0 )
		{
			break;
		}

		writeToVPoint( vname, vvalu );

	}

	close( listenerFD );

	return 0;
}
