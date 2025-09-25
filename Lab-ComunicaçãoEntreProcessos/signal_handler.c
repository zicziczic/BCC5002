#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sighandler(int signal) {
    if (signal == SIGINT){
        printf("Recebido SIGINT");
    }
    if (signal == SIGTERM){
        printf("Recebido SIGINT");
    }
    if (signal == SIGALRM){
        printf("Recebido SIGALRM");
    }

    fflush(stdout);
}


int main(){

    //Associando função tratadora de sinais
    if (signal(SIGTERM, sighandler) == SIG_ERR){
        printf("SIGTERM Não Funcionou.");
    }
    if (signal(SIGINT, sighandler) == SIG_ERR){
        printf("SIGINT Não Funcionou.");
    }
    if (signal(SIGALRM, sighandler) == SIG_ERR){
        printf("SIGALRM Não Funcionou.");
    }

    printf("My PID is: %d.\n", getpid());

    while(1){
        sleep(1);
    }
    return 0;
}