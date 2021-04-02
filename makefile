CC = g++
exe_file = assignment1
$(exe_file): assignment1.o prog.o
	$(CC) assignment1.o prog.o -o $(exe_file)
assignment1.o: assignment1.cpp
	$(CC) -c assignment1.cpp
prog.o: prog.cpp
	$(CC) -c prog.cpp

clean:
	rm -f *.out *.o $(exe_file)
