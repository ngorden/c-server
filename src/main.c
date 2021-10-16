#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "net/server.h"

/* These are the constant values and default
   config values if any/none are provided. */
enum
{
  BACKLOG = 9,
  PORT = 8080,
  MAXBUF = (1 << 12)
};

int
main (void)
{
  char buf[MAXBUF];
  size_t msglen;
  size_t bytesread;
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

  msglen = 0;
  puts ("waiting for traffic");
  client = accept_connection (server);

  while ((bytesread = get_from_client (client, buf + msglen, MAXBUF)) > 0)
    {
      msglen += bytesread;
      printf ("got %ld bytes from client.\n", bytesread);
      if (buf[msglen - 1] == '\n')
        break;
    }

  printf ("final client message was %ld bytes\n", bytesread);
  printf ("client message:\n\t%s\n\n", buf);
  bzero (buf, MAXBUF);
  strcpy (buf, "HTTP/1.1 200 OK\r\n\r\nHello");
  send_to_client (client, buf, strlen (buf));

  disconnect_client (client);
  dispose_server (server);
  return EXIT_SUCCESS;
}
