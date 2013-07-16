Compiling the code
===================

To compile the code just type "make" in the folder.

To do a clean rebuild do 1. make clean 2 make in the code folder.

Running the code
=================
This involves starting the server and then starting the client. 

To start the server run ./dict_server

To start the client run ./dict_client "server_hostname"


example 
 ./dict_server &
./dict_client localhost 

The localhost can be used if the client and the server is running on the same machine.


Output of the code
==================
The client code on starting up the program would display an interactive menu. 

Follow the onscreen guidelines, and press the necessary commands to perform the necessary options.


Additional comments
--------------------
	A concurrent server services several requests at the same time. Hence there should be mutual exclusion to prevent 
	more than one thread modidying the data at the same time. In the code attached read write locks are used. This helps
	increase the number of readers at the same time, therby increasing the performance compared to mutexs


Contact Details
===============
BITS WILP ID	2012HZ12797	
name 		Pradheep
Contact details pradheep.sh@gmail.com

