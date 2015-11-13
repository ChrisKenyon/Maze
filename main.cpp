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

	  pair<int, int> goal(m.numRows() - 1, m.numCols() - 1);
	  stack<Graph::vertex_descriptor> s;
	  s = FindPathDFSRecursive(g, goal);
	  m.printPath(num_vertices(g), s, g);
	  s = FindPathDFSStack(g, goal);
	  m.printPath(num_vertices(g), s, g);
	  s = FindShortestPathDFS(g, goal);
	  m.printPath(num_vertices(g), s, g);
	  s = FindShortestPathBFS(g, goal);
	  m.printPath(num_vertices(g), s, g);
	  
      //cout << g << endl;
   }
   catch (std::exception ex)
   {
	   cout << ex.what();
   }
}
