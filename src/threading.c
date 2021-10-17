#include "threading.h"

#include "net/server.h"
#include <stdio.h>
#include <string.h>

enum
{
  MAXBUF = (1 << 12)
};

static void
handle_client (p_cprops_t client)
{
  char buf[MAXBUF];
  size_t bytesread, bytessent;
  size_t msglen = 0;

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
  bytessent = send_to_client (client, buf, strlen (buf));
  printf ("send %ld bytes to the client\n", bytessent);
}

void *
server_thread (void *args)
{
  p_cprops_t client;
  payload_t *payload = (payload_t *)args;
  client = (p_cprops_t)payload->client_data;
  handle_client (client);
  pthread_exit (NULL);
}