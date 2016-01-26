/* Author : Edward Owusu - Adjei */
/* made it to correctly copy files to storage */


#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#ifndef BUF_SIZE
#define BUF_SIZE 262144
#endif

int main(int argc , char *argv[])
{
	int inputfd , outputfd, openflags;
	mode_t filePerms;
	ssize_t numRead , readout;
	char buf[BUF_SIZE];

	if(argc != 3 ||strcmp(argv[1],"--help") == 0)
	{
		printf("%s oldfiledir newfiledir\n",argv[0]);
		exit(1);
	}

	/* open input and output files */

	inputfd = open(argv[1],O_RDONLY);
	if(inputfd == -1)
	{
		printf("Error opening file\n",argv[1]);
        exit(0);
	}
 	openflags = O_CREAT | O_WRONLY | O_TRUNC ; /* equivalent to creat() but with flags it acts as creates yunnoe */
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP|S_IROTH|S_IWOTH; /* rw-rw-rw */

	outputfd = open(argv[2],openflags, filePerms);
	if (outputfd == -1)
	{
		printf("%s Error opening file \n",argv[2]);
		exit(1);
	}
	while((numRead = read(inputfd,buf,BUF_SIZE))> 0 )
	{
		readout = write(outputfd,buf,numRead);
		if(readout != numRead)
		{
			printf("Error writing whole\n",argv[2]);
		}
		
		
	} 
	if(numRead == -1)
	{
		printf("Read\n");
		exit(2);
	}
	if(close(inputfd)== -1)
	{
		printf("Exit output\n");
		exit(3);
	}
	if(close(outputfd) == -1)
	{
		printf("Exit output\n");
		exit(4);
	}
	//fsync(outputfd);
	exit(EXIT_SUCCESS);
	
	
}
