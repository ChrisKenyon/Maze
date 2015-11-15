#include "stdafx.h"
#include "graph.h"

using namespace std;
using namespace boost;

template <typename T>
void reverseStack(stack<T> &s)
{
	stack<T> s2;
	while (!s.empty())
	{
		s2.push(s.top());
		s.pop();
	}
	s = s2;
}

void clearVisited(Graph &g)
// Mark all nodes in g as not visited.
{
	int num = num_vertices(g);
	for (int i = 0; i < num; i++)
	{
		g[vertex(i, g)].visited = false;
		g[vertex(i, g)].pred = 0;
	}
}

void setNodeWeights(Graph &g, int w)
// Set all node weights to w.
{
	int num = num_vertices(g);
	for (int i = 0; i < num; i++)
	{
		g[vertex(i, g)].weight = w;
	}
}

void clearMarked(Graph &g)
{
	int num = num_vertices(g);
	for (int i = 0; i < num; i++)
	{
		g[vertex(i, g)].marked = false;
	}
}

bool findPathDFSRecursive(Graph &g, pair<int, int> goalPosition, Graph::vertex_descriptor currentVertex, stack<Graph::vertex_descriptor> &path)
{
	g[currentVertex].visited = true;
	VertexProperties vertProp = g[currentVertex];
	if (vertProp.cell == goalPosition)
	{
		path.push(currentVertex);
		return true;
	}

	Graph::adjacency_iterator neighborIt, neighborEnd;
	tie(neighborIt, neighborEnd) = adjacent_vertices(currentVertex, g);
	for (; neighborIt != neighborEnd; neighborIt++)
	{
		Graph::vertex_descriptor next = vertex(*neighborIt, g);
		if (!g[next].visited &&
			findPathDFSRecursive(g, goalPosition, next, path))
		{
			path.push(currentVertex);
			return true;
		}
	}
	return false;
}

stack<Graph::vertex_descriptor> FindPathDFSRecursive(Graph &g, pair<int, int> goalPosition)
{
	stack<Graph::vertex_descriptor> path;
	Graph::vertex_descriptor firstVertDesc = vertex(0, g);
	if (!findPathDFSRecursive(g, goalPosition, firstVertDesc, path))
	{
		std::cout << "No Path Found" << endl;
	}
	clearVisited(g);
	return path;
}

stack<Graph::vertex_descriptor> FindPathDFSStack(Graph &g, pair<int, int> goalPosition)
{
	stack <Graph::vertex_descriptor> pathStack;
	Graph::adjacency_iterator neighborIt, neighborEnd;

	Graph::vertex_descriptor currentVertex = vertex(0, g);
	g[currentVertex].pred = NULL;
	pathStack.push(currentVertex);

	while (!pathStack.empty())
	{
		currentVertex = pathStack.top();
		g[currentVertex].visited = true;
		pathStack.pop();
		if (g[currentVertex].cell == goalPosition)
			break;

		tie(neighborIt, neighborEnd) = adjacent_vertices(currentVertex, g);
		Graph::vertex_descriptor next = currentVertex;
		for (; neighborIt != neighborEnd; ++neighborIt)
		{
			Graph::vertex_descriptor next = vertex(*neighborIt, g);
			if (!g[next].visited)
			{
				g[next].pred = currentVertex;
				pathStack.push(next);
			}
		}
	}

	if (g[currentVertex].cell != goalPosition)
	{
		std::cout << "No Path Found!" << endl;
		throw new invalid_argument("No path in the graph");
	}

	stack<Graph::vertex_descriptor> printStack;
	while (currentVertex != NULL)
	{
		printStack.push(currentVertex);
		currentVertex = g[currentVertex].pred;
	}
	clearVisited(g);
	return printStack;
}

