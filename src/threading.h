#if !defined(__THREADING_H__)
#define __THREADING_H__

#if !defined(__THREADING_T_PTHREAD__)
#define __THREADING_T_PTHREAD__

#include <pthread.h>

#endif /* __THREADING_T_PTHREAD__ */

typedef struct
{
  void *client_data;
} payload_t;

/*! @brief this function is the main server function,
 *  which is to live on its own thread, running asyncronously
 *
 *  @param[in] args arguments for the thread, it is expected to
 *  be a pointer to <payload_t>
 *
 *  @return is always expected to be NULL
 */
void *server_thread(void*);

#endif /* __THREADING_H__ */