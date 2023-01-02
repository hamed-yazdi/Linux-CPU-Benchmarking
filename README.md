# Linux scheduling policies testing
To test and compare a subset of the Linux scheduling policies available, we follow the following steps to develop the <a href="https://github.com/hamed-yazdi/Linux-CPU-Benchmarking/blob/main/benchmark.c"> multithreaded program</a>:

<ol>
  <li>Choose the scheduling policies: <b>SCHED_OTHER, SCHED_BATCH, SCHED_IDLE, SCHED_FIFO, and SCHED_RR</b>.</li>
  <li>Write the program that creates multiple threads and assigns each thread to the same scheduling policy. We use the <b>"pthread_create"</b> function to create the threads. Each thread inherits the main program scheduling policies that was adjusted by sched_setattr function.
</li>
  <li>Write code to measure the throughput, latency, turnaround time and fairness of each thread. We use the <b>clock_t and tms</b> functions to measure the time taken for each thread to complete its work. The elapsed time of the program is also calculated by taking the difference between the start and end times.</li>
<li>Run the program on different Linux scheduling policy and record the results. We can use the <b>chrt -p "PID"</b> command to determine the the Linux scheduling policy of each thread we are running.</li>
 
<li>Analyze the results and compare the performance of the different scheduling policies. We can use charts and graphs (e.g., Powerbi tooltip) to visualize the results and make it easier to compare the performance of the different policies.</li>
  
</ol>

It's important to note that we need to have root privileges to set the scheduling policy for a thread.

This program creates 10 threads, each with a same scheduling policy. The "thread_func" function will be executed by each thread and measures the time taken for each thread to complete its work using the "clock_t and tms" function. The main function creates the threads and sets the scheduling policy for each the thread using the "pthread_attr_setschedpolicy" function. The program will be completed to calculate the elapsed time, real time, user time and system time for each thread and prints the results to the console. we are using them in order to measure such metrics like throughput, latency, turnaround time and fairness of each scheduling policy. 
 
# How to run the program
It is possible determin available scheduling policy based on the hosted kernel we can use "chrt -m" linux command in terminal. To run this program on different Linux scheduling policy, we need to cahnge pthread_attr_setschedpolicy function to rbitrary scheduling policy and check enabled policy by "chrt -p PID" in terminal.
 
 
To compile and run the program, we can use the following steps:
<ol> 
  <li>Open a terminal and navigate to the directory where the program is saved.</li>
  <li>Compile the program using the gcc command:  <pre>
  <code>
    gcc -o sched_test benchmark.c -lpthread
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
  <li> Choose a representative workload: The workload that we use to test the scheduling policies should be representative of the type of work that we expect the system to perform in practice. For example, if we test the scheduling policies for a database server, we should use workloads that are similar to the types of queries that the database will receive. In this benchmark tool CPU_bound workload is used for comparing. </li>
 
<li>  Use a sufficient number of threads: The number of threads that we use to test the scheduling policies should be sufficient to stress the system and give the meaningful results. The optimal number of threads will depend on the hardware and workload, but as a general rule, we should use at least as many threads as there are CPU cores on the system. </li> 
 
<li>  Run the tests for a sufficient amount of time: The tests should be run for a sufficient amount of time to get accurate and reliable results. The optimal test duration will depend on the workload and the hardware, but as a general rule, we should run the tests for at least several minutes to get a representative sample of the performance of the system. </li> 
 </ol> 
 
By following these guidelines, we can ensure that the program is adequate for testing the scheduling policies and is capable of running for a sufficient amount of time to draw conclusions.
 
Here is an example of a CPU-bound workload that we could use to test the scheduling policies:
 
<pre>
  <code>
    void workload() {
    /* Do some work */
    int z=0;
	  for(int i=0; i<1000; i++)
		  for(int j=0; j<1000; j++)
			  for(int k=0; k<1000; k++){
				  z++;
			  }
  </code>
</pre>


 
This workload function contains a loop that performs a large number of iterations. This can be used as a basic workload to test the scheduling policies under CPU pressure.
 
We can modify this workload function to perform more complex tasks, such as executing SQL queries on a database, performing calculations, or accessing files. The workload function should be representative of the type of work that we expect the system to perform in practice.





 
