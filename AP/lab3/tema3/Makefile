tema3: main.o lock_functions.o
	g++ -o tema3 main.o lock_functions.o

lock_functions.o: lock_functions.cpp
	g++ -c lock_functions.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f tema3 main.o lock_functions.o semafor sortat.txt nesortat.txt
zip:
	tar -czf tema3.tar.gz main.cpp lock_functions.cpp lock_functions.h Makefile