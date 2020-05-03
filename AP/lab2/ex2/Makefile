file_operations: main.o
	gcc -o file_operations main.o

main.o: main.c
	gcc -c main.c

clean:
	rm -f file_operations main.o ex2.tar.gz
zip:
	tar -czf ex2.tar.gz main.c