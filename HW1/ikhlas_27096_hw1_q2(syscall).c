#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(void) { 


  int pid=fork();
  
 
     if(pid==0){ //child 
     char *args[] = {"Simpleprog", "Hello", "from", "ikhlas", 0}; //can replace args[0] with any file/program name u wanna run
     //or u can capture from the command line
     printf("COUNTER RESET\n");
     resetc(); //RESET COUNTER /*1*/
     exec(args[0],args); /*EXECUTE PROGRAM IN CHILD*/ /*2*/
     exit(0);
     }
     
     else{ //parent
     wait(0);
     printf("Total System calls in the program: %d\n",count());// gave total system calls   /*3*/
     }

    

return 0;
}








