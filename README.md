# Multithreading Training

This project's aim is to learn in detail about multithreaded programming. The tasks are given and reviewed by my mentor.

## 01 - Pi Calculation Leibniz
Write a program that calculates pi using Leibniz's series. The number of threads of the program must be determined by the command line parameter. The number of iterations can be determined at compile time. 

## 02 - Sleepsort
Implement a unique sleepsort algorithm with O(log(n)) asymptotics (in CPU time).
The standard input of the program is not more than 100 strings of different lengths. You need to output these strings, sorted by length. Strings of equal length can be output in any order.

For each input string, create a thread and pass it to this string as a parameter. The thread should call sleep with a parameter proportional to the length of that string. The thread then outputs the string to the standard output stream and terminates. You should not choose the proportionality factor too small, you risk incorrect sorting.

## 03 - Recursive copy
Implement a multithreaded program for recursive copying of a subdirectory tree, a functional analog of the cp command with the -R key. The program must accept two parameters - the full pathname of the source tree's root directory and the full pathname of the target tree. 
For each subdirectory, a directory of the same name should be created in the target tree and a separate thread that traverses that subdirectory should be started. For each regular file, a thread should be started that copies that file to the target tree file of the same name. Files of other types (symbolic links, named pipes, etc.) should be ignored.

## 04 - Dining Philosophers Problem
This program simulates the famous problem of philosophers having lunch. Five philosophers sit around a round table and eat spaghetti. The spaghetti is eaten with two forks. Each of the two philosophers sitting next to each other uses a common fork. The philosopher ponders for a while, then tries to pick up the forks and starts eating. After eating some spaghetti, the philosopher releases the fork and starts thinking again. After some more time, he takes up the food again, and so on until the spaghetti runs out. If one of the forks fails, the philosopher waits until it is free. In the program, philosophers are simulated with threads, periods of thinking and eating are simulated with sleep, and forks are simulated with mutexes. Philosophers always take the left fork first, then the right. Under some circumstances, this can lead to deadlocks. Change the protocol for the interaction of philosophers with forks so that deadlocks do not occur.

## 05 - Synchronized output
Write a program that creates a thread. Use the default attributes. The parent and newly created threads should print ten lines of text. Modify the program so that the output of the parent and child threads is synchronized: first, the parent thread outputs the first line, then the child, then the parent the second line, and so on. 

## 06 - Synchronized and sorted list
The parent thread of the program must read the user-entered strings and place them at the beginning of the linked list. When an empty string is entered, the program should output the current state of the list. The child thread wakes up every five seconds and sorts the list in lexicographical order (use bubble sorting). All operations on the list must be synchronized using a mutex.

## 07 - Counting semaphore
Develop a simulation of a production line that makes screws (widgets). A screw is assembled from part C and a module, which in turn consists of parts A and B. It takes 1 second to make part A, two seconds for part B, and three seconds for part C. Simulate the delay in making the parts with sleep. Use semaphore counters.

## 08 - Producer comsumer

Implement a message queue that can be used to exchange data between two or more threads. 

The push method takes a character string as an ASCIIZ parameter and places it in the queue. If the queue contains more than 10 entries, push is blocked. 
The pop method returns the first entry from the queue. In either case, the entire entry is retrieved from the queue. If the queue is empty, pop is blocked. The function returns the extracted string.
The drop method must cause pending push and pop operations to be unblocked. Pending calls and all subsequent push and pop calls must return 0.

It is necessary to demonstrate queue operation with two producers and two consumers.

To synchronize access to the queue, use conditional variables and the minimum required number of mutexes.