/*
 * This program is developed in order compare performance
 * of different Linux scheduling policies such as FIFO, RR,
 * OTHER (CFS), DEADLINE, BATCH and IDLE.
 * By this way, the main function runs a CPU based process as multi-thread.
 *
 * The Real Time, User Time and System Time of each thread is calculated. In addition,
 * total execution time of this program calculated in order to measure such
 * interesting metrics like turnaround time, latency, fairness and efficiency
 * of each scheduling policy in Linux machines.
 *
 */

#include <time.h>
#include <linux/time.h>
#include <sys/times.h>
#include <sched.h>
#include <linux/sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 10

/*create arrays for keep necessary times*/
static clock_t st_time[NUM_THREADS];
static clock_t en_time[NUM_THREADS];
static struct tms st_cpu[NUM_THREADS];
static struct tms en_cpu[NUM_THREADS];

/*CPU-bound function*/
void *thread_func(void *arg) {
    int tid;
	tid = (int)arg;
	st_time[tid] = times(&st_cpu[tid]);
	int z=0;
	for(int i=0; i<1000; i++)
		for(int j=0; j<1000; j++)
			for(int k=0; k<1000; k++){
				z++;
			}
	en_time[tid] = times(&en_cpu[tid]);
	pthread_exit(NULL);
}

/*show collected times in terminal*/
void show_result(){
	/*print Real Time, User Time and System Time of each thread*/
	for(int tid = 0; tid < NUM_THREADS; tid++){
		double rt = (double)(en_time[tid] - st_time[tid]) / CLOCKS_PER_SEC*10000;
		double ut = (double)(en_cpu[tid].tms_utime - st_cpu[tid].tms_utime) / CLOCKS_PER_SEC*10000;
		double st = (double)(en_cpu[tid].tms_stime - st_cpu[tid].tms_stime) / CLOCKS_PER_SEC*10000;
		printf("Thread %d --> Real Time: %f, User Time %f, System Time %f\n",tid, rt, ut,st);
	}
	/*calculate Elapsed time of program by measure
	 *  end time of the latest thread - start time of the first thread*/
	clock_t end = en_time[0];
	clock_t start = st_time[0];
	for(int tid = 0; tid < NUM_THREADS; tid++){
		if(start > st_time[tid])
			start = st_time[tid];
		if(end < en_time[tid])
			end = en_time[tid];
	}
	double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC*10000;
	printf("Total Elapsed Time: %f\n",elapsed_time);
}

int main(){
	/*define attributes of scheduling policy */
	int policy;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	if(pthread_attr_getschedpolicy(&attr, &policy) != 0)
	        fprintf(stderr, "Unable to get policy.\n");
	    else{
	        if(policy == SCHED_OTHER)
	            printf("SCHED_OTHER\n");
	        else if(policy == SCHED_RR)
	            printf("SCHED_RR\n");
	        else if(policy == SCHED_FIFO)
	            printf("SCHED_FIFO\n");
	    }
	if(pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0)
	        fprintf(stderr, "Unable to set policy.\n");
	/*define multi-thread processes */
	pthread_t threads[NUM_THREADS];
	for( int i = 0; i < NUM_THREADS; i++ ){
		pthread_create(&threads[i], &attr, thread_func, (void *)i);
	}
	/*wait for finishing all threads*/
	for(int tid = 0; tid < NUM_THREADS; tid++){
		sleep(10);
		if(en_cpu[tid].tms_stime != NULL){
			continue;
		}
		else{
			printf("Benchmark is running\n");
		}
	}
	/*print aggregated times in terminal*/
	show_result();
	pthread_exit(NULL);
}



