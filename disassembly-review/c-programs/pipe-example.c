/*
Simple pipe example.

Run this application with:

ls | x86_64/pipe-example
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char *argv[]){
	int ret_val = 0;

	//pipefd[0] refers to the read end of the pipe.  pipefd[1] refers to the write end of the pipe
	int pipe_descriptors[2];

	ret_val = pipe(pipe_descriptors);
	if (ret_val == -1){
		perror("pipe");
		exit(1);
	}


	if (fork() == 0){
		// Child process
		dup2(pipe_descriptors[1], 1);
		close(pipe_descriptors[0]);
	}

	//Parent process
	dup2(pipe_descriptors[0], 0);
	close(pipe_descriptors[1]);

	execlp("sort", "sort", "-r", (char *)0);
	return 0;
}