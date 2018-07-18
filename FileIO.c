#include "FileIO.h"

int readFile( char* filename, char* buffer, int alloc )
{
	FILE* fd;

	if( (fd = fopen( filename, "r" )) < 0 )
	{
		return -1;
	}

	memset( buffer, '\0', alloc );

	int size;
	if( (size = fread( buffer, 1, alloc, fd )) == 0 )
	{
		if( feof(fd) )
		{
			size = strlen( buffer );
		}
		else
		{
			size = -1;
		}
	}

	fclose(fd);

	return size;
}

static int writeToFile( char* filename, char* buffer, int size, char* wa )
{
	FILE* fd;

	if( (fd = fopen( filename, wa )) < 0 )
	{
		return -1;
	}

	int written;
	if( (written = fwrite( buffer, 1, size, fd )) == 0 )
	{
		if( feof(fd) )
		{
			written = strlen( buffer );
		}
		else
		{
			written = -1;
		}
	}

	fclose(fd);

	return written;
}

int overwriteFile( char* filename, char* buffer, int size )
{
	return writeToFile( filename, buffer, size, "w" );
}
int appendToFile( char* filename, char* buffer, int size )
{
	return writeToFile( filename, buffer, size, "a" );
}


int main()
{
	char buff [] = "Hello World!";
	int size = strlen( buff );

	int w0rout = overwriteFile( "test1.txt", buff, size );
	int w1rout = overwriteFile( "test0.txt", buff, size );

	char inbuff [32];
	int insize = readFile( "test0.txt", inbuff, 32 );

	int w2rout = overwriteFile( "test0.txt", "abcd", 4 );
	int w3rout = appendToFile( "test1.txt", "efgh", 4 );

	printf( "w0 = %d\n", w0rout );
	printf( "w1 = %d\n", w1rout );
	printf( "insize = %d\n", insize );
	printf( "inbuff = \"%s\"\n", inbuff );
	printf( "w2 = %d\n", w2rout );
	printf( "w3 = %d\n", w3rout );

	return 0;
}
