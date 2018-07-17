#include "ValuePoint.h"

int writeToVPoint( char* vName, char* value )
{
	FILE* p_vFD;

	if( (p_vFD = fopen( vName, "w" )) == NULL )
	{
		perror( "writeToVPoint>fopen" );
		return -1;
	}

	if( fprintf( p_vFD, value ) < 0 )
	{
		perror( "writeToVPoint>fprintf" );
		return -1;
	}

	if( fclose( p_vFD ) )
	{
		perror( "writeToVPoint>fclose" );
		return -1;
	}

	return 0;
}

int readVPoint( char* vName, char* target, int tarSize )
{
	FILE* p_vFD;

	if( (p_vFD = fopen( vName, "r" )) == NULL )
	{
		perror( "readVPoint>fopen" );
		return -1;
	}

	memset( target, '\0', tarSize );

	int rsize;
	if( (rsize = fread( target, 1, tarSize, p_vFD )) == 0 )
	{
		if( feof( p_vFD ) )
		{
			clearerr(p_vFD);
			return strlen( target );
		}
		perror( "readVPoint>fread" );
		rsize = -1;
	}

	if( fclose(p_vFD) < 0 )
	{
		perror("readVPoint>fclose" );
		return -1;
	}

	return rsize;
}
