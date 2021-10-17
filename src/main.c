#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "net/server.h"
#include "threading.h"

/* These are the constant values and default
   config values if any/none are provided. */
enum
{
  BACKLOG = 9,
  PORT = 8080
};

int
main (void)
{
  payload_t pld;
  pthread_t pid;
  char *env_backlog;
  char *env_port;
  int backlog, port;
  p_cprops_t client;
  p_sprops_t server;

  env_port = getenv ("PORT");
  env_backlog = getenv ("BACKLOG");
  port = env_port ? atoi (env_port) : PORT;
  backlog = env_backlog ? atoi (env_backlog) : BACKLOG;

  server = initialize_server (backlog, port);
  puts ("waiting for traffic");
  client = accept_connection (server);

  pld.client_data = client;
  pthread_create (&pid, NULL, server_thread, &pld);
  pthread_join (pid, NULL);

  disconnect_client (client);
  dispose_server (server);
  return EXIT_SUCCESS;
}
