#include "minunit.h"
#include "structures/queue.h"

MU_TEST (complex)
{
  int queue_data[5] = { 1, 2, 3, 4, 5 };

  enqueue (queue_data + 3);
  enqueue (queue_data + 4);
  enqueue (queue_data + 1);
  enqueue (queue_data + 5);

  mu_check (dequeue () == queue_data + 3);
  mu_check (dequeue () == queue_data + 4);
  mu_check (dequeue () == queue_data + 1);
  mu_check (dequeue () == queue_data + 5);

  enqueue (queue_data + 5);
  enqueue (queue_data + 1);
  mu_check (dequeue () == queue_data + 5);
  enqueue (queue_data + 2);
  enqueue (queue_data + 3);

  mu_check (dequeue () != dequeue ());
  mu_check (dequeue () != NULL);
  mu_check (dequeue () == NULL);
}

MU_TEST (simple)
{
  void *dqd;
  int queue_data = 38;

  enqueue (&queue_data);
  dqd = dequeue ();

  mu_check (dqd == &queue_data);
}

MU_TEST_SUITE (queue)
{
  MU_RUN_TEST (complex);
  MU_RUN_TEST (simple);
}

int
main (void)
{
  MU_RUN_SUITE (queue);
  MU_REPORT ();
  return MU_EXIT_CODE;
}