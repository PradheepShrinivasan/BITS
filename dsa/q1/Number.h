#ifndef __NUMBER_H__
#define __NUMBER_H__


// C++ specific header file
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Position_value 
{
	private:
		int position;
		char value;
	public:
		
		Position_value () : position (-1), value (-1) {}
		Position_value (int pos, char val): position (pos), value (val) {}
		Position_value (const Position_value &from): position (from.getPosition()), value (from.getValue()) {}
		
		~Position_value () {}
		
		int getPosition () {return position;}
		int getPosition () const {return position;}
		char getValue () { return value;}
		char getValue () const { return value;}

		void setPostion (char pos) {position = pos;}
		void setValue (int val)  { value = val; }
};


// Creating a New ADT called the Number that would 
// contain the class and base value
class Number 
{
	private:
		int base;
		list<Position_value> data;
	
	public:
		typedef list<Position_value>::iterator Iterator;
		typedef list<Position_value>::const_iterator const_Iterator;
		
		static const unsigned short int Greater = 1;
		static const unsigned short int Lesser  = 2;
		static const unsigned short int Equal   = 3;

		Number ();
		Number (const Number &num); 
		Number (const char* format);
		Number (int baseval, string& src);
		const Number& insertNumber (const char* format);
		Number& operator= (const Number& num);
		
		unsigned short int compare (const Number &Number2);
		unsigned short int compare (const Number &Number2) const;
	

		string getNumber ();
		string getNumberWithBase ();
		void printNumber ();

		Number convert (int to_base);
				
		int getBase () 		{return base;}
		int getBase () const 	{return base;}
		size_t getNumDigits () {return data.size();}
		size_t getNumDigits () const {return data.size();}

		bool operator > (const Number &num);		
		bool operator== (const Number &num);
		bool operator < (const Number &num);

		bool operator > (const Number &num) const; 
		bool operator < (const Number &num) const;
		bool operator== (const Number &num) const;
		
		Iterator  begin () ;
		Iterator  end   () ;
		const_Iterator c_begin () const ;
		const_Iterator c_end () const;

	private:
		unsigned short int compareWithSameBase (const Number &Number2) const ;
};

#endif

