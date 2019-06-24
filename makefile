target:test

test:main.c lib.c lib.h
	gcc main.c lib.c -lm -o test
	./test