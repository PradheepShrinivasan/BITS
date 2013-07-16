hashtable: hashtable.o main.o
	gcc -g -Wall -o hashtable hashtable.o main.o

main.o:main.c hashtable.h
	gcc -c -Wall -g main.c

hashtable.o: hashtable.h hashtable.c
	gcc -c -g -Wall hashtable.c

clean:
	rm *.o
	rm hashtable
	rm *.csv
