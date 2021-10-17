#include "minunit.h"

#include "config.h"
#include <stdlib.h>

MU_TEST (backlog)
{
  configurations_t cfg;
  cfg = get_config ();
  mu_check (cfg.backlog == BACKLOG);

  setenv ("BACKLOG", "4", 0);
  cfg = get_config ();
  mu_check (cfg.backlog == atoi (getenv ("BACKLOG")));
  unsetenv ("BACKLOG");
}

MU_TEST (port)
{
  configurations_t cfg;
  cfg = get_config ();
  mu_check (cfg.port == PORT);

  setenv ("PORT", "4848", 0);
  cfg = get_config ();
  mu_check (cfg.port == atoi (getenv ("PORT")));
  unsetenv ("PORT");
}

MU_TEST (thread_count)
{
  configurations_t cfg;
  cfg = get_config ();
  mu_check (cfg.thread_count == THREAD_COUNT);

  setenv ("THREAD_COUNT", "1", 0);
  cfg = get_config ();
  mu_check (cfg.thread_count == atoi (getenv ("THREAD_COUNT")));
  unsetenv ("THREAD_COUNT");
}

MU_TEST_SUITE (config)
{
  MU_RUN_TEST (backlog);
  MU_RUN_TEST (port);
  MU_RUN_TEST (thread_count);
}

int
main (void)
{
  MU_RUN_SUITE (config);
  MU_REPORT ();
  return MU_EXIT_CODE;
}