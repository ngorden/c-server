#include "threading.h"

#include "config.h"
#include "net/server.h"
#include "structures/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* default values needed in
  this translation unit */
enum
{
  MAXBUF = (1 << 12)
};

/*! @brief this is the client handler,
 *  all client interaction occurs here
 *
 *  @param[in] client pointer to the client
 *  being handled
 */
static void
handle_client (p_cprops_t client)
{
  char buf[MAXBUF];
  size_t bytesread;
  size_t bytessent;
  size_t msglen = 0;

  /* this check helps with cleanup,
    when we signal all the threads to
    continue even though there are no
    more clients */
  if (client == NULL)
    return;

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

  disconnect_client (client);
}

void
thread_cleanup (void *vcfg, pthread_t *threads, pthread_cond_t *cnd)
{
  int i;
  configurations_t *cfg = (configurations_t *)vcfg;
  for (i = 0; i < cfg->thread_count; i++)
    pthread_cond_signal (cnd);

  for (i = 0; i < cfg->thread_count; i++)
    pthread_join (threads[i], NULL);

  free (threads);
}

pthread_t *
initialize_threads (void *vcfg, payload_t *pld, void *(*thread_func) (void *))
{
  int i;
  pthread_t *threads;
  configurations_t *cfg = (configurations_t *)vcfg;

  threads = malloc (cfg->thread_count * sizeof (pthread_t));
  for (i = 0; i < cfg->thread_count; i++)
    pthread_create (&threads[i], NULL, thread_func, pld);

  return threads;
}

void *
server_thread (void *arg)
{
  p_cprops_t client;
  payload_t *payload = (payload_t *)arg;
  pthread_mutex_lock (payload->mutex);
  if ((client = (p_cprops_t)dequeue ()) == NULL)
    {
      pthread_cond_wait (payload->cond, payload->mutex);
      client = (p_cprops_t)dequeue ();
    }
  pthread_mutex_unlock (payload->mutex);

  handle_client (client);
  pthread_exit (NULL);
}
