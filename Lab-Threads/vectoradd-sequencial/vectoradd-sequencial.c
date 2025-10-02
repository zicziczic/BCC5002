#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Entrada e saída.
float *h_a;
float *h_b;
float *h_c;

int n = 0;

void init_array(int n) {
  fprintf(stdout, "Inicializando os arrays.\n");
  int i;
  // Initialize vectors on host.
	for (i = 0; i < n; i++) {
	  h_a[i] = 0.5;
	  h_b[i] = 0.5;
	}
}

void print_array(int n) {
  int i;
  for (i = 0; i < n; i++) {
	fprintf(stdout, "h_c[%07d]: %f\n", i, h_c[i]);
  }
}

void check_result(int n){
  // Soma dos elementos do array C e divide por N, o valor deve ser igual a 1.
  int i;
  float sum = 0;
  fprintf(stdout, "Verificando o resultado.\n");  
  
  for (i = 0; i < n; i++) {
    sum += h_c[i];
  }

  fprintf(stdout, "Resultado Final: (%f, %f)\n", sum, (float)(sum / (float)n));
}

void vecadd(int n) {
  int i;

  printf("  Thread[%lu]: Particao prevista: %d [%d..%d]: %d.\n", (long int) pthread_self(), 0, 0, n-1, n);

  printf("  Thread[%lu]: Executando sobre particao: %d [%d..%d]: %d.\n", (long int) pthread_self(), 0, 0, n-1, n);
  
  for (i = 0; i < n; i++) {
    h_c[i] = h_a[i] + h_b[i];
  }

  printf("  Thread[%lu]: Terminando...\n", (long int) pthread_self());
}

int main(int argc, char *argv[]) {
  int i, num_elementos = 0;

  if(argc < 2){
    printf("Uso: %s <size>\n", argv[0]);
    exit(0);
  }

  num_elementos = atoi(argv[1]);

  printf("num_elementos: %d\n", num_elementos);

  h_a = (float *) malloc(num_elementos * sizeof(float));
  h_b = (float *) malloc(num_elementos * sizeof(float));
  h_c = (float *) malloc(num_elementos * sizeof(float));

  init_array(num_elementos);

  printf("Thread[%lu]: Calculando.\n", (long int) pthread_self());

  vecadd(num_elementos);
  
  printf("Thread[%lu]: Imprimindo o resultado.\n", (long int) pthread_self());
  print_array(num_elementos);

  printf("Thread[%lu]: Verificando o resultado.\n", (long int) pthread_self());
  check_result(num_elementos);

  printf("Thread[%lu]: Fui, Tchau!\n", (long int) pthread_self());

  fprintf(stdout, "Thread[%lu]: Releasing Allocated Memory.\n", (long int) pthread_self());
  free(h_a);
  free(h_b);
  free(h_c);

  return 0;
}
