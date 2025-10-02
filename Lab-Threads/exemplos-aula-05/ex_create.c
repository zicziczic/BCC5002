/** 
 * Exemplo básico de criação de threads com pthread.
 * Neste exemplo são criadas duas threads. Ambas as threads exibem uma mensagem e finalizam.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>     // pthread_t, pthread_create(), pthread_join(), pthread_exit()

/** funcao que implementa o fluxo da thread */
void *print_message_function( void *ptr );

/* fluxo principal  - thread 'main' */
int main() {
     /* Declara duas threads */
     pthread_t thread1, thread2;
     //pthread_t thread[2];
     
     char *message1 = "Olá eu sou a Thread 1";
     char *message2 = "Olá eu sou a Thread 2";

     int  iret1, iret2;

     /* Cria duas threads independentes, cada uma irá executar a função */
     iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);

     printf("Thread 1 retornou: %d\n", iret1);
     printf("Thread 2 retornou: %d\n", iret2);

     /* Aguarda até que todas as threads completem antes de continuar. */
     /* Pode acontecer de executar algo que termine o processo/thread principal antes das threads terminarem */
     //pthread_join(thread1, NULL);
     //pthread_join(thread2, NULL); 
     void *response1, *response2;
     pthread_join(thread1, &response1);
     pthread_join(thread2, &response2);
     //printf("Thread 1 devolveu %s\n", (char *)response1);  
     //printf("Thread 1 devolveu %d\n", *((int *)response1));  
     printf("Thread 1 devolveu %ld\n", *((pthread_t *)response1));  


     printf("MAIN - FIM\n");
     
     pthread_exit(0);
     //exit(0);
}

/* funcao executada pela thread */
void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;   //casting - coersão explicita
     sleep(1);
     printf("%s \n", message);
     
     int *value = malloc(sizeof(int));
     *value = 100;
     
     pthread_t *tid = malloc(sizeof(pthread_t));
     *tid = pthread_self();
     printf("%ld\n", *tid);

     //pthread_exit((void *) "teste");
     //pthread_exit((void *) value);
     pthread_exit((void *) tid);
     
     return NULL;
}
