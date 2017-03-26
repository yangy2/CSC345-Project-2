all:
	
	gcc -c *c
	gcc -o Project2 Project2.c -lpthread

clean:
	rm Project2 *o
