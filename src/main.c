#include <stdlib.h>

#include "config.h"
#include "net/server.h"
#include "structures/queue.h"
#include "threading.h"

pthread_cond_t cnd = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int
main (void)
{
  payload_t pld;
  p_cprops_t client;
  p_sprops_t server;
  pthread_t *threads;
  configurations_t cfg;

  cfg = get_config ();
  pld.cond = &cnd;
  pld.mutex = &mtx;

  threads = initialize_threads (&cfg, &pld);
  server = initialize_server (cfg.backlog, cfg.port);
  client = accept_connection (server);

  pthread_mutex_lock (&mtx);
  enqueue (client);
  pthread_cond_signal (&cnd);
  pthread_mutex_unlock (&mtx);

  thread_cleanup (&cfg, threads, &cnd);
  dispose_server (server);
  return EXIT_SUCCESS;
}
