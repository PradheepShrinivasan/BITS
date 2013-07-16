#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdbool.h>

struct edgeDeclaration; 

// a vetex contians its node infrmattion and collection of edges
typedef struct vertex
{
	int nodeId;	// the niodeId
	int colour;	// the colir 
	int numofEdges;	// the number of edges 
	struct edgeDeclaration *edge;	
}Vertex;

// an edge is nothing but a link to a vertex
typedef struct edgeDeclaration 
{
	Vertex *vertex;
	struct edgeDeclaration *nextEdge;
}Edge;


// a graph is a collection of a vertex and edges
typedef struct graph
{
	Vertex **vertexNodes;	// Graph is a collection of vertex
	int numofVertex;	// the number of nodes added
	int numofColoursUsed; 	// contians the number of colours used 
}Graph;

//function protypes
extern Graph* createGraph (int NumVertex);
extern Vertex* createVertex (Graph *g, int vertex);
extern Edge* createEdge (Vertex *v);
extern Graph* addEdge (Graph* g, int v1, int v2);
extern bool findVertexInGraph (Graph *g, int vertex, Vertex **v1);
extern Graph* sortGraphbyDegree (Graph *g);
extern Edge* getNeighbors (Graph* g, Vertex *v);
extern int chooseColour (Graph *g, Vertex *v);
extern int assignColour (Graph *g);
extern void printGraph (Graph *g, int numofColors, FILE *fp);

#endif

