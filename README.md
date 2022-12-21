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
