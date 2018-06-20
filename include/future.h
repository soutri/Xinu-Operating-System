#ifndef _FUTURE_H_
#define _FUTURE_H_  

typedef enum {
  FUTURE_EMPTY,
  FUTURE_WAITING,
  FUTURE_READY
} future_state_t;

typedef enum {
  FUTURE_EXCLUSIVE,
  FUTURE_SHARED,
  FUTURE_QUEUE
} future_mode_t;


struct queue_t
{
	int data;
	struct queue_t* next;
	
};

typedef struct {
  int value;
  future_state_t state;
  future_mode_t mode;
  pid32 pid;
 struct queue_t* set_queue;
 struct queue_t* get_queue;
} future_t;

/* Interface for the Futures system calls */
future_t* future_alloc(future_mode_t mode);
syscall future_free(future_t*);
syscall future_get(future_t*, int*);
syscall future_set(future_t*, int);
 
#endif /* _FUTURE_H_ */

