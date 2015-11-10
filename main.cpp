#include "stdafx.h"
#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include "maze.h"
#include "d_except.h"
#include "graph.h"

using namespace boost;
using namespace std;

void clearVisited(Graph &g)
// Mark all nodes in g as not visited.
{
	int num = num_vertices(g);
	for (int i = 0; i < num; i++)
	{
		g[vertex(i, g)].visited = false;
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

int main()
{
   try
   {
      ifstream fin;

      // Read the maze from the file.
      string fileName = "maze0.txt";
      
      fin.open(fileName.c_str());
      if (!fin)
      {
         cerr << "Cannot open " << fileName << endl;
         exit(1);
      }

      maze m(fin);
      fin.close();
      
      m.print(m.numRows()-1,m.numCols()-1,0,0);

      Graph g(m.numRows()*m.numCols());
      m.mapMazeToGraph(g);

	  //test print with test stack for maze0
	  stack<Graph::vertex_descriptor> s;
	  s.push(vertex(0, g));
	  s.push(vertex(1, g));
	  s.push(vertex(2, g));
	  s.push(vertex(3, g));
	  s.push(vertex(4, g));
	  s.push(vertex(24, g));
	  m.printPath(num_vertices(g), s, g);
	  //

      cout << g << endl;
   }
   catch (std::exception ex)
   {
	   cout << ex.what();
   }
}
