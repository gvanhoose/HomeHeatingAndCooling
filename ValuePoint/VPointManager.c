#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

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

	while(1)
	{
		int clientFD = accept( listenerFD, (struct sockaddr*) NULL, NULL );

		memset( recData, '\0', 65 );

		recSize = read( clientFD, recData, 64 );
