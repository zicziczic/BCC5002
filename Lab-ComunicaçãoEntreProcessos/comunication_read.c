#include <stdio.h>      // standard io
#include <stdlib.h>     // standard lib
#include <errno.h>      // number of last error
#include <sys/stat.h>   // data returned stat() function (mkfifo)
#include <unistd.h>     // unix standard
#include <fcntl.h>      // file control options
#include <string.h>     // string operations

#define SERVER_FIFO "/tmp/serverfifo"
#define MAX_NUMBERS 500

const char* check_even(int num) {
    if (num % 2 == 0) {
        return "Número Par";
    } else {
        return "Número Impar";
    }
}

int main(int argc, char **argv) {
    int fd, fd_client, num;
    ssize_t bytes_read;
    char buf[1024]; // Aumentar buffer para segurança
    char* return_fifo;
    char* num_str;

    printf("Iniciando Servidor.\n");

    // cria um FIFO do servidor
    if ((mkfifo(SERVER_FIFO, 0664) == -1) && (errno != EEXIST)) {
        perror("mkfifo");
        exit(1);
    }

    // abre o FIFO para leitura. Importante: abrir fora do loop.
    if ((fd = open(SERVER_FIFO, O_RDONLY)) == -1) {
        perror("open server fifo");
        exit(1);
    }

    printf("Servidor aguardando clientes...\n");

    while (1) {
        memset(buf, '\0', sizeof(buf));
        
        // Lê a mensagem completa enviada pelo cliente
        bytes_read = read(fd, buf, sizeof(buf));

        if (bytes_read == -1) {
            perror("read");
            continue; // Tenta ler novamente
        }
        
        if (bytes_read == 0) {
            // Cliente pode ter fechado a conexão, vamos reabrir o FIFO
            close(fd);
            if ((fd = open(SERVER_FIFO, O_RDONLY)) == -1) {
                perror("re-open server fifo");
                exit(1);
            }
            continue;
        }

        if (bytes_read > 0) {
            // 1. Extrai o nome do FIFO do cliente
            return_fifo = strtok(buf, " ");
            if (return_fifo == NULL) {
                fprintf(stderr, "Formato inválido: não foi possível encontrar o nome do FIFO.\n");
                continue;
            }
            
            printf("Solicitação de %s\n", return_fifo);

            // 2. Extrai a string do número (o próximo token)
            num_str = strtok(NULL, " \n");
            if (num_str == NULL) {
                fprintf(stderr, "Formato inválido: não foi possível encontrar o número.\n");
                continue;
            }

            // 3. Converte a string para inteiro
            num = atoi(num_str);
            printf("Número recebido: %d\n", num);

            const char* resultado = check_even(num);

            // Abre o FIFO do cliente para escrever a resposta
            if ((fd_client = open(return_fifo, O_WRONLY)) == -1) {
                perror("open: client fifo");
                continue;
            }
            
            // Escreve a resposta no FIFO do cliente
            if (write(fd_client, resultado, strlen(resultado)) != strlen(resultado)) {
                perror("write to client fifo");
            }

            // Fecha o FIFO do cliente
            if (close(fd_client) == -1) {
                perror("close client fifo");
            }
        }
    }

    close(fd);
    return 0;
}