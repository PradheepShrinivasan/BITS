#make file for problem 1

Number:Number.o sorting.o main.o Base.o
	g++ -o Number -g -Wall Base.o Number.o sorting.o main.o

main.o: main.cpp  sorting.h Number.h 
	g++ -c -g -Wall main.cpp

Number.o: Number.h Number.cpp
	g++ -c -g -Wall Number.cpp

sorting.o: sorting.h sorting.cpp
	g++ -c -g -Wall sorting.cpp

Base.o:Base.h Base.cpp
	g++ -c -g -Wall Base.cpp

clean:
	rm *.o
	rm Number
