**Getting Familiar With Linux**

__Find the variant of the ls command (i.e. argument(s) to be used) to list contents of a folder including its hidden files, the variant of cp to copy folder and the command to rename a file.__

Ans:   The variant of ls command to list contents of a folder including hidden files is: ls -a.
          The variant of cp to copy folder: cp -avr
          The command to rename a file: sudo apt-get install rename


__In this question, we will understand the hardware configuration of your working machine using the /proc filesystem.__
__Run command more /proc/cpuinfo and explain the following terms: processor and cores. Use the command lscpu to verify your definitions.__
    -How many CPU sockets, cores, and processors does your machine have?
        Sockets: 1
        Cores: 6
        Processors: 12
    -What is the frequency of each processor?
        3.00 GHz
    -How much memory does your machine have?
        8.00 GB
    -How much of it is free and available? What is the difference between them?
        Free: 3 GB, Available: 6 GB
        The difference between free memory vs. available memory in Linux is, free memory is not in use and sits there doing nothing. While available memory is used memory that includes but is not limited to caches and buffers, that can be freed without the performance penalty of using swap space.
    -What is the total number of user-level processes in the system?
        8
    -What is the total number of forks since the boot in the system?
        345
    -How many context switches has the system performed since bootup?
        2

__In this question, we will understand how to monitor the status of a running process using the top command. Compile the program cpu.c given to you and execute it in the bash or any other shell of your choice as follows.__
>gcc --version
># If gcc is not installed then run :- sudo apt-get install gcc
>gcc cpu.c -o cpu
>./cpu
This program runs in an infinite loop without terminating. Now open another terminal, run the top command and answer the following questions about the cpu process.
    -What is the PID of the process running the cpu command?
        7261
    -How much CPU and memory does this process consume?
        100% and 0%
    -What is the current state of the process? For example, is it running or in a blocked state or a zombie state?
        Running







