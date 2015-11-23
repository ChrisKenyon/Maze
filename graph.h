#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <stack>
#include <queue>

using namespace boost;
using namespace std;

#define LargeValue 99999999
struct VertexProperties;
struct EdgeProperties;
typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred; // predecessor node
	int weight;
	bool visited;
	bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

stack<Graph::vertex_descriptor> FindPathDFSRecursive(Graph &g, pair<int, int> goalPosition);
stack<Graph::vertex_descriptor> FindPathDFSStack(Graph &g, pair<int, int> goalPosition);
stack<Graph::vertex_descriptor> FindShortestPathDFS(Graph &g, pair<int, int> goalPosition);
stack<Graph::vertex_descriptor> FindShortestPathBFS(Graph & g, pair<int, int> goalPosition);
void clearVisited(Graph &g);
void setNodeWeights(Graph &g, int w);
void clearMarked(Graph &g);

bool relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);
void Dijkstra(Graph &g, Graph::vertex_descriptor start);
bool BellmanFord(Graph &g, Graph::vertex_descriptor start);
void printPaths(Graph &g, pair<Graph::vertex_iterator, Graph::vertex_iterator> vertItrRange, Graph::vertex_descriptor sourceNode);

stack<Graph::vertex_descriptor> getShortestPathFromBForD(Graph &g, Graph::vertex_descriptor target);

ostream& operator << (ostream &ostr, const Graph &g);