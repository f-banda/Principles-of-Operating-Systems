#
# PROGRAM: Assignment 4
# AUTHOR:  Francisco Banda
#
  CC = g++
  CXXFLAGS = -Wall -g -pthread

  all: z1912220_project4 z1912220_project4_p2

  z1912220_project4: z1912220_project4.o
		$(CC) -o z1912220_project4 $(CXXFLAGS) z1912220_project4.o

  z1912220_project4.o: z1912220_project4.cpp
		$(CC) -c $(CXXFLAGS) z1912220_project4.cpp

  z1912220_project4_p2: z1912220_project4_p2.o
		$(CC) -o z1912220_project4_p2 $(CXXFLAGS) z1912220_project4_p2.o

  z1912220_project4_p2.o: z1912220_project4_p2.cpp
		$(CC) -c $(CXXFLAGS) z1912220_project4_p2.cpp

  clean: 
		rm -f *.o z1912220_project4 z1912220_project4_p2