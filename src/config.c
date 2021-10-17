#include "config.h"

#include <stdlib.h>

configurations_t
get_config ()
{
  char *env_backlog;
  char *env_port;
  char *env_tcnt;
  configurations_t config;

  env_port = getenv ("PORT");
  env_backlog = getenv ("BACKLOG");
  env_tcnt = getenv ("THREAD_COUNT");

  config.port = env_port ? atoi (env_port) : PORT;
  config.backlog = env_backlog ? atoi (env_backlog) : BACKLOG;
  config.thread_count = env_tcnt ? atoi (env_tcnt) : THREAD_COUNT;

  return config;
}
