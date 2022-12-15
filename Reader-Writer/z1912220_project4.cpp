/********************************************************************
CSCI 480 - Assignment 4 - Fall 2022

Progammer: Francisco Banda
Section:   CSCI 480
Date Due:  11/06/2022

Purpose:   A program in C++ which solves the Reader-Writer problem
		using the PThreads library and by taking in two command
		line arguments, in order to get practice using semaphores.

Extra Sources:
https://www.bogotobogo.com/cplusplus/multithreading_pthread.php
*********************************************************************/

#include <unistd.h>
#include <iostream>
#include <wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Global variables
string string1 = "All work and no play makes Jack a dull boy.";
sem_t rw_sem; // Used by both readers and writers
sem_t cs_sem; // Used for protecting critical sections of readers
int threadCount = 0;

void* writer(void* param)
{
	// Writer variables
	long threadID = (long)param;

	// Loop until string is empty
	while (!string1.empty())
	{
		// Print writing message
		printf("Writer %ld is writing...\n", threadID);

		// Wait for writer
		sem_wait(&rw_sem);

		// Writing (chopping the last character) until empty
		if (!string1.empty())
		{
			string1.pop_back();
		}

		// Signal
		sem_post(&rw_sem);

		// Sleep for a second
		sleep(1);
	}

	// Exit writer thread
	return 0;
}

void* reader(void* param)
{
	// Reader variables
	long threadID = (long)param;

	// Loop until string is empty
	while (!string1.empty())
	{
		// Access critical section
		sem_wait(&cs_sem);

		// Increment threadCount
		threadCount++;

		// Signal rw_sem
		if (threadCount == 1)
		{
			sem_wait(&rw_sem);
		}

		// Exit critical section
		sem_post(&cs_sem);

		// Print reading message
		printf("Reader %ld is reading... %s\n", threadID, string1.c_str());

		// Access critical section
		sem_wait(&cs_sem);

		// Decrement threadCount
		threadCount--;

		// Signal rw_sem
		if (threadCount == 0)
		{
			sem_post(&rw_sem);
		}

		// Exit critical section
		sem_post(&cs_sem);

		// Sleep for a second
		sleep(1);
	}

	// Exit writer thread
	return 0;
}

int main(int argc, char* argv[])
{
	// Main variables
	int numReaderThreads = 0;
	int numWriterThreads = 0;
	long i;

	// Error-check command-line arguments
	if (argc != 3)
	{
		perror("Invalid arguments\n");
		return -1;
	}

	// Initialize and error check numReaderThreads/numWriterThreads
	if ((numReaderThreads = atoi(argv[1])) < 0 || (numWriterThreads = atoi(argv[2])) < 0)
	{
		printf("Invalid number of reader/writer threads\n");
		return -1;
	}

	// Initialize semaphores (cs_sem/rw_sem)
	if (sem_init(&rw_sem, 0, 1) == -1)
	{
		printf("sem_init operation on rw_sem was not successful.");
	}
	if (sem_init(&cs_sem, 0, 1) == -1)
	{
		printf("sem_init operation on cs_sem was not successful.");
	}

	// Initialize reader/writer threads
	pthread_t ReaderThreads[numReaderThreads];
	pthread_t WriterThreads[numWriterThreads];

	// Create reader threads
	for (i = 0; i < numReaderThreads; i++)
	{
		pthread_create(&ReaderThreads[i], NULL, &reader, (void*)i);
	}

	// Create writer threads
	for (i = 0; i < numWriterThreads; i++)
	{
		pthread_create(&WriterThreads[i], NULL, &writer, (void*)i);
	}

	// Wait for reader threads to finish
	for (i = 0; i < numReaderThreads; i++)
	{
		pthread_join(ReaderThreads[i], NULL);
	}

	// Wait for writer threads to finish
	for (i = 0; i < numWriterThreads; i++)
	{
		pthread_join(WriterThreads[i], NULL);
	}

	// Clean up
	sem_destroy(&cs_sem);
	sem_destroy(&rw_sem);

	// Exit
	pthread_exit(NULL);
}