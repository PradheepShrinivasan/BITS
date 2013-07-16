#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


#include "graph.h"


// create a new graph 
Graph* createGraph (int numVertex)
{
	 Graph *currentGraph = (Graph *)calloc(1, sizeof (Graph));
	 currentGraph->vertexNodes = calloc (numVertex, sizeof (Vertex*));
	 return currentGraph;
};


// creates a new vertex and returns a new  pointer to it
Vertex* createVertex (Graph *g, int vertex)
{
	Vertex *newVertex = (Vertex *)calloc (1,sizeof (Vertex));
	newVertex->nodeId = vertex;
	g->vertexNodes[g->numofVertex] = newVertex;
	g->numofVertex++;
	return newVertex;
}

// create a new Edge
Edge* createEdge (Vertex *v)
{
	Edge *curEdge = (Edge  *) calloc (1 , sizeof (Edge));
	curEdge->vertex = v;
	return curEdge;
}

// add an edge
Graph* addEdge (Graph* g, int v1, int v2)
{
	if (g == NULL)
		return NULL;

	Vertex *vertex1;
	Vertex *vertex2;

	// check if the vertex iv1 is present 
	// and create one if not present
	if (!findVertexInGraph (g, v1, &vertex1))
	{
		// create a new vertex 
		vertex1 = createVertex (g, v1);
	}

	// check if the vertex v2 is present
	// and create one is not present
	if (!findVertexInGraph (g, v2, &vertex2))
	{
		// create a new vertex 
		vertex2 = createVertex (g, v2);
	}
	
	//create a new Edge 
	// there is no checking to see if the edge is already present
	Edge *newEdge = createEdge (vertex2);
	newEdge->nextEdge = vertex1->edge;
	vertex1->edge  = newEdge;
	vertex1->numofEdges++;

	// add it as a edge on v2 too 
	newEdge = createEdge (vertex1);
	newEdge->nextEdge = vertex2->edge;
	vertex2->edge  = newEdge;
	vertex2->numofEdges++;

	return g;
}

// find if the vertex in graph and return true if the vertex is 
// found and flase if not found 
bool findVertexInGraph (Graph *g, int vertex, Vertex **v1)
{
	int i = 0;

	// if the graph has no inputs 
	if (g == NULL  || v1 == NULL )
		return false ;

	//search for the vertex v1  in the  graph
	for (i = 0; i < g->numofVertex; i++)
	{
		if (g->vertexNodes[i]->nodeId == vertex)
		{
			*v1 = g->vertexNodes [i];
			return true;
		}
	}
	return false;
}


Graph* sortGraphbyDegree (Graph *g)
{
	int i = 0 ,ihole = 0;

	if (g == NULL)
		return NULL;

	//do an insertion sort as it gurantees a inplace sort
	for ( i = 1; i < g->numofVertex; i++)
	{
		Vertex *item = g->vertexNodes[i];
		ihole = i;

		while ( ihole > 0 &&  g->vertexNodes[ihole-1]->numofEdges > item->numofEdges)
		{
			g->vertexNodes[ihole] = g->vertexNodes[ihole-1];
			ihole --;
		}	
		g->vertexNodes[ihole] = item;
	}
	return g;
}


Edge* getNeighbors (Graph* g, Vertex *v)
{
	return v->edge;
}


// choose a  colour to a particular vertex
int chooseColour (Graph *g, Vertex *v)
{
	int colour = 0;
	
	for (colour = 1; colour <= g->numofVertex; colour++)
	{
		Edge *curEdge = getNeighbors (g, v);
		while (curEdge != NULL )
		{
			// is the colour one of the neighbor colours ?
			if (curEdge->vertex->colour == colour)
				break;
			curEdge = curEdge->nextEdge;
		}
		// none of the neighbors have teh same colur
		if (curEdge == NULL)
			break;
	}

	v->colour = colour;
	if (colour > g->numofColoursUsed)
		g->numofColoursUsed++;
	return colour;
}

// assign the colour  tp eachj of the vertex
int assignColour (Graph *g) 
{
	int i = 0; 
	for (i = 0; i < g->numofVertex; i++)
		chooseColour (g, g->vertexNodes[i]);
	return 0;
}

void printGraph (Graph *g, int numofColors, FILE *fp)
{
	int count = 0;
	fprintf (fp, "%d\n", numofColors);
	for (count = 0; count < g->numofVertex; count++)
	{
		Vertex *curVertex = g->vertexNodes[count];
		Edge *edge = curVertex->edge;
		fprintf(fp, "(%c,%d):",curVertex->nodeId, curVertex->colour);
		if (edge != NULL)
		{
			fprintf (fp, "%c", edge->vertex->nodeId);
			edge = edge->nextEdge;
		}
		while (edge != NULL)
		{
			fprintf (fp, ",%c", edge->vertex->nodeId);
			edge = edge->nextEdge;

		}
		fprintf (fp, "\n");
	}
	fprintf (fp, "\n");

}
