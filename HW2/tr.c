#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"



int main(int argc, char *argv[]) {

	char buffer[512];
	int n;
	
	
	while ( (n=read(0,buffer,sizeof(buffer))) >0){
	for (int i=0;i<n;i++){
		if(buffer[i]>='a' &&buffer[i]<='z'){
		buffer[i]=buffer[i]+('A'-'a');
		}
	}
	
	write(1,buffer,n);
} 
	exit(0);
	
    return 0;
}


