#include "queue.h"

#include <stdlib.h>

typedef struct q
{
  void *data;
  struct q *next;
} q_t;

static q_t *head = NULL;
static q_t *tail = NULL;

void *
dequeue (void)
{
  void *data;
  q_t *old_head = head;
  if (head == NULL)
    return NULL;

  data = head->data;
  head = head->next;
  old_head->data = NULL;
  old_head->next = NULL;

  if (head == NULL)
    tail = NULL;

  free (old_head);
  return data;
}

void
enqueue (void *data)
{
  q_t *new_tail = malloc (sizeof (q_t));
  if (new_tail == NULL)
    return;

  new_tail->data = data;
  new_tail->next = NULL;

  if (head == NULL)
    {
      head = new_tail;
      tail = new_tail;
      return;
    }

  tail->next = new_tail;
  tail = new_tail;
}
