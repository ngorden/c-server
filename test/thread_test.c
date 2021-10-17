#include "minunit.h"

#include "config.h"
#include "threading.h"
#include <unistd.h>

static int pass = 0;
pthread_t *thread = NULL;
pthread_cond_t cnd = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
configurations_t cfg;

void *
idle_thread (void *arg)
{
  pthread_mutex_lock (&mtx);
  pass = 1;
  pthread_mutex_unlock (&mtx);
  pthread_exit (arg);
}

MU_TEST (thread_initializer)
{
  cfg.thread_count = 1;
  thread = initialize_threads (&cfg, NULL, idle_thread);
  mu_check (thread != NULL);
}

MU_TEST (thread_cleaner)
{
  thread_cleanup (&cfg, thread, &cnd);
  mu_check (pass == 1);
}

MU_TEST_SUITE (threading)
{
  MU_RUN_TEST (thread_initializer);
  MU_RUN_TEST (thread_cleaner);
}

int
main (void)
{
  MU_RUN_SUITE (threading);
  MU_REPORT ();
  return MU_EXIT_CODE;
}