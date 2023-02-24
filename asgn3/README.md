#Assignment 3 directory

This directory contains source code and other files for Assignment 3.

Bijaya Khadka CSE 130 Professor Quinn, Thursday Feb 23, 2023

Comments on Design/Structure

	The queue was represented using a void pointer array data structure with each element being a void pointer to a value to be modified. This was done in order to meet the function requirements of passing void pointer arguments both in push and pop and because of the static preallocated size of the queue. This made the implementation simple because each void point element could be directly assigned and modified using array commands. For push this meant assigning the void pointer element in ascending order of the array and for pop, deferencing the front void pointer and then shifting all elements down so as to fulfill the FIFO characteristic. With this implementation there was no further modularity required. 

	Thread safety was implemented using semaphores as discussed in lecture. Three semphores were used: full, empty and a mtuex semaphore. The full and empty semaphores were placed in push and pop in order to block in the cases that a push is called and the queue is full or in the case that a pop is called and the queue is empty. Full is an N size semaphore that counts how much room is available in the queue. Finally, a mutex semaphore was used to lock each function's critical operations so that race conditions do not occur. 

Vague Requirements

	The main vague requirement was the implementation of the FIFO based queue which was resolved with the void pointer array data structure. Some specific requirements about queue testing was also not clear such as popping when there are no elements initially or whether thread safety will also be tested outside of the two primary functions of pop and push such as calling delete function amidst other threads modifying the queue. With delibration in discussion sections it was reassured that these edge cases would not be tested. 
	 
