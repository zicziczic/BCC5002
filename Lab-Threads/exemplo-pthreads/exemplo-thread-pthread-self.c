/* Para compilar use:
 *  C compiler: gcc -lpthread exemplo-thread.c -o exemplo-thread
 *  C++ compiler: g++ -lpthread exemplo-thread.c -o exemplo-thread
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr );

int main() {
     /* Declara duas threads */
     pthread_t thread1, thread2;
     char *message1 = "Olá eu sou a Thread 1";
     char *message2 = "Olá eu sou a Thread 2";
     int  iret1, iret2;

     printf("Thread[%lu]: Principal.\n", (long int) pthread_self());

     printf("Thread[%lu]: Criando as threads.\n", (long int) pthread_self());

     /* Cria duas threads independentes, cada uma irá executar a função */
     iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);

     printf("Thread[%lu]: Thread 1 retornou: %d da criação.\n", (long int) pthread_self(), iret1);
     printf("Thread[%lu]: Thread 2 retornou: %d da criação.\n", (long int) pthread_self(), iret2);

     /* Aguarda até que todas as threads completem antes de continuar. */
     /* Pode acontecer de executar algo que termine o processo/thread principal antes das threads terminarem */

     printf("Thread[%lu]: Aguardando o término das threads.\n", (long int) pthread_self());

     iret1 = pthread_join(thread1, NULL);
     iret1 = pthread_join(thread2, NULL);

     printf("Thread[%lu]: Thread 1 retornou: %d do join.\n", (long int) pthread_self(), iret1);
     printf("Thread[%lu]: Thread 2 retornou: %d do join.\n", (long int) pthread_self(), iret2);
     
     printf("Thread[%lu]: Finalizando.\n", (long int) pthread_self());
     
     exit(0);
}

void *print_message_function(void *ptr) {
     char *message;
     message = (char *) ptr;

     printf("  Thread[%lu]: Imprimindo a mensagem: %s\n", (long int) pthread_self(), message);
}
