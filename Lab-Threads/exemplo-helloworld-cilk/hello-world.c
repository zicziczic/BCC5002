#include <stdio.h>
#include <cilk/cilk.h>

static void hello() {
  int i = 0;
  for (i = 0; i < 1000000; i++)
    printf("");
  fprintf(stdout, "Thread[%lu]: Before parallel region.\n", (long int) pthread_self());
  fprintf(stdout, "Hello ");
}

static void world() {
  int i = 0;
  for (i = 0; i < 1000000; i++)
    printf("");
  fprintf(stdout, "Thread[%lu]: Before parallel region.\n", (long int) pthread_self());
  fprintf(stdout, "world!\n");
}

int main() {
  
  printf("Spawning threads.\n");  

  cilk_spawn hello();
  cilk_spawn world();
  cilk_sync;

  printf("Done!\n");

  return 0;
}
