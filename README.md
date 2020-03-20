# **Threading-C**
This repository is a demonstration of using the Pthreads.h library to emulate threading in C. The repository contains solutions to the dinning philosophers problem and memory allocation.
*****************
## **1. Dinning Philosophers**
   ### This program is meant to solve the dining philosophers problem. The program uses threads to carry out every action of the philosophers (in this case eating, sleeping or thinking). Semaphores to lock and fork so that there is no chance for a lock out. It takes in user input through command line arguments to tailor the program to work with specified values.

   Compile:  **make dine**

   Run Program:  **./bin/dine `<num philosopher>` `<num times eaten>`**

## **2. Memory Allocation Simulator**
   ### The program emulates memory allocation by taking in processes and trying to allocate them to a memory of 128 mbs. Using different methods to fit processes in. I used linked lists as a queue to hold the processes. After that I store them in an array which represents the memory. Using first fit I allocate the ram. And using linked lists commands, I can manipulate the queue to add processes to the back when they are replaced in memory until the program is done.


   Compile:  **make holes**

   Run Program:  **./bin/holes `<textFile>`**

**********
**make all** command will compile all files
