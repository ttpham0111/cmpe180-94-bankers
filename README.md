# Project Topic: Banker’s Algorithm

## Introduction:
The Banker's algorithm is a resource allocation and deadlock avoidance algorithm developed by Edsger Dijkstra that tests for safety by simulating the allocation of pre-determined maximum possible amounts of all resources, and then makes a "safe-state" check to test for possible deadlock conditions for all other pending activities, before deciding whether allocation should be allowed to continue. (Source: Wikipedia). The name is chosen as such because this algorithm could be used by banks to safely allocate cash to their customers.

## Objective:
In this project we are going to write a multithreaded program that will implement the Banker’s Algorithm in which several customers request and release resources from the bank. The banker will consider requests from n customers for m resources types.

If the request leaves the system in a safe state, then the banker will grant that request. All requests that leaves the bank in an unsafe state will be denied. The program will be invoked  by passing the number of resources of each type on the command line.

The following topics will be covered as part of our project:
- Multithreading
- Preventing race conditions
- Deadlock avoidance
- Detection-and-recovery scheme

Project Schedule:

09/24/2016 to 10/04/2016 - Project Design
10/05/2016 to 11/10/2016 - Project Implementation
11/11/2016 to 11/17/2016 - Project Report
11/18/2016 to 11/23/2016 - Project Presentation

Conclusion:
By completing the Banker’s Algorithm we will be implementing a multithreaded computer program that help us discover the different strategies in resolving conflicts in resource allocation and task scheduling. This project would simulate the functionality of a task scheduler and improve the understanding of the operating system.
