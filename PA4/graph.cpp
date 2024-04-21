#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */

Graph::Graph() {
	vertices_cnt = 0;
	GraphAdjMatrix.adjmatrix = new bool* [NodeMaxCount];
	GraphAdjMatrix.weights = new int* [NodeMaxCount];
	for (int i = 0;i < NodeMaxCount;i++) {
		GraphAdjMatrix.adjmatrix[i] = new bool[NodeMaxCount];
		GraphAdjMatrix.weights[i] = new int[NodeMaxCount];
		for (int j = 0;j < NodeMaxCount;j++) {
			GraphAdjMatrix.adjmatrix[i][j] = false;
			GraphAdjMatrix.weights[i][j] = INF;
		}
	}
	GraphAdjMatrix.vertices = new string[NodeMaxCount];
	for (int i = 0;i < NodeMaxCount;i++)
		GraphAdjMatrix.vertices[i] = "";
}

int Graph::search(string node) {
	for (int i = 0;i < NodeMaxCount;i++) {
		if (GraphAdjMatrix.vertices[i] == node) {
			return i;
		}
		else continue;
	}
	return -100; // node not found
}

void Graph::sortVertices() {
	for (int i = 0;i < vertices_cnt - 1;i++) {
		for (int j = i + 1;j < vertices_cnt;j++) {
			if (GraphAdjMatrix.vertices[i] > GraphAdjMatrix.vertices[j]) { //swap
				string temp = GraphAdjMatrix.vertices[i];
				GraphAdjMatrix.vertices[i] = GraphAdjMatrix.vertices[j];
				GraphAdjMatrix.vertices[j] = temp;

				bool* tempRow = GraphAdjMatrix.adjmatrix[i];
				GraphAdjMatrix.adjmatrix[i] = GraphAdjMatrix.adjmatrix[j];
				GraphAdjMatrix.adjmatrix[j] = tempRow;

				for (int k = 0;k < vertices_cnt;k++) {
					bool tempEdge = GraphAdjMatrix.adjmatrix[k][i];
					GraphAdjMatrix.adjmatrix[k][i] = GraphAdjMatrix.adjmatrix[k][j];
					GraphAdjMatrix.adjmatrix[k][j] = tempEdge;
				}

				int* tempRowWeights = GraphAdjMatrix.weights[i];
				GraphAdjMatrix.weights[i] = GraphAdjMatrix.weights[j];
				GraphAdjMatrix.weights[j] = tempRowWeights;

				for (int k = 0;k < vertices_cnt;k++) {
					int tempWeight = GraphAdjMatrix.weights[k][i];
					GraphAdjMatrix.weights[k][i] = GraphAdjMatrix.weights[k][j];
					GraphAdjMatrix.weights[k][j] = tempWeight;
				}
			}
		}
	}
}

void Graph::dfs(int v, bool* visited, string& connected) {
	visited[v] = true;
	connected += GraphAdjMatrix.vertices[v] + " ";
	for (int i = 0;i < vertices_cnt;i++) {
		if (GraphAdjMatrix.adjmatrix[v][i] && !visited[i])
			dfs(i, visited, connected);
	}
}

Graph Graph::getReverse() {
	Graph gr;
	gr.vertices_cnt = vertices_cnt;
	gr.GraphAdjMatrix.adjmatrix = new bool* [vertices_cnt];
	gr.GraphAdjMatrix.weights = new int* [vertices_cnt];
	for (int i = 0;i < vertices_cnt;i++) {
		gr.GraphAdjMatrix.adjmatrix[i] = new bool[vertices_cnt];
		gr.GraphAdjMatrix.weights[i] = new int[vertices_cnt];
	}
	gr.GraphAdjMatrix.vertices = new string[vertices_cnt];
	for (int i = 0;i < vertices_cnt;i++) { //initialize gr
		for (int j = 0;j < vertices_cnt;j++) {
			gr.GraphAdjMatrix.adjmatrix[i][j] = false;
			gr.GraphAdjMatrix.weights[i][j] = INF;
		}
		gr.GraphAdjMatrix.vertices[i] = "";
	}
	for (int i = 0;i < vertices_cnt;i++) {
		gr.GraphAdjMatrix.vertices[i] = GraphAdjMatrix.vertices[i]; //vertices are same with GraphAdjMatrix
		for (int j = 0;j < vertices_cnt;j++) {
			if (GraphAdjMatrix.adjmatrix[i][j] == true) { //change direction of edges in opposite
				gr.GraphAdjMatrix.adjmatrix[j][i] = true;
				gr.GraphAdjMatrix.weights[j][i] = GraphAdjMatrix.weights[i][j];
			}
		}
	}
	return gr;
}

