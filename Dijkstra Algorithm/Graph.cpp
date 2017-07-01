#include <sstream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <algorithm>

#include "Graph.h"

Graph::Graph(std::string inp)
{
	std::string line;
	std::ifstream file(inp);

	if (file.is_open())
	{
		std::getline(file, line);
		//std::cout << line << std::endl;

		if (line[0] == 'D') _graphDirect = DIRECTED;
		else if (line[0] == 'U') _graphDirect = UNDIRECTED;
		if (line[0] == 'W')
		{
			_graphDirect = DIRECTED;
			_graphWeigh = WEIGHTED;
		}
		int count = 0;
		for (int i = 1; i < line.size(); i++)
		{
			if (line[i] != ',')
			{
				_vertices.push_back(std::string(1, line[i]));
				_graph.push_back(AdjNode(count, *(new std::vector<edge>())));
				count++;
			}
		}
		for (int j = 1; std::getline(file, line); j++)
		{
			int flag = 0;
			std::stringstream iss(line);
			std::string token;
			for (int dummy = 0; std::getline(iss, token, ','); ++dummy)
			{
				if (::isdigit(token[token.size() - 1]))
				{
					if (dummy > 0)
					{
						int weight = std::stoi(token);
						if (weight > 0)
							_graph[j - 1].neighbors.push_back(edge(flag, weight));
						flag++;
					}
				}
			}
		}
	}
}

std::vector<std::string> Graph::Nodes()
{
	return _vertices;
}

std::string Graph::Name(int index)
{
	if (index < _vertices.size())
		return _vertices[index];
	return "";
}

bool Graph::Rename(int index, std::string newname)
{
	if (index < _vertices.size())
	{
		_vertices[index - 1] = newname;
		return true;
	}
	return false;
}

void Graph::AddVertice(std::string _new)
{
	_vertices.push_back(_new);
	_graph.push_back(AdjNode(_vertices.size() - 1, *(new std::vector<edge>)));
}

bool Graph::RemoveVertex(std::string _remove)
{
	int index = std::find(_vertices.begin(), _vertices.end(), _remove) - _vertices.begin();
	_vertices.erase(std::find(_vertices.begin(), _vertices.end(), _remove));
	std::vector<AdjNode>::iterator removeVertex;

	for (std::vector<AdjNode>::iterator item = _graph.begin(); item != _graph.end(); item++)
	{
		if (index == item->node)
			removeVertex = item;
		else
		{
			if (item->node > index)
				item->node--;

			std::vector<edge>::iterator removeEdge = item->neighbors.end();
			for (std::vector<edge>::iterator lst = item->neighbors.begin(); lst != item->neighbors.end(); lst++)
			{
				if (index == lst->node)
					removeEdge = lst;

				else if (lst->node > index)
					lst->node--;
			}
			if (removeEdge != item->neighbors.end())
				item->neighbors.erase(removeEdge);
		}
	}
	_graph.erase(removeVertex);
	return true;
}

void Graph::AddEdge(std::string vert1, std::string vert2, direct d, weigh w, int weight)
{
	_graphDirect = d;
	_graphWeigh = w;
	int index1 = std::find(_vertices.begin(), _vertices.end(), vert1) - _vertices.begin();
	int index2 = std::find(_vertices.begin(), _vertices.end(), vert2) - _vertices.begin();

	if (index1 < _vertices.size() && index2 < _vertices.size())
	{
		_graph[index1].neighbors.push_back(edge(index2, weight));
		if (d == UNDIRECTED)
			_graph[index2].neighbors.push_back(edge(index1, weight));	
	}
}

bool Graph::RemoveEdge(std::string vert1, std::string vert2)
{
	int index1 = std::find(_vertices.begin(), _vertices.end(), vert1) - _vertices.begin();
	int index2 = std::find(_vertices.begin(), _vertices.end(), vert2) - _vertices.begin();

	if (index1 < _graph.size() && index2 < _graph.size())
		return RemoveEdge(index1, index2);

	return false;
}

bool Graph::RemoveEdge(int index1, int index2)
{
	for (std::vector<edge>::iterator lst = _graph[index1].neighbors.begin(); lst != _graph[index1].neighbors.end(); )
	{
		if (lst->node == index2)
		{
			_graph[index1].neighbors.erase(lst);
			break;
		}
		else ++lst;
	}

	if (_graphDirect == UNDIRECTED)
	{
		for (std::vector<edge>::iterator lst = _graph[index2].neighbors.begin(); lst != _graph[index2].neighbors.end(); )
		{
			if (lst->node == index1)
			{
				_graph[index2].neighbors.erase(lst);
				return true;
			}
			else ++lst;
		}
	}
	return false;
}

