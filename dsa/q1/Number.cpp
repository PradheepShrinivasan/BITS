// Generic header file
/**********
READEME
 This file implementes the methods for the Number ADT

 In C++
 for making it more closer to standard data types the Number argument in the functions has been 
 ommited as its autimatically passd as a this pointer.

*****************/
#include <iostream>

#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>

#include <stdlib.h>

// Project specifle header file
#include "Number.h"
#include "Base.h"



using namespace std;
Number::Number ():  base (0)
{
}

Number:: Number(const Number& src):base (src.getBase())
{
	for (Number::const_Iterator it = src.c_begin (); it != src.c_end(); ++it )
	{
		data.push_back (*it);
	}
}

Number::Number (int baseval, string& src)
{
	base = baseval;
	for (size_t i = 0; i < src.size (); i++ )
	{
		data.push_back (Position_value (src.size()-i-1, src[i]));
	}
}

Number::Number (const char* format)
{
	insertNumber (format);
}

Number& Number::operator= (const Number& left)
{
	base = left.base;
	data.clear ();
	for (Number::const_Iterator it = left.c_begin (); it != left.c_end(); ++it )
	{
		data.push_back (*it);
	}

	return *this;
}

const Number& Number::insertNumber (const char* format)
{
	size_t spacePos = 0;
	size_t valuePos = 0;
	string source (format);


	spacePos = source.find (" ");
	base = atoi (source.substr(0, spacePos).c_str());
	// this one would point to the place where get the actual
	// second part of the string
	valuePos = spacePos+1;

	while (valuePos < source.length ())
	{
		data.push_back (Position_value (source.length()-valuePos-1, source[valuePos]));
		valuePos++;
	}
	return *this;
}

string Number::getNumber ()
{
	string returnString;

	for (list<Position_value>::iterator it = data.begin (); it != data.end (); ++it)
	{
		returnString.push_back (it->getValue ());
	}

	return returnString;
}

string Number::getNumberWithBase ()
{
	stringstream str;
	str << "(" << getNumber() << ")"<< base;
	return str.str();
}

void Number::printNumber ()
{	
	cout << getNumberWithBase () << endl;
}

// concerts the number frrom one base to the other
Number Number::convert (int to_base) 
{
	if (base == to_base)
		return *this;

	// calculate the number in decimal format and then convert it to base 10
	long value = 0;
	for (Iterator it = data.begin (); it != data.end(); it++)
	{
		value = value*base + Base::lookup (it->getValue ());	
	}


	//clear the data stored
	base = to_base;

	string newvalue;
	// now convert the number into the required base by 
	// L division method 
	while (value)
	{
		int temp = value%to_base; // reminded
		value = value / to_base; // quotient
		newvalue.push_back (Base::lookupChar(temp));
	}
	// reverse rhe sequecen ro fw the actual number in string format 
	reverse (newvalue.begin(), newvalue.end());
	
	data.clear();
	for (size_t i = 0; i < newvalue.size (); i++ )
	{
		data.push_back (Position_value (newvalue.size()-i-1, newvalue[i]));
	}

	return *this;
}

unsigned short int Number::compare (const Number &Number2)
{
	return static_cast<const Number>(*this).compare(Number2);
}
// the function compares Number with N2 and returns one of the followind 
//	Greater if N1 > N2
//	Lesser if N1 < N2
//      Equal if N1 == N2
unsigned short int Number::compare (const Number &Number2) const 
{
	if (base == Number2.getBase ())
		return compareWithSameBase (Number2);
		
	Number temp (Number2);
	temp.convert (base); //  convert to the same base
	return temp.compareWithSameBase (Number2);
}

unsigned short int Number::compareWithSameBase (const Number &Number2) const 
{
	//  the number with the most number of digits is always largest
	if (data.size () > Number2.getNumDigits ())
		return Number::Greater;
	else if (data.size () < Number2.getNumDigits ())
		return Number::Lesser;
	else
	{
		// since both of them have the equal number of digits
		// we have to now compare digit by digit
			
		const_Iterator Num1 = data.begin ();
		const_Iterator Num2 = Number2.c_begin ();
		for (; Num1 != data.end(); ++Num1 ,++Num2)
		{
			// check the position values 
			if ( Num1->getPosition () >  Num2->getPosition ())
				return Number::Greater;
			else if (Num1->getPosition () < Num2->getPosition ())
				 return Number::Lesser;
			else
			{
				// now check the character values
				if (Base::lookup(Num1->getValue ()) == (Base::lookup(Num2->getValue ())))
					continue;
				else if (Base::lookup(Num1->getValue ()) < (Base::lookup(Num2->getValue ())))
					 return Number::Lesser;
				else
					return Number::Greater;
			}

		}
	}
	return Number::Equal; 
}
		

bool Number::operator> (const Number &num) 
{

	unsigned short int val = compare (num);
	if (val == Number::Greater)
		return true;
	return false;
}

bool Number::operator< (const Number &num)
{
	unsigned short int val = compare (num);
	if (val == Number::Lesser)
		return true;
	return false;
}

bool Number::operator== (const Number &num)
{
	unsigned short int val = compare (num);
	if (val == Number::Equal)
		return true;
	return false;
}

bool Number::operator> (const Number &num) const
{
	unsigned short int val = compare (num);
	if (val == Number::Greater)
		return true;
	return false;
	
}

bool Number::operator< (const Number &num) const
{
	unsigned short int val = compare (num);
	if (val == Number::Lesser)
		return true;
	return false;
}

bool Number::operator== (const Number &num) const
{
	unsigned short int val = compare (num);
	if (val == Number::Equal)
		return true;
	return false;
}

Number::Iterator Number::begin () 
{
	return data.begin ();
}

Number::const_Iterator Number::c_begin () const 
{
	return data.begin ();
}


Number::Iterator Number::end () 
{
	return data.end ();
}

Number::const_Iterator Number::c_end () const 
{
	return data.end ();
}
