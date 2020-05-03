tema2: main.o lock_functions.o
	g++ -o tema2 main.o lock_functions.o

lock_functions.o: lock_functions.cpp
	g++ -c lock_functions.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f tema2 main.o lock_functions.o semafor sortat.txt
zip:
	tar -czf tema2.tar.gz main.cpp lock_functions.cpp lock_functions.h Makefile