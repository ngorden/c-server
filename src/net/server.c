#include "server.h"

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_in;

struct client_props
{
  int connfd;
  SA_in hints;
};

struct server_props
{
  int sockfd;
  SA_in hints;
};

/* Sets socket option as enabled. */
static int enabled = 1;

struct client_props *
accept_connection (struct server_props *server)
{
  socklen_t addrlen;
  struct client_props *props = malloc (sizeof *props);
  if (props == NULL)
    return NULL;

  addrlen = sizeof props->hints;
  props->connfd = accept (server->sockfd, (SA *)&props->hints, &addrlen);
  return props;
}

void
disconnect_client (struct client_props *client)
{
  close (client->connfd);
  shutdown (client->connfd, SHUT_RDWR);
  free (client);
}

void
dispose_server (struct server_props *props)
{
  close (props->sockfd);
  shutdown (props->sockfd, SHUT_RDWR);
  free (props);
}

struct server_props *
initialize_server (int backlog, int port)
{
  struct server_props *props = malloc (sizeof *props);

  props->hints.sin_family = AF_INET;
  props->hints.sin_port = htons (port);
  props->hints.sin_addr.s_addr = htonl (INADDR_ANY);

  props->sockfd = socket (AF_INET, SOCK_STREAM, 0);
  setsockopt (props->sockfd, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof (int));
  bind (props->sockfd, (struct sockaddr *)&props->hints, sizeof props->hints);
  listen (props->sockfd, backlog);
  printf ("waiting for traffic on %d\n", port);

  return props;
}

size_t
get_from_client (struct client_props *client, void *data, size_t nbytes)
{
  size_t bytesreceived;
  bytesreceived = read (client->connfd, data, nbytes);
  return bytesreceived;
}

size_t
send_to_client (struct client_props *client, void *data, size_t nbytes)
{
  size_t bytessent;
  bytessent = send (client->connfd, data, nbytes, 0);
  return bytessent;
}
