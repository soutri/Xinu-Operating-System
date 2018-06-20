#ifndef PROCESS_RING_H
#define PROCESS_RING_H
#define DEFAULT_PROCS 2
#define DEFAULT_ROUNDS 3

poll(volatile int32*,int32,int32,int32);
sem_syn(volatile int32*,int32,int32,sid32,sid32,sid32,int32);
#endif
