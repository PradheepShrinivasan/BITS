#ifndef __QSORTING_H__
#define __QSORTING_H__

#include <iostream>

#include "Number.h"

using namespace std;

int partition (Number numberGroup[], const int start, const int end);
Number quickSelect (Number numberGroup[], int size, int k);
void insertionSort (Number list[], int N);

template<class V>
inline V median(const V &a, const V &b, const V &c)
{
	return max(min(a,b),min(c,max(a,b))); 
} 

template<class V>
inline V Median5(const V &a, const V &b, const V &c, const V &d, const V &e)
{
	V f=max(min(a,b),min(c,d)); // discards lowest from first 4
        V g=min(max(a,b),max(c,d)); // discards biggest from first 4
	return median(e,f,g);
}


#endif
