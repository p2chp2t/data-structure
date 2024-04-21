#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////
struct AdjMatrix {
  bool **adjmatrix;
  int **weights;
  string *vertices;
};

struct Edge {
	int weight;
	string start;
	string end;
};
/*I modified task7 and task 8 in pa4.cpp so that it doesn't include int value for return type. Also I modified graph constructor. Please be aware. Thank you.*/
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
  Graph(); // I modified the constructor. It is implemented in graph.cpp.
  ~Graph(){};

  string DFS();
  string BFS();

  int addDirectedEdge(string nodeA, string nodeB);
  int addDirectedEdge(string nodeA, string nodeB, int weight);
  int addUndirectedEdge(string nodeA, string nodeB);
  int addUndirectedEdge(string nodeA, string nodeB, int weight);

  string StronglyConnectedComponent();

  string getShortestPath_task5(string source, string destination);
  string getShortestPath_task6(string source, string destination);
  int primMST(ofstream &, string startNode); 
  int kruskalMST(ofstream &, string endNode); 
private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
 AdjMatrix GraphAdjMatrix;
	int vertices_cnt;

	int search(string node);
	void sortVertices();
	void dfs(int v, bool* visited, string& connected);

	Graph getReverse();
	void fillorder(int s, bool* visited, int*& numbering); //numbering the vertices in order of completion of the recursive calls
	void findHighest(int* numbering, int*& order);
	void sortString(string& strongConnected, string& output);

	int minDistance(int* dist, bool* sptSet);

	int findMin(int* dist, bool* mstSet);

	int findSet(string name, int* parent);
	void unionSet(int u, int v, int*& parent);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
