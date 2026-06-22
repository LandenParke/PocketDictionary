#undef pthread_create
#include <pthread.h>
#include <errno.h>
#include "pthreadtest.h"

int pthread_createerr = 0;

int pthread_createtest(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg)
{
    return pthread_createerr ? EAGAIN : pthread_create(thread, attr, start_routine, arg);
}