void Graph::fillorder(int s, bool* visited, int*& numbering) {
	visited[s] = true;
	for (int i = 0;i < vertices_cnt;i++) {
		if (GraphAdjMatrix.adjmatrix[s][i] && !visited[i]) {
			fillorder(i, visited, numbering);
			numbering[s]++;
		}
	}
}

void Graph::findHighest(int* numbering, int*& order) {
	for (int i = 0; i < vertices_cnt; i++) {
		order[i] = i;
	}
	for (int i = 0; i < vertices_cnt - 1; i++) {
		for (int j = i + 1; j < vertices_cnt; j++) {
			if (numbering[order[i]] < numbering[order[j]]) {
				int tmp = order[i];
				order[i] = order[j];
				order[j] = tmp;
			}
			else if (numbering[order[i]] == numbering[order[j]]) {
				// If the numbering is the same, compare the labels lexicographically
				string label1 = GraphAdjMatrix.vertices[order[i]];
				string label2 = GraphAdjMatrix.vertices[order[j]];
				if (label1 > label2) {
					int tmp = order[i];
					order[i] = order[j];
					order[j] = tmp;
				}
			}
		}
	}
}

void Graph::sortString(string& strongConnected, string& output) {
	int start = 0;
	int cnt = 0;
	string* temp = new string[NodeMaxCount];
	for (int i = 0;i < strongConnected.length();i++) {
		if (strongConnected[i] == ' ') {
			if (cnt < NodeMaxCount) {
				temp[cnt++] = strongConnected.substr(start, i - start);
				start = i + 1;
			}
			else
				break;
		}
	}
	if (cnt < NodeMaxCount)
		temp[cnt++] = strongConnected.substr(start);

	// Sort the components based on their smallest node label
	for (int i = 0; i < cnt - 1; i++) {
		for (int j = i + 1; j < cnt; j++) {
			if (temp[i] > temp[j]) {
				string tmp = temp[i];
				temp[i] = temp[j];
				temp[j] = tmp;
			}
		}
	}
	for (int i = 0; i < cnt; i++) {
		output += temp[i];
		output += " ";
	}
	delete[] temp;
}

int Graph::minDistance(int* dist, bool* sptSet) {
	int min = INF;
	int idx = 0;
	for (int i = 0;i < vertices_cnt;i++) {
		if (!sptSet[i] && dist[i] < min) {
			min = dist[i];
			idx = i;
		}
	}
	return idx;
}

int Graph::findMin(int* dist, bool* mstSet) {
	int min = INF;
	int idx = 0;
	for (int i = 0;i < vertices_cnt;i++) {
		if (!mstSet[i] && dist[i] < min) {
			min = dist[i];
			idx = i;
		}
	}
	return idx;
}

int Graph::findSet(string name, int* parent) {
	int n = search(name);
	if (parent[n] == n)
		return n;
	return findSet(GraphAdjMatrix.vertices[parent[n]], parent);
}

