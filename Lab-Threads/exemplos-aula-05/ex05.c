/**
 * Configurando atributos de threads
 * Fonte original: https://www.ibm.com/support/knowledgecenter/SSLTBW_2.2.0/com.ibm.zos.v2r2.bpxbd00/ptaint.htm
 */

#include <stdio.h>                                                              
#include <pthread.h>
#include <stdlib.h>
                                                                                
void *thread_code(void *arg)                                                        
{                                                                               
   printf("hello from the thread\n");   
   pthread_exit(NULL);                                                          
}                                                                               
                                                                                
int main()                                                                      
{                                                                               
   int            ret_status, status;                                                     
   pthread_attr_t attr;                                                         
   pthread_t      threadid;                                                         
                                                                                
   ret_status = pthread_attr_init(&attr);                                               
   if (ret_status == -1) {                                                              
      perror("error in pthread_attr_init");                                     
      exit(1);                                                                  
   }

   ret_status = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //ou PTHREAD_CREATE_JOINABLE (padrao)
   printf("Attr state retorno = %d\n", ret_status);                                                                              

   ret_status = pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);         //ou PTHREAD_SCOPE_SYSTEM (padrao)
   printf("Attr scope retorno = %d\n", ret_status);                                                                              
                                                                                
   ret_status = pthread_create(&threadid, &attr, thread_code, NULL);                            
   if (ret_status == -1) {                                                              
      perror("error in pthread_create");                                        
      exit(2);                                                                  
   }                                                                            
                                                                                
   ret_status = pthread_join(threadid, (void *)&status);   //DETACHED ignora o join

   printf("main finished.\n");
   
   pthread_exit(NULL);  // garante que as outras threads desanexadas continuem a execucao                                                                   
}               
