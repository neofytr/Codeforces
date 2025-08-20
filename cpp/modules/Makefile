CC = g++
CFLAGS = -Wall -std=c++20
MFLAGS = -fmodules-ts

main: Vector.o testing.o
	$(CC) $(CFLAGS) testing.o Vector.o -o main

testing.o: testing.cpp
	$(CC) $(CFLAGS) $(MFLAGS) testing.cpp -c testing.o

Vector.o: Vector.ixx Vector.cpp
	$(CC) $(CFLAGS) $(MFLAGS) -x c++ Vector.ixx -c -o .interfaceVec
	$(CC) $(CFLAGS) $(MFLAGS) Vector.cpp -c
	rm .interfaceVec # we can remove this temp and not use it while linking with the module
					 # since the module interface file doesn't contain anything that requires
 		     		 # external linkages; we only need to link with the module implementation while
 		     		 # when using the module
lib:
	$(CC) $(CFLAGS) $(MFLAGS) -x c++-system-header iostream
	$(CC) $(CFLAGS) $(MFLAGS) -x c++-system-header cstddef
	$(CC) $(CFLAGS) $(MFLAGS) -x c++-system-header stdexcept

clean:
	rm -rf *.o main
