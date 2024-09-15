#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
	
	int p1[2]; // parent-pipe
	pipe(p1); 
	
	int p2[2]; //child-pipe
	pipe(p2);
	
	int pid=fork();
	
	/*1*/
	if(pid>0){ //parent pehle chalta hai 
	write(p1[1],"P",1);
	printf("written\n");
	wait((int *)0); //goes to child now
	
	
	/*3*/
	char *bufp[1];
	read(p2[0],bufp,1); //read 1 byte jo child ne abhi p2 me likhi
	printf("<%d>:recieved pong\n",getpid() );
		
	}
	
	/*2*/
	else if(pid==0){//child
	char *buf[1];
	read(p1[0],buf,1);//read 1 byte JO parent ne abhi p1 me likhi
	printf("<%d>:recieved ping\n",getpid() );
	
	//2nd pipe process
	write(p2[1],"C",1);
	exit(0);

	}

    return 0;
}


