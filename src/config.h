#if !defined(__CONFIG_H__)
#define __CONFIG_H__

/* These are the constant values and default
   config values if any/none are provided. */
enum
{
  BACKLOG = 9,
  PORT = 8080,
  THREAD_COUNT = 8
};

typedef struct
{
  int backlog;
  int port;
  int thread_count;
} configurations_t;

/*! @brief get application configurations
 *
 *  @return a struct containing the required configurations
 */
configurations_t get_config(void);

#endif // __CONFIG_H__
