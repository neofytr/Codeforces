CC = g++
CFLAGS = -Wall -std=c++20
MFLAGS = -fmodules-ts

main: Container.o List.o Vector.o testing.o
	$(CC) $(CFLAGS) Container.o List.o Vector.o testing.o -o main

testing.o: testing.cpp
	$(CC) $(CFLAGS) $(MFLAGS) testing.cpp -c testing.o

Container.o: Container.cpp
	$(CC) $(CFLAGS) $(MFLAGS) -x c++ Container.cpp -c

List.o: List.cpp
	$(CC) $(CFLAGS) $(MFLAGS) -x c++ List.cpp -c

Vector.o: Vector.cpp
	$(CC) $(CFLAGS) $(MFLAGS) Vector.cpp -c
lib:
	$(CC) $(CFLAGS) $(MFLAGS) -x c++-system-header iostream
	$(CC) $(CFLAGS) $(MFLAGS) -x c++-system-header cstddef
	$(CC) $(CFLAGS) $(MFLAGS) -x c++-system-header stdexcept

clean:
	rm -rf *.o main
