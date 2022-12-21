The purpose of this program is to evaluate the performance of various Linux scheduling policies, including FIFO, RR, CFS, DEADLINE, BATCH, and IDLE. The main function of the program runs a CPU-based process as multiple threads. The Real Time, User Time, and System Time of each thread are calculated, as well as the total execution time of the program, in order to assess metrics such as turnaround time, latency, fairness, and efficiency of each scheduling policy on Linux machines.

To develop a multithreaded program to test and compare a subset of the Linux scheduling policies available, we follow these steps:

  1-  Choose the scheduling policies: SCHED_OTHER, SCHED_BATCH, SCHED_IDLE, SCHED_FIFO, and SCHED_RR.
  
  2-  Write a program that creates multiple threads and assigns each thread to a different scheduling policy. We use the "pthread_create" function to create the threads and the "pthread_setschedparam" function to set the scheduling policy for each thread.
