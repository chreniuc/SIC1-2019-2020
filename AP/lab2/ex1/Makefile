stiva: functii.o main.o
	gcc -o stiva functii.o main.o

functii.o: functii.h functii.c
	gcc -c functii.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f stiva main.o functii.o ex1.tar.gz
zip:
	tar -czf ex1.tar.gz main.c functii.h functii.c