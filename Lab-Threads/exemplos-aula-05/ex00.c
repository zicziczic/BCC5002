/** 
 * Exemplo básico de criação de threads com pthread.
 * Neste exemplo são criadas duas threads. Ambas as threads exibem uma mensagem e finalizam.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>     // pthread_t, pthread_create(), pthread_join(), pthread_exit()

/** funcao que implementa o fluxo da thread */
void *print_message (void *ptr);

/* fluxo principal  - thread 'main' */
int main() {
     /* Declara duas threads */
     pthread_t thread1, thread2;
     //pthread_t thread[2];
     
     char *msg1 = "Olá eu sou a Thread 1";
     char *msg2 = "Olá eu sou a Thread 2";

     int  iret1, iret2;

     /* Cria duas threads independentes, cada uma irá executar a função */
     iret1 = pthread_create( &thread1, NULL, print_message, (void*) msg1);
     iret2 = pthread_create( &thread2, NULL, print_message, (void*) msg2);

     printf("Thread 1 retornou: %d\n", iret1);
     printf("Thread 2 retornou: %d\n", iret2);

     /* Aguarda até que todas as threads completem antes de continuar. */
//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL); 
     printf("MAIN - FIM\n");
     
     pthread_exit(0);
     
     //exit(0);
}

/* funcao executada pela thread */
void *print_message (void *ptr)
{
     char *message;
     message = (char *) ptr;   //casting - coersão explicita
     sleep(2);
     printf("%s \n", message);
     
//     pthread_exit(NULL);
     return NULL;
}