stack<Graph::vertex_descriptor> shortestPath;
int minLength = -1;
void findShortestPathDFSRecursive(Graph &g, pair<int, int> goalPosition, Graph::vertex_descriptor currentVertex, stack<Graph::vertex_descriptor> &path)
{
	g[currentVertex].visited = true;
	path.push(currentVertex);
	VertexProperties vertProp = g[currentVertex];

	if (vertProp.cell == goalPosition)
	{
		if (minLength < 0 || path.size() < minLength)
		{
			minLength = path.size();
			shortestPath = path;
		}
	}

	Graph::adjacency_iterator neighborIt, neighborEnd;
	tie(neighborIt, neighborEnd) = adjacent_vertices(currentVertex, g);
	for (; neighborIt != neighborEnd; ++neighborIt)
	{
		Graph::vertex_descriptor next = vertex(*neighborIt, g);
		if (!g[next].visited && next != g[currentVertex].pred)
		{
			findShortestPathDFSRecursive(g, goalPosition, next, path);
		}
	}

	path.pop();
	g[currentVertex].visited = false;
}

stack<Graph::vertex_descriptor> FindShortestPathDFS(Graph & g, pair<int, int> goalPosition)
{
	stack<Graph::vertex_descriptor> path;
	Graph::vertex_descriptor firstVertDesc = vertex(0, g);
	findShortestPathDFSRecursive(g, goalPosition, firstVertDesc, path);
	if (shortestPath.size() == 0)
	{
		std::cout << "No Path Found" << endl;
	}
	reverseStack(shortestPath);
	clearVisited(g);
	return shortestPath;
}

stack<Graph::vertex_descriptor> FindShortestPathBFS(Graph & g, pair<int, int> goalPosition)
{
	queue<Graph::vertex_descriptor> pathQueue;
	Graph::adjacency_iterator neighborIt, neighborEnd;

	Graph::vertex_descriptor currentVertex = vertex(0, g);
	g[currentVertex].pred = NULL;
	pathQueue.push(currentVertex);

	while (!pathQueue.empty())
	{
		currentVertex = pathQueue.front();
		g[currentVertex].visited = true;
		if (g[currentVertex].cell == goalPosition)
		{
			break;
		}

		tie(neighborIt, neighborEnd) = adjacent_vertices(currentVertex, g);
		for (; neighborIt != neighborEnd; ++neighborIt)
		{
			Graph::vertex_descriptor next = vertex(*neighborIt, g);
			if (!g[next].visited)
			{
				g[next].pred = currentVertex;
				pathQueue.push(next);
			}
		}
		pathQueue.pop();
	}

	if (g[currentVertex].cell != goalPosition)
	{
		std::cout << "No Path Found!" << endl;
		throw new invalid_argument("No path in the graph");
	}

	stack<Graph::vertex_descriptor> printStack;
	while (currentVertex != NULL)
	{
		printStack.push(currentVertex);
		currentVertex = g[currentVertex].pred;
	}
	clearVisited(g);
	return printStack;
}

ostream& operator << (ostream &ostr, const VertexProperties &vp) {
	ostr << "Cell [" << vp.cell.first << "," << vp.cell.second << "]:" << endl;
	ostr << "Marked: " << vp.marked
		<< "  Pred: " << vp.pred
		<< "  Visited: " << vp.visited
		<< "  Weight: " << vp.weight << endl;
	return ostr;
}

ostream& operator << (ostream &ostr, const EdgeProperties&ep) {
	ostr <<"  Marked: " << ep.marked
		<< "  Visited: " << ep.visited
		<< "  Weight: " << ep.weight;
	return ostr;
}
typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

ostream& operator << (ostream &ostr, const Graph &g) {
	// Iterate through the vertex properties and print them out
	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	std::pair<vertex_iter, vertex_iter> vertIter;
	for (vertIter = vertices(g); vertIter.first != vertIter.second; ++vertIter.first)
		ostr << g[*vertIter.first] << std::endl;
	ostr << std::endl;

	// Iterate through the edges and print them out
	typedef graph_traits<Graph>::edge_iterator edge_iter;
	std::pair<edge_iter, edge_iter> edgeIter;
	for (edgeIter = edges(g); edgeIter.first != edgeIter.second; ++edgeIter.first)
	{
		ostr << g[*edgeIter.first] << endl;
	}
	return ostr;
}