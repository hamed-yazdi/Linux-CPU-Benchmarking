# Linux scheduling policies testing
To develop this multithreaded <a href="https://github.com/hamed-yazdi/Linux-CPU-Benchmarking/blob/main/benchmark.c">program</a> to test and compare a subset of the Linux scheduling policies available, we follow these steps:

<ol>
  <li>Choose the scheduling policies: <b>SCHED_OTHER, SCHED_BATCH, SCHED_IDLE, SCHED_FIFO, and SCHED_RR</b>.</li>
  <li>Write the program that creates multiple threads and assigns each thread to a different scheduling policy. We use the <b>"pthread_create"</b> function to create the threads and the <b>"pthread_setschedparam"</b> function to set the scheduling policy for each thread.
</li>
  <li>Write code to measure the throughput and latency of each thread. We use the <b>clock_gettime</b> function to measure the time taken for each thread to complete its work.
</li>Run the program on different Linux kernels and record the results. We can use the <b>uname</b> command to determine the version of the Linux kernel that we are running.</li>
 
<li>Analyze the results and compare the performance of the different scheduling policies. We can use charts and graphs (e.g., Powerbi tooltip) to visualize the results and make it easier to compare the performance of the different policies.</li>
  
</ol>

It's important to note that we need to have root privileges to set the scheduling policy for a thread. We can use the <b>seteuid</b> function to temporarily drop privileges, set the scheduling policy, and then restore privileges after the policy has been set.

This program creates 5 threads, each with a different scheduling policy. The "thread_func" function will be executed by each thread and sets the scheduling policy for the thread using the "pthread_setschedparam" function. The main function creates the threads and measures the time taken for each thread to complete its work using the "clock_gettime" function. The program will be completed to calculate the throughput and latency for each policy and prints the results to the console.
 
# How to run the program
To run this program on different Linux kernels, we need to compile and run the program on a system with each kernel that we want to test. we can use the "uname" command to determine the version of the Linux kernel that we are running.
 
 
To compile and run the program, we can use the following steps:
<ol> 
  <li>Open a terminal and navigate to the directory where the program is saved.</li>
  <li>Compile the program using the gcc command:  <pre>
  <code>
    gcc -o sched_test sched_test.c -lpthread
  </code>
</pre>
  This creates an executable file called "sched_test".
  </li>
  <li> Run the program using the ./sched_test command: </li>
  <pre>
  <code>
    ./sched_test
  </code>
</pre>

</ol>


# Ensure capability of the program with a workload
To ensure that the program is adequate for testing the scheduling policies and is capable of running for a sufficient amount of time to draw conclusions, we may want to consider the following:
<ol> 
  <li> Choose a representative workload: The workload that we use to test the scheduling policies should be representative of the type of work that we expect the system to perform in practice. For example, if we test the scheduling policies for a database server, we should use workloads that are similar to the types of queries that the database will receive.  </li>
 
<li>  Use a sufficient number of threads: The number of threads that we use to test the scheduling policies should be sufficient to stress the system and give the meaningful results. The optimal number of threads will depend on the hardware and workload, but as a general rule, we should use at least as many threads as there are CPU cores on the system. </li> 
 
<li>  Run the tests for a sufficient amount of time: The tests should be run for a sufficient amount of time to get accurate and reliable results. The optimal test duration will depend on the workload and the hardware, but as a general rule, we should run the tests for at least several minutes to get a representative sample of the performance of the system. </li> 
 </ol> 
 
By following these guidelines, we can ensure that the program is adequate for testing the scheduling policies and is capable of running for a sufficient amount of time to draw conclusions.
 
Here is an example of a workload that we could use to test the scheduling policies:
 
<pre>
  <code>
    void workload() {
    /* Do some work */
    int i;
    for (i = 0; i < 1000000000; i++);
    }
  </code>
</pre>


 
This workload function contains a loop that performs a large number of iterations. This can be used as a basic workload to test the scheduling policies.
 
We can modify this workload function to perform more complex tasks, such as executing SQL queries on a database, performing calculations, or accessing files. The workload function should be representative of the type of work that we expect the system to perform in practice.
 
Here is an example of how we could use the workload function in a thread:


<pre>
  <code>
  void * thread_func(void * arg) {
  thread_args * targ = (thread_args * ) arg;

  /* Set scheduling policy for the thread */
  struct sched_param param;
  param.sched_priority = sched_get_priority_max(targ -> policy);
  pthread_setschedparam(pthread_self(), targ -> policy, ¶m);

  /* Do some work */
  workload();

  return NULL;
}
  </code>
</pre>



 