std::vector<edge> Graph::SingleSourceShortestPath(int node)
{
	PriorityQueue _PQ;

	std::vector<edge> minDistances;
	if (singleSourceParent.size() > 0)
		singleSourceParent.clear();
	for (auto iter: _graph)
	{
		minDistances.push_back(edge(iter.node, 0));
	}

	for (int i = 0; i < minDistances.size(); i++)
	{
		_PQ.Insert(std::numeric_limits<int>::max(), minDistances[i].node);
	}
	_PQ.Insert(0, node);

	int newWeight = 0;
	while (_PQ.Size())
	{
		int currentNode = _PQ.Minimum();
		int currentWeight = _PQ[currentNode];
		int parent = _PQ.getParent(currentNode);
		singleSourceParent.push_back(edge(currentNode, parent));
		minDistances[currentNode].weight = currentWeight;

		_PQ.ExtractMin();
		for (std::vector<AdjNode>::iterator neighbor = _graph.begin(); neighbor != _graph.end(); neighbor++)
		{
			if (neighbor->node == currentNode)
			{
				for (std::vector<edge>::iterator item = neighbor->neighbors.begin(); item != neighbor->neighbors.end(); item++)
				{
					newWeight = item->weight + currentWeight;

					if (newWeight < _PQ[item->node])
					{
						_PQ.Decrease(item->node, newWeight, currentNode);
					}
				}
				break;
			}
		}
	}

	return minDistances;
}

void Graph::PrintGraph()
{
	std::cout << "\n";
	for (auto item : _graph)
	{
		std::cout << _vertices[item.node] << " -> ";
		for (auto val : item.neighbors)
			std::cout << "(" << _vertices[val.node] << "," << val.weight << ") , ";

		std::cout << std::endl;
	}
}

void Graph::Show(std::string filename)
{
	std::ofstream _file;
	_file.open(filename + ".dot");
	if (_graphDirect == DIRECTED)_file << "digraph G { \n";
	else _file << "strict graph G { \n";
	_file << "rankdir=LR; \n";
	_file << "constraint=false;\n";
	_file << "decorate=true;\n";
	_file << "ordering=in;\n";

	for (auto item : _graph)
	{
		//for (auto val : item.neighbors)
		//	if (_graphDirect == DIRECTED && _graphWeigh == WEIGHTED)
		//		_file << "\"" << _vertices[item.node] << "\" -> \"" << _vertices[val.node] << "\" [label=\"" << val.weight << "\"]; \n";
		//	else if (_graphDirect == UNDIRECTED && _graphWeigh == WEIGHTED)
		//		_file << "\"" << _vertices[item.node] << "\" -- \"" << _vertices[val.node] << "\" [label=\"" << val.weight << "\"]; \n";
		//	else if (_graphDirect == DIRECTED)
		//		_file << "\"" << _vertices[item.node] << "\" -> \"" << _vertices[val.node] << "\" ; \n";
		//	else
		//		_file << "\"" << _vertices[item.node] << "\" -- \"" << _vertices[val.node] << "\" ; \n";

		if (item.neighbors.size() == 0)
			_file << "\"" << _vertices[item.node] << "\"\n";

		for (std::vector<edge>::iterator val = item.neighbors.begin(); val != item.neighbors.end(); val++)
		{
			edge color(val->node, item.node);

			edge iter;
			for (edge edg : singleSourceParent)
			{
				if (edg.node == val->node)
					if (edg.weight == item.node)
						iter = edg;
			}
			//iter = std::find(singleSourceParent.begin(), singleSourceParent.end(), edge(val->node, item.node));
			if(iter.node == val->node && iter.weight == item.node)
			{
				if (_graphDirect == DIRECTED && _graphWeigh == WEIGHTED)
					_file << "\"" << _vertices[item.node] << "\" -> \"" << _vertices[val->node] << "\" [color=\"red\" label=\"" << val->weight << "\"]; \n";
				else if (_graphDirect == UNDIRECTED && _graphWeigh == WEIGHTED)
					_file << "\"" << _vertices[item.node] << "\" -- \"" << _vertices[val->node] << "\" [color=\"red\" label=\"" << val->weight << "\"]; \n";
				else if (_graphDirect == DIRECTED)
					_file << "\"" << _vertices[item.node] << "\" -> \"" << _vertices[val->node] << "\" [color=\"red\"] ; \n";
				else
					_file << "\"" << _vertices[item.node] << "\" -- \"" << _vertices[val->node] << "\" [color=\"red\"] ; \n";
			}
			else
			{
				if (_graphDirect == DIRECTED && _graphWeigh == WEIGHTED)
					_file << "\"" << _vertices[item.node] << "\" -> \"" << _vertices[val->node] << "\" [label=\"" << val->weight << "\"]; \n";
				else if (_graphDirect == UNDIRECTED && _graphWeigh == WEIGHTED)
					_file << "\"" << _vertices[item.node] << "\" -- \"" << _vertices[val->node] << "\" [label=\"" << val->weight << "\"]; \n";
				else if (_graphDirect == DIRECTED)
					_file << "\"" << _vertices[item.node] << "\" -> \"" << _vertices[val->node] << "\" ; \n";
				else
					_file << "\"" << _vertices[item.node] << "\" -- \"" << _vertices[val->node] << "\" ; \n";
			}
		}
	}
	_file << "}";
	_file.close();
}

void Graph::AddToDot(std::ofstream & file, std::string parent,std::string arrow, std::string child, std::string label)
{
	file << "\"" << parent << "\"" << arrow << "\"" << child << "\"" << label << ";\n";
}
