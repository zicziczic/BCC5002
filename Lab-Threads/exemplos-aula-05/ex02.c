/**
 * Exemplo de cancelamento de thread
 */

#include <pthread.h>   // pthread_testcancel(), pthread_setcancelstate(), pthread_cancel()
#include <stdio.h>
#include <unistd.h>

/* tarefa para ser executada como thread  e testar o cancelamento */
void *task_do_nothing(void *parm)
{
  int   i = 1;
  printf("THREAD - thread executada.\n");
  //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
  /* altera o tipo de cancelamento para assíncrono - padrão é o deferred (adiado) */
  //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);  

  for (;;i++) {
    printf("THREAD - thread em laco %d\n", i);   //ponto de cancelamento
    
    /* testa o cancelamento */
    //pthread_testcancel();

    sleep(1);
    if (i == 5) {
      /* Como o opcao de cancelamento foi desabilitada, ativar  agora */
       printf("THREAD - ativa o estado de cancelamento\n");
       pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    }
  } // for
 
  return NULL;
}


/* fluxo principal (thread principal) */
int main(int argc, char **argv)
{
  pthread_t thread;
  int status = 0;

  printf("MAIN   - Iniciando a thread principal (main)\n");

  /* cria a thread com atributos padrões */
  printf("MAIN   - Cria a thread com atributos padroes \n");
  status = pthread_create(&thread, NULL, task_do_nothing, NULL);
   
  /* aguarda um tempo antes de solicitar o cancelamento */
  sleep(2);

  printf("MAIN   - Cancelar a thread\n");
  status = pthread_cancel(thread);
  printf("MAIN   - Retorno de pthread_cancel %d\n", status);

  pthread_join(thread, NULL);  
  printf("MAIN   - Main completed\n");

  pthread_exit(NULL);
  
  return 0;
}
