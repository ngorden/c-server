#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

/* These are the constant values and default
   config values if any/none are provided. */
enum
{
  BACKLOG = 9,
  PORT = 8080,
  MAXBUF = (1 << 12)
};

/* Sets socket option as enabled. */
static int enabled = 1;

int
main (void)
{
  char buf[MAXBUF];
  size_t msglen;
  ssize_t bytesread;
  char *env_backlog;
  char *env_port;
  int connfd, sockfd;
  int backlog, port;
  struct sockaddr_in hints;

  env_port = getenv ("PORT");
  env_backlog = getenv ("BACKLOG");
  port = env_port ? atoi (env_port) : PORT;
  backlog = env_backlog ? atoi (env_backlog) : BACKLOG;

  hints.sin_family = AF_INET;
  hints.sin_port = htons (port);
  hints.sin_addr.s_addr = htonl (INADDR_ANY);

  sockfd = socket (AF_INET, SOCK_STREAM, 0);
  setsockopt (sockfd, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof (int));
  bind (sockfd, (struct sockaddr *)&hints, sizeof hints);
  listen (sockfd, backlog);

  msglen = 0;
  puts ("waiting for traffic");
  connfd = accept (sockfd, NULL, NULL);
  while ((bytesread = read (connfd, buf + msglen, MAXBUF)) > 0)
    {
      msglen += bytesread;
      printf ("got %ld bytes from client.\n", bytesread);
      if (buf[msglen - 1] == '\n')
        break;
    }

  printf ("client message:\n\t%s\n\n", buf);
  bzero (buf, MAXBUF);
  strcpy (buf, "HTTP/1.1 200 OK\r\n\r\nHello");
  send (connfd, buf, strlen (buf), 0);

  close (connfd);
  shutdown (connfd, SHUT_RDWR);

  close (sockfd);
  shutdown (sockfd, SHUT_RDWR);
  return EXIT_SUCCESS;
}