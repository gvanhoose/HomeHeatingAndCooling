#include <stdio.h>
#include <string.h>

int readFile( char* filename, char* buffer, int alloc );
static int writeToFile( char* filename, char* buffer, int size, char* wa );
int overwriteFile( char* filename, char* buffer, int size );
int appendToFile( char* filename, char* buffer, int size );
