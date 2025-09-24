/**
 * Lê mensagens de um FIFO e exibe na tela
 */
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
    if (num%2 == 0){
        return "Número Par";
    } else {
        return "Número Impar";
    }
};

int main(int argc, char **argv) {

    int fd, fd_client,
        num,              // descritores do FIFO (servidor e cliente)
        bytes_read, i;              
    char buf [100];
    char return_fifo;              // nome do FIFO do cliente

    printf("Iniciando Servidor.\n");

    // cria um FIFO
    if ((mkfifo (SERVER_FIFO, 0664) == -1) && (errno != EEXIST)) {
        perror ("mkfifo");
        exit (1);
    }

    // abre o FIFO para leitura
    if ((fd = open (SERVER_FIFO, O_RDONLY)) == -1)
        perror ("open");

    while (1) {
        // lê o que o cliente mandou
        ssize_t n = read(fd, buf, sizeof(buf));
        if (n == -1) {
            perror("Erro ao ler da FIFO");
            close(fd);
            exit(EXIT_FAILURE);
        }

        buf[n] = '\0';

        if (sscanf(buf, "%d %s", &num, return_fifo) != 2) {
            fprintf(stderr, "Formato inválido: %s\n", buf);
            continue;
        }


        // Converte Numero Para Inteiro
        const char* resultado = check_even(num);

        if ((fd_client = open (return_fifo, O_WRONLY)) == -1) {
                    perror ("open: client fifo");
                    continue;
                }
        if (write (fd_client, resultado, strlen(resultado)+1) != strlen (resultado))
                 perror ("write");

        if (close (fd_client) == -1)
            perror ("close");
    }
    close(fd);
    return 0;
}