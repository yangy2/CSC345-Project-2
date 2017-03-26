/**
  * Written by Dr. Yoon on March 5, 2017 (rev. March 18, 2017)
  * Based   on Richard Levenson's initial attempt on the issue
  */
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>
#include <sched.h>
#define NUM_THREADS 4 
#define NUM_TO_RUN	100000

void *runner (void *param)
{
	int tid = *((int*)param);
	int total_primes = 0;

	printf("Thread #%d executing.\n", tid);
	
	/* wait 1 seconds for fair start and pretty-printing */
	sleep(1);

	/* the game: prime check */
	for (int i = 2; i < NUM_TO_RUN; ++i) {
		short isprime = 1;
		for (int j = 1; j < i; ++j) {
			if (i % j == 0 && j > 1) {
				isprime = 0;
				break;
			}
		}
		if (isprime > 0) {
			++total_primes;
		}
	}

	printf("Thread #%d found %d prime numbers in [1..%d]\n", 
			tid, total_primes, NUM_TO_RUN);

	pthread_exit(0);
}

int main(int argc, char **argv)
{
	int i, policy, errcode;
	int params[NUM_THREADS];
	pthread_t tid[NUM_THREADS];
	pthread_attr_t attr;
	struct sched_param schedparam;

	/* Uncomment following code to see why we cannot modify SCHED_OTHER directly */
	 struct rlimit rl;
	 getrlimit(RLIMIT_RTPRIO, &rl);
	 printf("soft = %d, hard = %d\n", (int)rl.rlim_cur, (int)rl.rlim_max);

	/* get the default attributes */
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

	/* set the scheduler to real-time round robin */
	pthread_attr_setschedpolicy(&attr, SCHED_RR);

	for (i = 0; i < NUM_THREADS; ++i) 
	{
		/* we give different priority to different thread, [1..99]; larger = higher */
		int myprio = (i + 1) * 5;
		schedparam.sched_priority = myprio;
		if ((errcode = pthread_attr_setschedparam(&attr, &schedparam)) != 0)
		{
			fprintf(stderr, "Error setting priority: ");
			switch (errcode)
			{
				case EINVAL:
					fprintf(stderr, "EINVAL\n"); break;
				case ENOTSUP:
					fprintf(stderr, "ENOTSUP\n"); break;
			};
		}

		/* parameter to hold thread ID */
		params[i] = i;

		/* create thread */
		if ((errcode = pthread_create(&tid[i], &attr, runner, &(params[i]))) != 0) 
		{
			fprintf(stderr, "Error creating thread: ");
			switch (errcode)
			{
				case EAGAIN: 
					fprintf(stderr, "EAGAIN\n"); break;
				case EINVAL:
					fprintf(stderr, "EINVAL\n"); break;
				case EPERM:
					fprintf(stderr, "EPERM\n"); break;
			};
		} 
		else 
		{
			printf("Thread #%d created with priority %d.\n", i, myprio);
		}
	}

	/* get the current thread's scheduling policy */
	printf("Reading scheduling policy...\n");
	if (pthread_attr_getschedpolicy(&attr, &policy) != 0)
	{
		fprintf(stderr, "Unable to get policy.\n");
	}
	else
	{
		if (policy == SCHED_OTHER)
			printf("main: SCHED_OTHER\n");
		else if (policy == SCHED_RR)
			printf("main: SCHED_RR\n");
		else if (policy == SCHED_FIFO)
			printf("main: SCHED_FIFO\n");
	}

	/* get each thread's scheduling policy */
	int get_policy[NUM_THREADS];
	struct sched_param get_param;
	printf("Reading policy from threads...\n");
	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_getschedparam(tid[i], &get_policy[i], &get_param);
		printf("Thread #%d: ", i);
		if (get_policy[i] == SCHED_OTHER)
			printf("SCHED_OTHER\n");
		else if (get_policy[i] == SCHED_RR)
			printf("SCHED_RR\n");
		else if (get_policy[i] == SCHED_FIFO)
			printf("SCHED_FIFO\n");
	}

	/* let the game begin... */
	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(tid[i], NULL);
	}

	return 0;
}

