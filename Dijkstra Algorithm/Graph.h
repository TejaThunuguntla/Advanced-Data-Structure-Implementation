#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

enum weigh { UNWEIGHTED, WEIGHTED };
enum direct { UNDIRECTED, DIRECTED };


struct edge
{
	int node;
	int weight;

	edge()
	{
		node = 0;
		weight = 0;
	}

	edge(int _node, int _weight)
	{
		node = _node;
		weight = _weight;
	}

	bool operator<(const edge& rhs) const 
	{
		return weight < rhs.weight;
	}

	bool operator==(const edge& rhs)
	{
		if (node == rhs.node)
			if (weight = rhs.weight)
				return true;
		return false;
	}
};

struct AdjNode
{
	int node;
	std::vector<edge> neighbors;

	std::vector<edge>& operator=(const std::vector<edge> vec)
	{
		return neighbors = vec;
	}

	AdjNode(int node, std::vector<edge> neighbor)
	{
		this->node = node;
		this->neighbors = neighbor;
	}

	AdjNode(int node, edge neighbor)
	{
		this->node = node;
		this->neighbors.push_back(neighbor);
	}
};

class Graph
{
public:
	Graph() {}
	Graph(std::string inp);
	
	std::vector<edge> SingleSourceShortestPath(int node);
	bool Rename(int index, std::string newname);
	void AddVertice(std::string _new);
	bool RemoveVertex(std::string _remove);
	void AddEdge(std::string vert1, std::string vert2, direct = UNDIRECTED ,weigh = UNWEIGHTED,int weight = 1);
	bool RemoveEdge(std::string vert1, std::string vert2);
	void SetDirection(direct _d) { _graphDirect = _d; }
	void PrintGraph();
	std::string Name(int index);
	std::vector<std::string> Nodes();
	std::vector<edge> GetSingleSourceParent() { return singleSourceParent; }
	void Show(std::string filename);
private:
	weigh _graphWeigh;
	direct _graphDirect;
	std::vector<std::string> _vertices;
	std::vector<edge> singleSourceParent;
	std::vector<AdjNode> _graph;
	bool RemoveEdge(int vert1, int vert2);
	void AddToDot(std::ofstream& file, std::string parent, std::string arrow, std::string child, std::string label);
};

#endif
