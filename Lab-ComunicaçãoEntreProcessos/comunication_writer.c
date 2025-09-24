#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>

#define SERVER_FIFO "/tmp/serverfifo"

char my_fifo_name[128];
char buf1[512], buf2[1024];

// Função para remover o FIFO ao sair
void cleanup(void) {
    unlink(my_fifo_name);
}

int main(int argc, char **argv) {
    int fd, fd_server;
    ssize_t bytes_read;

    // cria o fifo para a comunicação concatenando como PID do processo.
    sprintf(my_fifo_name, "/tmp/add_client_fifo_%ld", (long)getpid());

    if (mkfifo(my_fifo_name, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }
    
    // Registra a função de limpeza para ser chamada ao sair
    atexit(cleanup);

    printf("-- Descoberta de Número Par --\n\n");
    while (1) {
        // Solicita ao usuário uma sequência de números
        printf("Digite um número (ou Ctrl+D para sair): \n");

        if (fgets(buf1, sizeof(buf1), stdin) == NULL) {
            printf("\nSaindo...\n");
            break;
        }

        // MELHORIA: Remove a quebra de linha '\n' adicionada pelo fgets
        buf1[strcspn(buf1, "\n")] = 0;

        // Constrói a mensagem completa: "fifo_cliente numero"
        sprintf(buf2, "%s %s", my_fifo_name, buf1);

        // abre o FIFO do servidor para escrita
        if ((fd_server = open(SERVER_FIFO, O_WRONLY)) == -1) {
            perror("open: server fifo");
            break;
        }
        
        // envia a mensagem ao servidor
        if (write(fd_server, buf2, strlen(buf2)) != strlen(buf2)) {
            perror("write");
            close(fd_server); // Fecha o descritor em caso de erro
            break;
        }

        // fecha o FIFO do servidor
        if (close(fd_server) == -1) {
            perror("close server fifo");
            break;
        }

        // abre o FIFO do cliente para ler a resposta do servidor
        if ((fd = open(my_fifo_name, O_RDONLY)) == -1) {
            perror("open client fifo");
            break;
        }
        
        memset(buf2, '\0', sizeof(buf2));
        
        // lê a resposta do servidor
        if ((bytes_read = read(fd, buf2, sizeof(buf2))) == -1) {
            perror("read");
        }

        if (bytes_read > 0) {
            printf("Resposta do Servidor: %s\n\n", buf2);
        }

        // fecha o FIFO do cliente
        if (close(fd) == -1) {
            perror("close client fifo");
            break;
        }
    }
    
    return 0;
}