#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


int main() {
    
    char cmd[100];
    pid_t pid;
    pid_t ppid;
    int check;
    char *subc;
    char *sep[100]={NULL};
    int i=0;
    int fd[2],nbytes;
    int andtrig=0;
    
        
    while (1) {
        andtrig=0;
        subc=NULL;
        check=0;
        
        
        for (i=0; i!=100; i++) {
            sep[i]=NULL;
        }
        
        i=0;
        printf(">");
        fgets (cmd, 100, stdin);
        
        
        
        if(cmd[strlen(cmd)-1]=='\n') {
            cmd[strlen(cmd)-1]='\0';
        }
        if (strcmp(cmd,"exit")==0) {
            break;
        }
        
        subc=strtok(cmd," |>");
        while (subc!=NULL) {
            sep[i]=subc;
            subc=strtok(NULL," |>");
            i++;
        }
        if (strcmp(sep[i-1],"&")==0) {
            sep[i-1]=NULL;
            andtrig=1;
        }
        /* for (i=0; i!=10; i++) {
         
         if(sep[i]==NULL) break;
         printf("%s\n",sep[i]);
         }*/
        
        
        pid = fork();
        
        if (pid<0) {
            fprintf(stderr, "Fork Failed a");
            exit(-1);
            
        }
        
        else if (pid==0) {
            ppid=fork();
            
            if (ppid<0) {
                fprintf(stderr, "Fork Failed b");
                exit(-1);
                
            }
            
            if (ppid==0) {
                //printf("[%d]\n",getpid());
                check = execvp(sep[0],sep);
                //printf("done\n");
                exit (0) ;
            }
            else{
                if(andtrig==0){
                    wait(NULL);
                }
                exit (0);
            }

        }
        
        else {
                wait(NULL);
            
        }

    }
    return 0;
}
/* printf("[%d]\n",andtrig);
 if (andtrig==1) {
 printf("[%d]",getpid());
 }
 check = execvp(sep[0],sep);
 exit (0) ;
*/
