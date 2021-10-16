#if !defined(__SERVER_H__)
#define __SERVER_H__

#if !defined(__SERVER_H_STDDEF__)
#define __SERVER_H_STDDEF__

#include <stddef.h>

#endif /* __SERVER_H_STDDEF__ */

typedef struct client_props *p_cprops_t;
typedef struct server_props *p_sprops_t;

/*! @brief  accept a new client connection
 *
 *  @param[in]  server pointer to the server
 *  instace to accept the connection
 *
 *  @return client pointer to the connected
 *  client instance
 *
 */
p_cprops_t accept_connection(p_sprops_t);

/*! @brief  disposes the client connection and
 *  frees its resources
 *
 *  @param[in]  client pointer to the client
 *  object
 */
void disconnect_client(p_cprops_t);

/*! @brief  disposes the server object and
 *  frees its resources
 *
 *  @param[in]  server pointer to the server
 *  object
 */
void dispose_server(p_sprops_t);

/*! @brief  initializes the server object.
 *
 *  @param[in]  backlog desired server backlog
 *  count
 *
 *  @param[in]  port desired port for the server
 *  to listen for traffic on
 *
 *  @return pointer to the server object
 */
p_sprops_t initialize_server(int, int);

/*! @brief receive a blob of data from the client
 *
 *  @param[in] client the client from which to receive data
 *
 *  @param[in] data blob in which to put the received data
 *
 *  @param[in] nbytes max size of the data blob
 *
 *  @return number of bytes actually received
 */
size_t get_from_client(p_cprops_t, void *, size_t);

/*! @brief sends data to the client
 *
 *  @param[in] client pointer to the client object
 *
 *  @param[in] data data blob to send to the client
 *
 *  @param[in] count size (in bytes) of the data blob
 *
 *  @return number of bytes actually sent to the client
 */
size_t send_to_client(p_cprops_t, void *, size_t);

#endif /* __SERVER_H__ */
