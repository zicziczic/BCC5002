#include <stdio.h>
#include <pthread.h>

int main() {
  int sum = 0;
  int i = 0;
  pthread_mutex_t m;
  pthread_mutex_init(&m, NULL);

  cilk_for (i = 0; i <= 1024; i = i+1)
  {
    // lock.
    pthread_mutex_lock(&m);
    sum += i;
    // unlock.
    pthread_mutex_unlock(&m);
  }

  printf("%d\n", sum);

  return 0;
}
