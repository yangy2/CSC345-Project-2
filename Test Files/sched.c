#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static void *thread(void *unused)
{
        struct sched_param p;
        int policy;

        pthread_getschedparam(pthread_self(), &policy, &p);

        fprintf(stderr, "priority = %d, policy = %d\n", p.sched_priority,
		policy);

        pthread_exit("DONE");
}

int main(void)
{
        pthread_attr_t attr;
        struct sched_param p;
        pthread_t tid;

        pthread_attr_init(&attr);
        pthread_attr_setschedpolicy(&attr, SCHED_RR);
        p.sched_priority = 10;
        pthread_attr_setschedparam(&attr, &p);
        pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

        pthread_create(&tid, &attr, thread, NULL);
        pthread_join(tid, NULL);

        return 0;
}
