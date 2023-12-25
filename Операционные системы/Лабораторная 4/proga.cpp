#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char* argv[]){

	while (1){
		char ar[100];
		scanf("%s",ar);
		pid_t child = fork();
		if (child != 0);
			
		if (child == 0)
			if (execvp(ar,argv) ==-1)
				perror("execvp call: ");	
	}
return 0;
}
