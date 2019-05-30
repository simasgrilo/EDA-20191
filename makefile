all: ABB ARVG AB
	gcc main.c objects/abb.o objects/arvg.o objects/ab.o  -o main -lm
ABB:
	mkdir -p objects
	gcc -c abb.c -o objects/abb.o
ARVG: 
	mkdir -p objects
	gcc -c arvg.c -o objects/arvg.o 
AB:
	mkdir -p objects
	gcc -c ab.c -o objects/ab.o 
debug: ABB ARVG AB
	gcc -g main.c objects/abb.o objects/arvg.o objects/ab.o -o main -lm
clean:
	rm -rf objects/*.o