#include "stdafx.h"
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include "maze.h"
#include "d_except.h"
#include "graph.h"

using namespace boost;
using namespace std;

int main();

void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin);

int main()
{
	try
	{
		ifstream fin;

		// Read the maze from the file.
		// (5B) string fileName = "maze0.txt";
		
		// ------ Project 5C: Dijkstra & Bellman-Ford ------ 
		string fileName = "graph3.txt";

		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}

		Graph g;
		typedef graph_traits<Graph>::vertex_iterator vertex_iter;
		std::pair<vertex_iter, vertex_iter> vertItrRange = vertices(g);
		Graph::vertex_descriptor first = vertex(*vertItrRange.first, g);
		Graph::vertex_descriptor second = vertex(*vertItrRange.second, g);

		initializeGraph(g, first, second, fin);
		clearMarked(g);
		clearVisited(g);
		fin.close();

		// Dijkstra Algorithm

		size_t sourceNode = 0;
		Dijkstra(g, vertex(sourceNode, g));
		vertItrRange = vertices(g);

		printPaths(g, vertItrRange, sourceNode);

		cout << g;

		// Bellman-Ford Algorithm

		BellmanFord(g, sourceNode);
		vertItrRange = vertices(g);

		printPaths(g, vertItrRange, sourceNode);

		cout << g;

		/* ------ Project 5b: DFS/BFS ------ 
				maze m(fin);
				fin.close();
				Graph g(m.numRows()*m.numCols());

				m.print(m.numRows() - 1, m.numCols() - 1, 0, 0);
				m.mapMazeToGraph(g);
				pair<int, int> goal(m.numRows() - 1, m.numCols() - 1);
				stack<Graph::vertex_descriptor> s;

				// some of these don't include the starting point in the print stack, so they
				// may not match up by a difference of 1 in size.
				s = FindPathDFSRecursive(g, goal);
				//m.printPath(num_vertices(g), s, g);
				s = FindPathDFSStack(g, goal);
				//m.printPath(num_vertices(g), s, g);
				s = FindShortestPathDFS(g, goal);
				//m.printPath(num_vertices(g), s, g);
				s = FindShortestPathBFS(g, goal);
				//m.printPath(num_vertices(g), s, g);

				//cout << g << endl;
		*/
	}
	catch (std::exception ex)
	{
		cout << ex.what();
	}
}

void initializeGraph(Graph &g,
	Graph::vertex_descriptor &start,
	Graph::vertex_descriptor &end, ifstream &fin)
	// Initialize g using data from fin.  Set start and end equal
	// to the start and end nodes.
{
	EdgeProperties e;

	int n, i, j;
	int startId, endId;
	fin >> n;
	fin >> startId >> endId;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
	{
		v = add_vertex(g);
		if (i == startId)
			start = v;
		if (i == endId)
			end = v;
	}

	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i, j, e, g);
	}
}
