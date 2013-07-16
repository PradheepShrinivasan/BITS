// standard header file
#include <iostream>
#include "sorting.h"

#define CUTOFF 5
using namespace std;

static void swapPivotElement (Number list[], Number pivot, int start, int end);

Number quickSelect (Number list[], int size, int k)
{
	int start = 0;
	int end = size -1;
	
	while (start+CUTOFF <= end)
	{
		int i = partition (list, start, end); 
		if (k <= i)
			end = i-1;
		else  
			start = i+1;
	}
	insertionSort (list+start, end-start+1);
	return list[k-1];
}


int partition (Number list[], const int start, const int end)
{
		Number Pivot = Median5 <Number> (list [start], list [(start+end)/4], list [(start+end)/4*3], list [(start+end)/2], list [end]);
		swapPivotElement (list, Pivot, start, end);

		int i = start; 
		int j = end-1;

		for (;;)
		{
			while (list[i] < Pivot && i < end) {i++;}
			while (list[j] > Pivot && j > 0) {j--;}
			if (i < j)
				swap (list[i], list[j]);
			else 
				break;
		}
		swap (list[i], list[end]);
			
		return i;
}


// place the pivot element at the end of the list
void static swapPivotElement (Number list[], Number pivot, int start, int end)
{
	if (pivot == list [start])
		swap (list[start], list[end]);
	else if (pivot == list [(start+end)/4])
		swap (list [(start+end)/4], list [end]);
	else if (pivot == list [(start+end)/4*3])
		swap (list [(start+end)/4*3], list [end]);
	else if (pivot == list [(start+end)/2])
		swap (list [(start+end)/2], list [end]);
	else 
		return;// if its at already at the end no need to swap
}

// insertion sort algorithmn
void insertionSort (Number list[], int N)
{
	int j, P;
	Number temp;

	for (P = 1; P < N; P++)
	{
		temp = list[P];
		for (j = P; j > 0 && list [j-1]> temp; j--)
			list[j] = list[j-1];
		list[j] = temp;
	}
}
