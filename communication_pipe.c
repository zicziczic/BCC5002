#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char* check_even(int num) {
    if (num % 2 == 0) {
        return "Número Par";
    } else {
        return "Número Impar";
    }
}

/* Programa principal */
int main(void) {
	pid_t pid;
	int mypipe[2];
    char buffer[40];

    /* Criar o pipe. */
	if (pipe(mypipe)) {
		fprintf(stderr, "Falha ao criar o Pipe.\n");
		return EXIT_FAILURE;
	}

    pid = fork();

    if (pid < (pid_t) 0){
        fprintf(stderr, "Falha ao executar o Fork.\n");
        return EXIT_FAILURE;
    }
    if (pid == (pid_t) 0){
        //Processo filho
        close(mypipe[1]);
        read(mypipe[0], buffer, sizeof(buffer));
        int num = atoi(buffer);
        char* retorno = check_even(num);
        printf("FILHO: ...%s\n", retorno);
        fflush(stdout);
        return EXIT_SUCCESS;
    }
    else {
        //Processo pai
        close(mypipe[0]);
        printf("PAI: Digite um número para verificar se é par: ");
        scanf("%40[^\n]", buffer);
		write(mypipe[1], buffer, sizeof(buffer));
        
        wait(NULL);
		return EXIT_SUCCESS;
    }
}