void Graph::unionSet(int u, int v, int*& parent) {
	int a = findSet(GraphAdjMatrix.vertices[u], parent);
	int b = findSet(GraphAdjMatrix.vertices[v], parent);
	if (a < b)
		parent[a] = b;
	else
		parent[b] = a;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

string Graph::DFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string connected = "";
	int connect = 0;
	bool* visited = new bool[vertices_cnt];
	for (int i = 0;i < vertices_cnt;i++) {
		visited[i] = false;
	}
	for (int i = 0;i < vertices_cnt;i++) {
		if (!visited[i]) {
			dfs(i, visited, connected);
			connected.pop_back();
			connected += "\n";
			connect++;
		}
	}
	delete[] visited;
	string answer = "";
	answer = to_string(connect) + "\n" + connected;
  answer.pop_back();
	return answer;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::BFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

	string connected = "";
	int connect = 0;
	bool* visited = new bool[vertices_cnt];
	for (int i = 0;i < vertices_cnt;i++) {
		visited[i] = 0;
	}
	for (int i = 0;i < vertices_cnt;i++) {
		if (!visited[i]) {
			int front = 0;
			int rear = 0;
			int* queue = new int[vertices_cnt];
			queue[rear++] = i;
			visited[i] = true;
			while (front<rear)	
			{
				int v = queue[front++];
				connected += GraphAdjMatrix.vertices[v];
				connected += " ";
				for (int j = 0;j < vertices_cnt;j++) {
					if (GraphAdjMatrix.adjmatrix[v][j] == true && !visited[j]) {
						queue[rear++] = j;
						visited[j] = true;
					}
				}
			}
			delete[] queue;
			connected.pop_back();
			connected += "\n";
			connect++;
		}
	}
	delete[] visited;
	string answer = "";
	answer = to_string(connect) + "\n" + connected;
  answer.pop_back();
	return answer;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

	int idxA = search(nodeA);
	int idxB = search(nodeB);
	if (idxA < 0 && idxB < 0) { //both nodes weren't in the Graph
		if (vertices_cnt + 2 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeA;
		GraphAdjMatrix.vertices[vertices_cnt + 1] = nodeB;
		GraphAdjMatrix.adjmatrix[vertices_cnt][vertices_cnt + 1] = true;
		vertices_cnt += 2;
		sortVertices();
		return 1;
	}
	else if (idxA >= 0 && idxB < 0) {
		if (vertices_cnt + 1 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeB;
		GraphAdjMatrix.adjmatrix[idxA][vertices_cnt] = true;
		vertices_cnt++;
		sortVertices();
		return 1;
	}
	else if (idxA < 0 && idxB >= 0) {
		if (vertices_cnt + 1 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeA;
		GraphAdjMatrix.adjmatrix[vertices_cnt][idxB] = true;
		vertices_cnt++;
		sortVertices();
		return 1;
	}
	else { //both nodes were in the graph
		GraphAdjMatrix.adjmatrix[idxA][idxB] = true;
		sortVertices();
		return 1;
	}
	return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
	int idxA = search(nodeA);
	int idxB = search(nodeB);
	if (idxA < 0 && idxB < 0) { //both nodes weren't in the Graph
		if (vertices_cnt + 2 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeA;
		GraphAdjMatrix.vertices[vertices_cnt + 1] = nodeB;
		GraphAdjMatrix.adjmatrix[vertices_cnt][vertices_cnt + 1] = true;
		GraphAdjMatrix.weights[vertices_cnt][vertices_cnt + 1] = weight;
		vertices_cnt += 2;
		sortVertices();
		return 1;
	}
	else if (idxA >= 0 && idxB < 0) {
		if (vertices_cnt + 1 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeB;
		GraphAdjMatrix.adjmatrix[idxA][vertices_cnt] = true;
		GraphAdjMatrix.weights[idxA][vertices_cnt] = weight;
		vertices_cnt++;
		sortVertices();
		return 1;
	}
	else if (idxA < 0 && idxB >= 0) {
		if (vertices_cnt + 1 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeA;
		GraphAdjMatrix.adjmatrix[vertices_cnt][idxB] = true;
		GraphAdjMatrix.weights[vertices_cnt][idxB] = weight;
		vertices_cnt++;
		sortVertices();
		return 1;
	}
	else { //both nodes were in the graph
		GraphAdjMatrix.adjmatrix[idxA][idxB] = true;
		GraphAdjMatrix.weights[idxA][idxB] = weight;
		sortVertices();
		return 1;
	}
	return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

	int idxA = search(nodeA);
	int idxB = search(nodeB);
	if (idxA < 0 && idxB < 0) { //both nodes weren't in the Graph
		if (vertices_cnt + 2 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeA;
		GraphAdjMatrix.vertices[vertices_cnt + 1] = nodeB;
		GraphAdjMatrix.adjmatrix[vertices_cnt][vertices_cnt + 1] = true;
		GraphAdjMatrix.adjmatrix[vertices_cnt + 1][vertices_cnt] = true;
		vertices_cnt += 2;
		sortVertices();
		return 1;
	}
	else if (idxA >= 0 && idxB < 0) {
		if (vertices_cnt + 1 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeB;
		GraphAdjMatrix.adjmatrix[idxA][vertices_cnt] = true;
		GraphAdjMatrix.adjmatrix[vertices_cnt][idxA] = true;
		vertices_cnt++;
		sortVertices();
		return 1;
	}
	else if (idxA < 0 && idxB >= 0) {
		if (vertices_cnt + 1 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeA;
		GraphAdjMatrix.adjmatrix[vertices_cnt][idxB] = true;
		GraphAdjMatrix.adjmatrix[idxB][vertices_cnt] = true;
		vertices_cnt++;
		sortVertices();
		return 1;
	}
	else { //both nodes were in the graph
		GraphAdjMatrix.adjmatrix[idxA][idxB] = true;
		GraphAdjMatrix.adjmatrix[idxB][idxA] = true;
		sortVertices();
		return 1;
	}
	return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
	int idxA = search(nodeA);
	int idxB = search(nodeB);
	if (idxA < 0 && idxB < 0) { //both nodes weren't in the Graph
		if (vertices_cnt + 2 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeA;
		GraphAdjMatrix.vertices[vertices_cnt + 1] = nodeB;
		GraphAdjMatrix.adjmatrix[vertices_cnt][vertices_cnt + 1] = true;
		GraphAdjMatrix.adjmatrix[vertices_cnt + 1][vertices_cnt] = true;
		GraphAdjMatrix.weights[vertices_cnt][vertices_cnt + 1] = weight;
		GraphAdjMatrix.weights[vertices_cnt + 1][vertices_cnt] = weight;
		vertices_cnt += 2;
		sortVertices();
		return 1;
	}
	else if (idxA >= 0 && idxB < 0) {
		if (vertices_cnt + 1 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeB;
		GraphAdjMatrix.adjmatrix[idxA][vertices_cnt] = true;
		GraphAdjMatrix.adjmatrix[vertices_cnt][idxA] = true;
		GraphAdjMatrix.weights[idxA][vertices_cnt] = weight;
		GraphAdjMatrix.weights[vertices_cnt][idxA] = weight;
		vertices_cnt++;
		sortVertices();
		return 1;
	}
	else if (idxA < 0 && idxB >= 0) {
		if (vertices_cnt + 1 > NodeMaxCount)
			return -1;
		GraphAdjMatrix.vertices[vertices_cnt] = nodeA;
		GraphAdjMatrix.adjmatrix[vertices_cnt][idxB] = true;
		GraphAdjMatrix.adjmatrix[idxB][vertices_cnt] = true;
		GraphAdjMatrix.weights[vertices_cnt][idxB] = weight;
		GraphAdjMatrix.weights[idxB][vertices_cnt] = weight;
		vertices_cnt++;
		sortVertices();
		return 1;
	}
	else { //both nodes were in the graph
		GraphAdjMatrix.adjmatrix[idxA][idxB] = true;
		GraphAdjMatrix.adjmatrix[idxB][idxA] = true;
		GraphAdjMatrix.weights[idxA][idxB] = weight;
		GraphAdjMatrix.weights[idxB][idxA] = weight;
		sortVertices();
		return 1;
	}
	return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::StronglyConnectedComponent() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
	bool* visited = new bool[vertices_cnt];
	for (int i = 0;i < vertices_cnt;i++)
		visited[i] = false;
	int* numbering = new int[vertices_cnt];
	for (int i = 0;i < vertices_cnt;i++)
		numbering[i] = 0;
	for (int i = 0;i < vertices_cnt;i++) {
		if (!visited[i])
			fillorder(i, visited, numbering);
	}
	Graph reverse = getReverse();
	int connect = 0;
	for (int i = 0;i < vertices_cnt;i++)
		visited[i] = false;
	int* order = new int[vertices_cnt];
	findHighest(numbering, order);
	string output = "";
	for (int i = 0;i < vertices_cnt;i++) {
		int s = order[i];
		if (!visited[s]) {
			string strongConnected = "";
			reverse.dfs(s, visited, strongConnected);
			strongConnected.pop_back();
			sortString(strongConnected, output);
			output.pop_back();
			output += "\n";
			connect++;
		}
	}
	/*printed in an ascending lexiographical order*/
	string* lines = new string[NodeMaxCount];
	int idx = 0;
	int start = 0;
	for (int i = 0;i < output.length();i++) {
		if (output[i] == '\n') {
			lines[idx] = output.substr(start, i - start);
			start = i + 1;
			idx++;
		}
	}
	lines[idx] = output.substr(start);
	idx++;
	for (int i = 0;i < connect-1;i++) { //sort lines in lexiographical order
		for (int j = i + 1;j < connect;j++) {
			if (lines[i] > lines[j]) {
				string tmpline = lines[i];
				lines[i] = lines[j];
				lines[j] = tmpline;
			}
		}
	}
	string result = "";
	for (int i = 0;i < connect;i++) {
		result += lines[i];
		result += "\n";
	}
	delete[] lines;
	delete[] order;
	delete[] visited;
	delete[] numbering;
	string answer = "";
	answer += to_string(connect) + "\n" + result;
  answer.pop_back();
	return answer;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::getShortestPath_task5(string source, string destination) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
	int* dist = new int[vertices_cnt];
	bool* sptSet = new bool[vertices_cnt];
	string* path = new string[vertices_cnt];
	for (int i = 0; i < vertices_cnt; i++) {
		dist[i] = INF;
		sptSet[i] = false;
		path[i] = "";
	}
	int sidx = search(source);
	int didx = search(destination);
	dist[sidx] = 0;
	for (int i = 0; i < vertices_cnt; i++) {
		int min = minDistance(dist, sptSet);
		sptSet[min] = true;
		for (int j = 0; j < vertices_cnt; j++) {
			if (!sptSet[j] && GraphAdjMatrix.adjmatrix[min][j]
				&& dist[min] != INF && dist[min] + GraphAdjMatrix.weights[min][j] < dist[j]) {
				dist[j] = dist[min] + GraphAdjMatrix.weights[min][j];
				path[j] = path[min] + " " + GraphAdjMatrix.vertices[j];
			}
		}
	}
	if (dist[didx] == INF) {
		return "error";
	}
	else {
		string answer = "";
		answer += GraphAdjMatrix.vertices[sidx];
		answer += path[didx] + " ";
		answer += to_string(dist[didx]);
		return answer;
	}

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string Graph::getShortestPath_task6(string source, string destination) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
   
	int sidx = search(source);
	int didx = search(destination);
	int** dist = new int* [vertices_cnt];
	int** next = new int* [vertices_cnt];

	for (int i = 0; i < vertices_cnt; i++) {
		dist[i] = new int[vertices_cnt];
		next[i] = new int[vertices_cnt];

		for (int j = 0; j < vertices_cnt; j++) {
			if (i == j) {
				dist[i][j] = 0;
				next[i][j] = -1;
			}
			else if (GraphAdjMatrix.adjmatrix[i][j]) {
				dist[i][j] = GraphAdjMatrix.weights[i][j];
				next[i][j] = j;
			}
			else {
				dist[i][j] = INF;
				next[i][j] = -1;
			}
		}
	}
	
	for (int k = 0;k < vertices_cnt;k++) {
		for (int i = 0;i < vertices_cnt;i++) {
			if (dist[i][k] == INF)
				continue;
			for (int j = 0;j < vertices_cnt;j++) {
				if (k == i || j == k || i == j)
					continue;

				if (dist[i][k] == INF || dist[k][j] == INF)
					continue;
				
				if (next[k][j] != i && dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = k;
				}
			}
		}
	}
	int shortest = dist[sidx][didx];
	string path = "";
	if (shortest == INF) {
		for (int i = 0; i < vertices_cnt; i++) {
			delete[] dist[i];
			delete[] next[i];
		}
		delete[] dist;
		delete[] next;
		return "INF";
	}
	path += GraphAdjMatrix.vertices[sidx] + " ";
	int cur = next[sidx][didx];
	while (cur != -1) {
		path += GraphAdjMatrix.vertices[cur] + " ";
		cur = next[cur][didx];
	}
	for (int i = 0; i < vertices_cnt; i++) {
		delete[] dist[i];
		delete[] next[i];
	}
	delete[] dist;
	delete[] next;
	string answer = path + to_string(shortest);
	return answer;
  
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
	int* parent = new int[vertices_cnt];
	int* dist = new int[vertices_cnt];
	bool* mstSet = new bool[vertices_cnt];
	for (int i = 0;i < vertices_cnt;i++) {
		dist[i] = INF;
		mstSet[i] = false;
		parent[i] = -1;
	}
	int start = search(startNode);
	dist[start] = 0;
	parent[start] = -1;

	int edge_cnt = 0;
	while (edge_cnt < vertices_cnt)
	{
		int u = findMin(dist, mstSet);
		mstSet[u] = true;

		for (int v = 0; v < vertices_cnt; v++)
		{
			if (GraphAdjMatrix.adjmatrix[u][v] && !mstSet[v] && GraphAdjMatrix.weights[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = GraphAdjMatrix.weights[u][v];
			}
			else if (GraphAdjMatrix.adjmatrix[u][v] && !mstSet[v] && GraphAdjMatrix.weights[u][v] == dist[v])
			{
				if (GraphAdjMatrix.vertices[u] < GraphAdjMatrix.vertices[v])
				{
					parent[v] = u;
					dist[v] = GraphAdjMatrix.weights[u][v];
				}
			}
		}
		string path = "";
		if (edge_cnt > 0) {
			int cur = u;
			while (cur != -1) {
				path = GraphAdjMatrix.vertices[cur] + " " + path;
				cur = parent[cur];
			}
			path.pop_back();
			fout << path << endl;
		}
		edge_cnt++;
	}
	string path = "";
	int min_cost = 0;
	for (int i = 0;i < vertices_cnt;i++) {
		if (parent[i] != -1)
			min_cost += GraphAdjMatrix.weights[i][parent[i]];
		else
			continue;
	}
	fout << to_string(min_cost) << endl;
	delete[] parent;
	delete[] dist;
	delete[] mstSet;
  return 1;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout, string endNode) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
	int edge_cnt = 0;
	for (int i = 0;i < vertices_cnt;i++) {
		for (int j = i+1;j < vertices_cnt;j++) {
			if (GraphAdjMatrix.adjmatrix[i][j] && GraphAdjMatrix.weights[i][j] != INF)
				edge_cnt++;
		}
	}
	Edge* edgeList = new Edge[edge_cnt];
	for (int i = 0;i < edge_cnt;i++) {
		edgeList[i].weight = INF;
		edgeList[i].start = "";
		edgeList[i].end = "";
	}
	int edge_idx = 0;
	for (int i = 0;i < vertices_cnt;i++) {
		for (int j = i+1;j < vertices_cnt;j++) {
			if (GraphAdjMatrix.adjmatrix[i][j] && GraphAdjMatrix.weights[i][j] != INF) {
				edgeList[edge_idx].weight = GraphAdjMatrix.weights[i][j];
				edgeList[edge_idx].start = GraphAdjMatrix.vertices[i];
				edgeList[edge_idx].end = GraphAdjMatrix.vertices[j];
				edge_idx++;
			}
		}
	}
	//sort edges in ascending order
	for (int i = 0;i < edge_cnt-1;i++) {
		for (int j = i+1;j < edge_cnt;j++) {
			if (edgeList[i].weight > edgeList[j].weight) {
				Edge temp = edgeList[i];
				edgeList[i] = edgeList[j];
				edgeList[j] = temp;
			}
		}
	}
	int min_cost = 0;
	string path = "";
	int* parent = new int[vertices_cnt];
	for (int i = 0;i < vertices_cnt;i++)
		parent[i] = i;
	for (int i = 0;i < edge_cnt;i++) {
		if (findSet(edgeList[i].start,parent) != findSet(edgeList[i].end, parent)) {
			min_cost += edgeList[i].weight;
			path = path + edgeList[i].start + " " + edgeList[i].end + " " + to_string(edgeList[i].weight);
			fout << path << endl;
			path = "";
			unionSet(findSet(edgeList[i].start, parent), findSet(edgeList[i].end, parent), parent);
		}
	}
	string smallestNode = GraphAdjMatrix.vertices[0];
	for (int i = 1; i < vertices_cnt; i++) {
		if (GraphAdjMatrix.vertices[i] < smallestNode) {
			smallestNode = GraphAdjMatrix.vertices[i];
		}
	}
	string fin_path = smallestNode;
	string curNode = smallestNode;
	bool* visited = new bool[vertices_cnt];
	for (int i = 0; i < vertices_cnt; i++)
		visited[i] = false;
	visited[search(curNode)] = true;
	while (curNode != endNode) {
		bool foundNextNode = false;
		string nextNode = "";
		for (int i = 0; i < edge_cnt; i++) {
			if (!visited[search(edgeList[i].start)] && edgeList[i].end == curNode) {
				nextNode = edgeList[i].start;
				visited[search(nextNode)] = true;
				foundNextNode = true;
				break;
			}
			else if (!visited[search(edgeList[i].end)] && edgeList[i].start == curNode) {
				nextNode = edgeList[i].end;
				visited[search(nextNode)] = true;
				foundNextNode = true;
				break;
			}
		}
		if (foundNextNode) {
			fin_path += " " + nextNode;
			curNode = nextNode;
		}
		else {
			break;
		}
	}
	fout << fin_path << " " << to_string(min_cost) << endl;
	delete[] visited;
	delete[] parent;
	delete[] edgeList;
  return 1;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
