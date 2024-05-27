all: 
	gcc 1.c o- 1
	gcc 2.c o- 2
	gcc 3.c o- 3
clean:
	rm 1
	rm 2
	rm 3
