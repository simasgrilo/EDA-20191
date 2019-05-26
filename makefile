all: ABB ARVG 
	gcc main.c objects/abb.o objects/arvg.o  -o main -lm
ABB:
	mkdir -p objects
	gcc -c abb.c -o objects/abb.o
ARVG: 
	mkdir -p objects
	gcc -c arvg.c -o objects/arvg.o 
debug: CATONUXMV STATE INPUT
	gcc -g main.c objects/abb.o objects/arvg.o  -o main
clean:
	rm -rf objects/*.o