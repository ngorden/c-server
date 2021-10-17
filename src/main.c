#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "net/server.h"
#include "threading.h"

int
main (void)
{
  payload_t pld;
  pthread_t pid;
  p_cprops_t client;
  p_sprops_t server;
  configurations_t cfg;

  cfg = get_config ();
  server = initialize_server (cfg.backlog, cfg.port);
  puts ("waiting for traffic");
  client = accept_connection (server);

  pld.client_data = client;
  pthread_create (&pid, NULL, server_thread, &pld);
  pthread_join (pid, NULL);

  disconnect_client (client);
  dispose_server (server);
  return EXIT_SUCCESS;
}
