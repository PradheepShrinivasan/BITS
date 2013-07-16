#ifndef __BASE_H__
#define __BASE_H__

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
class Base 
{
	private:
		static vector<char> LookUpTable;	
	public:
		
		static const int SUCCESS = 0;
		static const int ERROR_NOTVALIDFILE = 1;
		static const int ERROR_CHARACTERNOTFOUND = -1;

		static	int initializeBase (FILE *basefile);
		static	int lookup (char characterToFind);
		static  char lookupChar(int position);
		~Base () {}

	private:
		Base  ();	
		Base (const Base& ref);
		Base& operator= (const Base& to); 
};

#endif
