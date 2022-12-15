/********************************************************************
CSCI 480 - Assignment 1 - Fall 2022

Progammer: Francisco Banda
Section:   CSCI 480
Date Due:  09/16/2022

Purpose:   A program in C++ which uses fork system to start child
           process(es) in Linux. Simply for practicing system calls
           such as fork().

Sources:   https://www.delftstack.com/howto/cpp/cpp-fork/
           Used to understand fork() and process structuring
*********************************************************************/

#include <unistd.h>
#include <iostream>
#include <wait.h>

using namespace std;

int main()
{
    // Initial process creation, parent and child
    pid_t parent = fork();

    // Second process creation, intermediate and grand child
    pid_t child = fork();

    // If call fails, -1 is returned to the parent : error and exit.
    if (parent == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    
    // Parent process
    else if (parent > 0 && child > 0)
    {
        // PARENT: My PID is xxxx, my parent's PID is yyyy, my Children are wwww, zzzz.
        cout << "PARENT: My PID is " << getpid() << ", my parent's PID is " << getppid() << ", my children are " << parent << ", " << child << endl;

        // Sleeping just to try and make output look ideal
        sleep(1);

        // Invoke command "ps -f --ppid ..." to show all processes involved
        cout << "PARENT: Issuing command: /bin/ps -f --ppid " << getppid() << "," << getpid() << "," << parent << "," << child << endl;

        // Build string
        string command = "/bin/ps -f --ppid " + to_string(getppid()) + "," + to_string(getpid()) + "," + to_string(parent) + "," + to_string(child);

        // Load string
        const char *cmd = command.c_str();

        // Print string
        system(cmd);

        // Wait for finale, for better output
        wait(NULL);

        // End
        cout << "PARENT: Children processes are finished." << endl;
    }

    // Intermediate parent process
    else if (parent == 0 && child > 0)
    {
        cout << "INTERMEDIATE PARENT: My PID is " << getpid() << ", my parent's PID is " << getppid() << ", my child is " << child << "." << endl;

        // Sleep for 3 seconds, as mentioned
        sleep(3);

        cout << "INTERMEDIATE PARENT: " << getpid() << " is awake" << endl;

        // Exit process
        exit(EXIT_SUCCESS);
    }

    // Child process
    else if (parent > 0 && child == 0)
    {

        cout << "CHILD: My PID is " << getpid() << ", my parent's PID is " << getppid() << endl;

        // Sleep for 3 seconds, as mentioned
        sleep(3);

        cout << "CHILD: " << getpid() << " is awake" << endl;

        // Exit process
        exit(EXIT_SUCCESS);
    }

    // Grand child process
    else
    {
        cout << "GRAND CHILD: My PID is " << getpid() << ", my parent's PID is " << getppid() << endl;

        // Sleep for 3 seconds, as mentioned
        sleep(3);

        cout << "GRAND CHILD: " << getpid() << " is awake" << endl;

        // Exit process
        exit(EXIT_SUCCESS);
    }

    // End program
    return 0;

}