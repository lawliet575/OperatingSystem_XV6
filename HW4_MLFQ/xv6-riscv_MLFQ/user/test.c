#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"


int main() {

    int pid = fork();  // Fork the process

    if (pid > 0) {
        // Parent process
             wait((int *) 0);
            printf("parent comin up\n");
            

        
    } 
    else if (pid == 0) {
        // Child process
        printf("child comin up\n");
        exit(0);

        
    }


//reading wriitng on pipe
int p[2];
	pipe(p);
	int pd=fork();
	
	
	if(pd==0){
	write(p[1],"hello ikhlas from child\n",13);// write to  pipe p using file descriptor 1
	printf("msg written in pipe\n");
	exit(0);
	}
	
	
	else if(pd>0){
	wait(0);// now went to child
	char buf[13];
	//read from pipe p using file descriptor 0
	read(p[0],buf,13);//13byte jo likhi hai abhi wo
	close(0); //fd ka input wala part now closed so that it doesnt hang 
	printf("successfully readed in parent: %s\n",buf);
	}

    return 0;
}