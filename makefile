all: dine holes

dine: src/dine.c
	gcc -Wall -std=c99 -pthread src/dine.c -o bin/dine

holes: src/holes.c
	gcc -Wall -std=c99 src/holes.c -o bin/holes

clean:
	rm bin/*
	rm _output/*
