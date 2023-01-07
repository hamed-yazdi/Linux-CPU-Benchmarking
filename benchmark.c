#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <linux/sched.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>
#include <sys/times.h>
#define NUM_THREADS 10
int counter=0;

/*create arrays for keep necessary times*/
static clock_t st_time[NUM_THREADS];
static clock_t en_time[NUM_THREADS];
static struct tms st_cpu[NUM_THREADS];
static struct tms en_cpu[NUM_THREADS];

/*define structure to keep scheduler attributes*/
struct sched_attr {
    uint32_t size;
    uint32_t sched_policy;
    uint64_t sched_flags;
    int32_t sched_nice;
    uint32_t sched_priority;
    uint64_t sched_runtime;
    uint64_t sched_deadline;
    uint64_t sched_period;
};

/*apply desired scheduling policy to the current thread*/
int sched_setattr(pid_t pid, const struct sched_attr *attr, unsigned int flags) {
    return syscall(__NR_sched_setattr, pid, attr, flags);
}
/*CPU_bound workload*/
void Func_cpu(void *arg){
	int tid;
	tid = (int)arg;
	st_time[tid] = times(&st_cpu[tid]);
	int z=0;
	for(int i=0; i<1000; i++)
		for(int j=0; j<1000; j++){
			z=0;
			for(int k=0; k<1000; k++)
				z++;
		}
	en_time[tid] = times(&en_cpu[tid]);
	counter++;
	pthread_exit(NULL);
}
/*show collected times in terminal and write them in a file*/
void show_result(){
	printf("result start\n");
	FILE *fpt;
	fpt = fopen("MyFile.csv", "w+");
	fprintf(fpt,"thread_id, Start_time, End_time, Real_time, User_time, System_time, Elapsed_time\n");
	/*print Real Time, User Time and System Time of each thread*/
	for(int tid = 0; tid < NUM_THREADS; tid++){
		double rt = (double)(en_time[tid] - st_time[tid]) / CLOCKS_PER_SEC*10000;
		double ut = (double)(en_cpu[tid].tms_utime - st_cpu[tid].tms_utime) / CLOCKS_PER_SEC*10000;
		double st = (double)(en_cpu[tid].tms_stime - st_cpu[tid].tms_stime) / CLOCKS_PER_SEC*10000;
		printf("Thread %d --> Real Time: %f, User Time %f, System Time %f  --> en_time %d, st_time %d\n",tid, rt, ut,st,en_time[tid],st_time[tid]);
		fprintf(fpt,"%d, %d, %d, %f, %f, %f\n", tid, st_time[tid], en_time[tid], rt, ut, st);

	}
	/*calculate Elapsed time of program by measure
	 * end time of the latest thread - start time of the first thread*/
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
	fprintf(fpt,"%d, %d, %d, %f, %f, %f, %d\n",NULL, NULL, NULL, NULL, NULL, NULL, elapsed_time);
	fclose(fpt);
}

int main() {
	/*Set schedule policy attributes*/
    struct sched_attr attr = {
            .size = sizeof (attr),
            .sched_policy = SCHED_FIFO,
            .sched_priority = 1,
        };
    /*struct sched_attr attr = {
            .size = sizeof (attr),
            .sched_policy = SCHED_RR,
            .sched_priority = 1,
        };*/
    /*struct sched_attr attr = {
            .size = sizeof (attr),
            .sched_policy = SCHED_OTHER,
            .sched_priority = 0,
    		.sched_nice = 0,
        };*/
    /*struct sched_attr attr = {
            .size = sizeof (attr),
            .sched_policy = SCHED_DEADLINE,
            .sched_runtime = 10 * 1000 * 1000,
            .sched_period = 30 * 1000 * 1000,
            .sched_deadline = 1 * 1000 * 1000,
        };*/
    /*struct sched_attr attr = {
            .size = sizeof (attr),
            .sched_policy = SCHED_BATCH,
            .sched_priority = 0,
    		.sched_nice = 0,
        };*/
    sched_setattr(0, &attr, 0);
    /*define multi-thread processes */
    pthread_t pthreadA[NUM_THREADS];
    for(int i=0; i<NUM_THREADS; i++){
    	pthread_create(&pthreadA[i], NULL, Func_cpu, (void *)i);
    }
    /*Role back main scheduling policy to OTHER*/
    struct sched_attr attr_main_roleback = {
            .size = sizeof (attr_main_roleback),
            .sched_policy = SCHED_OTHER,
            .sched_priority = 0,
    		.sched_nice = 0,

        };
    sched_setattr(0, &attr_main_roleback, 0);
    /*wait for finishing all threads*/
    for(;;){
    	if(counter == NUM_THREADS)
    		break;
    }
    /*print aggregated times in terminal*/
    show_result();
    pthread_exit(0);
    return (EXIT_SUCCESS);
}
