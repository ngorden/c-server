#include <stdio.h>
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
  int i;
  payload_t pld;
  p_cprops_t client;
  p_sprops_t server;
  pthread_t *threads;
  configurations_t cfg;

  cfg = get_config ();
  pld.cond = &cnd;
  pld.mutex = &mtx;

  threads = malloc (cfg.thread_count * sizeof (pthread_t));
  for (i = 0; i < cfg.thread_count; i++)
    pthread_create (&threads[i], NULL, server_thread, &pld);

  server = initialize_server (cfg.backlog, cfg.port);
  puts ("waiting for traffic");
  client = accept_connection (server);
  pthread_mutex_lock (&mtx);
  enqueue (client);
  pthread_cond_signal (&cnd);
  pthread_mutex_unlock (&mtx);

  for (i = 0; i < cfg.thread_count; i++)
    pthread_join (threads[i], NULL);

  disconnect_client (client);
  dispose_server (server);
  return EXIT_SUCCESS;
}
