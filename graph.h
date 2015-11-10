#pragma once
#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

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

ostream& operator << (ostream &ostr, const VertexProperties &vp) {
	ostr << "Cell [" << vp.cell.first << "," << vp.cell.second << "]:" << endl;
	ostr << "Marked: " << vp.marked
		<< "  Pred: " << vp.pred
		<< "  Visited: " << vp.visited
		<< "  Weight: " << vp.weight << endl;
	return ostr;
}

ostream& operator << (ostream &ostr, const EdgeProperties&ep) {
	ostr << "(Edge)  Marked: " << ep.marked
		<< "  Visited: " << ep.visited
		<< "  Weight: " << ep.weight;
	return ostr;
}

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

//typedef property<edge_weight_t, int> EdgeProperty;

#define LargeValue 99999999

ostream& operator << (ostream &ostr, const Graph &g) {
	// Iterate through the vertex properties and print them out
	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	std::pair<vertex_iter, vertex_iter> vertIter;
	for (vertIter = vertices(g); vertIter.first != vertIter.second; ++vertIter.first)
		ostr << g[*vertIter.first] << std::endl;
	ostr << std::endl;
	
	// Iterate through the edges and print them out
	typedef graph_traits<Graph>::edge_iterator edge_iter;
	edge_iter edgeIt, edgeIt_end;
	for (tie(edgeIt, edgeIt_end) = edges(g); edgeIt != edgeIt_end; ++edgeIt)
		ostr << g[*edgeIt] << endl;

	return ostr;
}