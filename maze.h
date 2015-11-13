#include "stdafx.h"
#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include "d_except.h"
#include "d_matrix.h"
#include "graph.h"

#include<stdlib.h>

using namespace std;

class maze
{
public:
   maze(ifstream &fin);
   void print(int,int,int,int);
   bool isLegal(int i, int j);
   void mapMazeToGraph(Graph &g);
   void printPath(Graph::vertex_descriptor end,
                        stack<Graph::vertex_descriptor> &s,
                        Graph &g);
   int numRows(){return rows;};
   int numCols(){return cols;};

private:
   int rows; // number of rows in the maze
   int cols; // number of columns in the maze12 a
   
   matrix<bool> value;
};

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;
   
   char x;
   
   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
         fin >> x;
         if (x == 'O')
            value[i][j] = true;
         else
            value[i][j] = false;
      }
   
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
	system("CLS");
	cout << endl;

	if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
		throw rangeError("Bad value in maze::print");

	if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
		throw rangeError("Bad value in maze::print");

	for (int i = 0; i <= rows - 1; i++)
	{
		for (int j = 0; j <= cols - 1; j++)
		{
			if (i == goalI && j == goalJ)
				cout << "*";
			else
				if (i == currI && j == currJ)
					cout << "+";
				else
					if (value[i][j])
						cout << " ";
					else
						cout << "X";
		}
		cout << endl;
	}
	cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
	if (i < 0 || i > rows || j < 0 || j > cols)
		throw rangeError("Bad value in maze::isLegal");

	return value[i][j];
}

void maze::mapMazeToGraph(Graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int current = i*cols + j;
			g[vertex(current, g)].cell = pair<int,int>(i, j);
			g[vertex(current, g)].visited = false;
			g[vertex(current, g)].marked = false;
			g[vertex(current, g)].pred = 0;
			g[vertex(current, g)].weight = 1;

			if (!isLegal(i , j))
				continue;

			// Up is Redundant?
			if (i > 0 && isLegal(i - 1, j))
			{
				add_edge(current, current - cols, g);
			}

			// Down
			if (i < rows - 1 && isLegal(i + 1, j))
			{
				add_edge(current, current + cols, g);
			}

			// Left is Redundant?
			if (j > 0 && isLegal(i, j - 1))
			{
				add_edge(current, current - 1, g);
			}

			// Right
			if (j < cols - 1 && isLegal(i, j + 1))
			{
				add_edge(current, current + 1, g);
			}
		}
	}

	// Iterate through the edges and initialize them
	typedef graph_traits<Graph>::edge_iterator edge_iter;
	edge_iter edgeIt, edgeIt_end;
	for (tie(edgeIt, edgeIt_end) = edges(g); edgeIt != edgeIt_end; ++edgeIt)
	{
		g[*edgeIt].marked = false;
		g[*edgeIt].visited= false;
		g[*edgeIt].weight = 1;
	}
}

void maze::printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph &g) {
	stack<Graph::vertex_descriptor> reverseStack;
	while (!s.empty())
	{
		pair<int, int> cell(g[s.top()].cell.first, g[s.top()].cell.second);
		print(rows - 1, cols - 1, cell.first, cell.second);
		s.pop();
	}
}

