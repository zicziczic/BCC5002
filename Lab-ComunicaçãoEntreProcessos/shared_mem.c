#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
/* Tamanho do segmento compartilhado. */
#define SHMSZ (sizeof(tshare))
typedef struct tshare
{
    int ii;
    float ff;
    char str[10];
} tshare;
int main()
{
    int shmid;

    key_t key;
    tshare *shm, *s;
    /* Nome do segmento de memória compartilhada "5678". */
    key = 5678;
    /* Cria o segmento compartilhado. */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0){
        perror("Erro ao tentar criar o segmento de shm (shmget).");
        exit(1);
    }
    printf("Identificação da região criada: %d. \nPara verificar use:\n ipcs -m | grep \"%d\"\n",
            shmid, shmid);
    /* Acoplamento do segmento criado ao espaço de dados. */
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1){
        perror("Erro ao acoplar o segmento ao espaço de dados do programa (shmat).");
        exit(1);
    }
    /* Colocando dados para o outro processo ler. */
    s = shm;
    tshare *novo = (tshare *)malloc(sizeof(tshare));
    novo->ii = 1;
    novo->ff = 1.0;
    strncpy(novo->str, "abcdefghi\0", 10);
    memcpy(s, novo, sizeof(tshare));
    /* Aguardando a leitura do outro processo. O client irá mudar o
    primeiro
    * caractere da região compartilhada para '*', indicando que já fez
    a leitura
    * do que foi posto lá.
    */
    while (shm->ii != -1)

        sleep(1);
    /* Desacoplamento da região de memória compartilhada. */
    if (shmdt(shm) == -1){
        perror("Erro ao desacoplar a região de memória compartilhada (shmdt).");
        exit(1);
    }
    /* Destruição do segmento */
    if (shmctl(shmid, IPC_RMID, 0) == -1){
        perror("Erro ao destruir o segmento compartilhado. (shmctl).");
        exit(1);
    }
    return EXIT_SUCCESS;
}