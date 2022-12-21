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
 
To run this program on different Linux kernels, we need to compile and run the program on a system with each kernel that you want to test. You can use the "uname" command to determine the version of the Linux kernel that we are running.
 
 
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
  
</ol>
