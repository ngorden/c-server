#if !defined(__THREADING_H__)
#define __THREADING_H__

#if !defined(__THREADING_T_PTHREAD__)
#define __THREADING_T_PTHREAD__

#include <pthread.h>

#endif /* __THREADING_T_PTHREAD__ */

typedef struct
{
  pthread_cond_t* cond;
  pthread_mutex_t* mutex;
} payload_t;

/*! @brief initialize the threading objects needed
 *
 *  @param[in] cfg pointer to the application
 *  configuration
 *
 *  @param[in] pld pointer to the payload to be sent to
 *  the server thread
 *
 *  @return pointer to the thread objects
 */
pthread_t *initialize_threads (void*, payload_t* );

/*! @brief cleanup the threading objects at the end of use
 *
 *  @param[in] cfg pointer to the application configuration
 *
 *  @param[in] thread pointer the the thread objects
 *
 *  @param[in] cnd pointer to the condition variable
 */
void thread_cleanup (void*, pthread_t *, pthread_cond_t*);

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
