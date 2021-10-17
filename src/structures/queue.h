#if !defined(__QUEUE_H__)
#define __QUEUE_H__

/*! @brief dequeue data from the front of the queue
 *
 *  @return the data blob that was at the front of the queue
 */
void *dequeue(void);

/*! @brief enqueue data to the end of the queue
 *
 *  @param[in] data data blob to enqueue to the end of the queue
 */
void enqueue(void *);

#endif /* __QUEUE_H__ */
