#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void runpipe(); //define functions

//the code runs perfectly in xv6 but itsn't able to run exec command on ls and tr files 
//as ls and tr are unix based utilities and not available in xv6

/*ERROR*/ //ALL THESE COMMENTED LINES WILL CAUSE ERROR IN XV6 SO THEY CANT BE RUN,
//SO INSTEAD RIGHT AFTER THOSE I HAVE REPLACED THEIR POSSIBLE REPLACEMENTS IN XV6

int main(int argc, char **argv)
{
	int pid, status;
	int fd[2]; //file decsriptor of pipe always set to 2
	pipe(fd); //piping
	
	
	switch (pid = fork()) {
		case 0: //child pe function chalega
		runpipe(fd);
		exit(0);
		
		
		default: //other than 0 pe parent chalega
		while ((pid = wait(&status)) != -1)
/*ERROR*/	//fprintf(stderr, "process %d exits with %d\n",pid,WEXITSTATUS(status)); //
		//WEXITSTATUS NOT IN XV6
		printf("ERROR: process %d exits with %d\n",pid,status);
		break;
		
		
		case -1:
/*ERROR*/	//perror("fork");
		printf("FORK FAILED\n");
		exit(1);
	}
	
	
	exit(0);
}


	char *cmd1[] = { "/bin/ls", "-al", "/", 0 };
	char *cmd2[] = { "/usr/bin/tr", "a-z", "A-Z", 0 };
	
void runpipe(int pfd[])
{
	int pid;
	
	switch (pid = fork()) {
		case 0:
/*ERROR*/	//dup2(pfd[0], 0);
 		close(0);
		dup(pfd[0]);
		close(pfd[1]); //close write end of pipe to avoid data leakage
/*ERROR*/	//execvp(cmd2[0], cmd2);
		exec(cmd2[0], cmd2); //will not execute properly as TR doesnt exist in xv6
		printf("Translation tr FAILED\n");//no output tho after exec
/*ERROR*/	//perror(cmd2[0]);
		exit(0);
		
		default:
/*ERROR*/	//dup2(pfd[1], 1);
		close(1); //close stdout
		dup(pfd[1]); //redirect pipes write to stdout
		close(pfd[0]);
/*ERROR*/	//execvp(cmd1[0], cmd1);
		exec(cmd1[0],cmd1); //will not execute properly as LS doesnt exist in xv6
		printf("Listing ls FAILED\n");
		wait(0);
/*ERROR*/	//perror(cmd1[0]);
		
		case -1:
/*ERROR*/	//perror("fork");
     		printf("FORK FAILED\n");
		exit(1);
		
	}
}





