graph:main.o graph.o
	gcc  -g -Wall -o graph main.o graph.o
main.o: main.c graph.h
	gcc -c -g -Wall main.c
graph.o:graph.c graph.h
	gcc -c -g -Wall graph.c
clean:
	rm *.o
	rm graph
