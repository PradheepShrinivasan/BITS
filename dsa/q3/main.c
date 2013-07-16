#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"


int main (int argc, char** argv)
{
	Graph *currentGraph = NULL;
	int numVertex = 0;
	char  v1 = 0, v2 =0;


	if (argc != 3 )
	{
		printf ("The number of argument are wrong. Check ReadMe");
		return 0;
	}


	FILE *fp = fopen (argv[1], "r");
	if (fp == NULL)
	{
		perror ("Error in reading the file");
		return 0;
	}

	FILE *fpOutput = fopen (argv[2], "w+");
	if (fpOutput == NULL)
	{
		perror ("Error in opening file");
		return 0;
	}
	
	
	fscanf (fp, "%d\n", &numVertex);
	currentGraph = createGraph (numVertex);
	
	while (fscanf (fp,"%c,%c\n", &v1, &v2) != EOF)
	{
		addEdge (currentGraph, v1, v2);
	}

	sortGraphbyDegree (currentGraph);
	assignColour (currentGraph);
	printGraph (currentGraph, currentGraph->numofColoursUsed, fpOutput);

	return 0;
}
