Compiling the code
===================

To compile the code just type "make" in the folder

Running the code
=================

To run the code type ./Number base.txt numbers.txt 10 output

ie ./Number characterListFile InputNumberFile PositionToFind OutputFile


Output of the code
==================
The program writes the output in the file give as the last argument

In the above case output is the name of the file 

File List
=========

Source/Data Files
-----------------

main.c             	The business logic file/driver file
Base.cpp		contains all the Base class ADT
Base.h			The header file of base
Number.cpp		Contins the Number ADT implementation
Number.h		The header file of Number.cpp
sorting.cpp		Contains the sorting routine
sorting.h		the header file of sorting


Output/Generated files
----------------------
Number		 	The final executable
*.o			object files of compilation

Example Files attached
----------------------
base.txt 		The character map file.In example contains Hex notation
numbers.tx		The input numbers file.In example contains numbers from 1 to 10 in decimal format

Additional comments
--------------------

1.The Number member functions does not pass Number1 as argument as this is passed implicty as this pointer by the compiler. Sorry for the change but functionality remains the same
2.Have added additional qualifiers like const at places in function prototypes provided to make it more robust.
3.A good number of constructors. destructors, operators have been added to make the ADT closer to the native data types like int

Contact Details
===============
BITS WILP ID	2012HZ12797	
name 		Pradheep
Contact details pradheep.sh@gmail.com

