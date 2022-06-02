all: compile exec clean
compile:
	gcc main.c utilities.c -pthread -o pout
exec:
	./pout
clean:
	rm -rfv pout
