#include <string>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include "Graph.h"

void TestCase4(Graph& graph)
{
	graph.AddVertice("z");
	graph.AddEdge("z", "w");
	graph.AddEdge("z", "x");
	graph.AddEdge("z", "y");

	graph.Show("t4a");
	std::cout << "Generated t4a.dot" << std::endl;

	graph.RemoveVertex("s");
	graph.RemoveVertex("x");
	graph.RemoveEdge("u", "t");
	graph.Show("t4b");
	std::cout << "Generated t4b.dot" << std::endl;
}

void TestCase5(Graph& graph)
{
	for (int i = 6; i < 11; i++)
		graph.AddVertice(std::to_string(i));

	graph.AddEdge("6", "7");
	graph.AddEdge("7", "8");
	graph.AddEdge("8", "9");
	graph.AddEdge("9", "10");
	graph.AddEdge("10", "6");

	for (int i = 1; i <= 5; i++)
		graph.AddVertice(std::to_string(i));

	graph.AddEdge("1", "6");
	graph.AddEdge("2", "7");
	graph.AddEdge("3", "8");
	graph.AddEdge("4", "9");
	graph.AddEdge("5", "10");

	graph.Show("t5a");
	std::cout << "Generated t5a.dot" << std::endl;

	graph.RemoveVertex("8");
	graph.RemoveVertex("6");
	graph.Show("t5b");
	std::cout << "Generated t5b.dot" << std::endl;
}

void TestCase6(Graph& graph)
{
	for (int i = 2; i <= 10; i += 2)
		graph.AddVertice(std::to_string(i));

	graph.AddEdge("2", "4", DIRECTED);
	graph.AddEdge("2", "6", DIRECTED);
	graph.AddEdge("4", "6", DIRECTED);
	graph.AddEdge("4", "8", DIRECTED);
	graph.AddEdge("6", "8", DIRECTED);
	graph.AddEdge("6", "10", DIRECTED);
	graph.AddEdge("8", "10", DIRECTED);
	graph.AddEdge("8", "2", DIRECTED);

	for (int i = 1; i < 10; i += 2)
		graph.AddVertice(std::to_string(i));

	graph.AddEdge("1", "2", DIRECTED);
	graph.AddEdge("3", "4", DIRECTED);
	graph.AddEdge("5", "6", DIRECTED);
	graph.AddEdge("7", "8", DIRECTED);
	graph.AddEdge("9", "10", DIRECTED);

	graph.Show("t6a");
	std::cout << "Generated t6a.dot" << std::endl;

	std::string vertices1[] = { "2","4","6","8","10" };
	std::string vertices2[] = { "1","3","5","7","9" };
	srand(time(NULL));
	std::string v1 = vertices1[rand() % 5];
	std::string v2 = vertices2[rand() % 5];
	std::cout << "Vertex " << v1 << " is being removed" << std::endl;
	graph.RemoveVertex(v1);
	std::cout << "Vertex " << v2 << " is being removed" << std::endl;
	graph.RemoveVertex(v2);
	graph.Show("t6b");
	std::cout << "Generated t6b.dot" << std::endl;
}

void TestCase8(Graph& graph)
{
	graph.SetDirection(DIRECTED);
	std::vector<edge> minDistance;
	std::vector<std::string> nodes = graph.Nodes();
	for (auto vertex : nodes)
	{
		std::cout << "" <<std::setw(3) << vertex;
	}
	std::cout << "\n-----------------" << std::endl;
	for (int i = 0; i < 5; i++) 
	{
		minDistance = graph.SingleSourceShortestPath(i);
		std::cout << nodes[i];
		for (auto edg : minDistance)
			std::cout << std::setw(3) << edg.weight;
		std::cout << std::endl;
	}
}

void TestCase9(Graph& graph)
{
	std::vector<std::string> nodes = graph.Nodes();
	graph.SingleSourceShortestPath(0);

	std::cout<<std::setw(6) << "Vertex"
		<< std::setw(32) << "Path from source s to vertex";
	std::cout << "\n----------------------------------" << std::endl;
	std::string output;
	std::vector<edge> parent = graph.GetSingleSourceParent();
	for (int node = 0; node < 5; node++)
	{
		int _node = node;
		output = "";
		for (int i = parent.size() - 1; i >= 0; i--)
		{
			if (parent[i].node == _node)
			{
				_node = parent[i].weight;
				if (_node < 0)
					break;
				output += nodes[_node];
			}
		}
		std::cout << std::setw(5) << nodes[node];
		std::cout << std::setw(12);
		for (std::string::reverse_iterator iter = output.rbegin(); iter != output.rend(); ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << "\n";
	}

	graph.SingleSourceShortestPath(4);
	parent = graph.GetSingleSourceParent();
	std::cout << std::setw(6) << "Vertex"
		<< std::setw(32) << "Path from source z to vertex";
	std::cout << "\n----------------------------------" << std::endl;
	for (int node = 0; node < 5; node++)
	{
		int _node = node;
		output = "";
		for (int i = parent.size() - 1; i >= 0; i--)
		{
			if (parent[i].node == _node)
			{
				_node = parent[i].weight;
				if (_node < 0)
					break;
				output += nodes[_node];
			}
		}
		std::cout << std::setw(5) << nodes[node];
		std::cout << std::setw(12);
		for (std::string::reverse_iterator iter = output.rbegin(); iter != output.rend(); ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << "\n";
	}
}

void TestCase10(Graph& graph)
{
	graph.SetDirection(UNDIRECTED);
	std::vector<std::string> nodes = graph.Nodes();
	graph.SingleSourceShortestPath(0);

	std::cout << std::setw(6) << "Vertex"
		<< std::setw(32) << "Path from source s to vertex";
	std::cout << "\n----------------------------------" << std::endl;
	std::string output;
	std::vector<edge> parent = graph.GetSingleSourceParent();
	for (int node = 0; node < 5; node++)
	{
		int _node = node;
		output = "";
		for (int i = parent.size() - 1; i >= 0; i--)
		{
			if (parent[i].node == _node)
			{
				_node = parent[i].weight;
				if (_node < 0)
					break;
				output += nodes[_node];
			}
		}
		std::cout << std::setw(5) << nodes[node];
		std::cout << std::setw(12);
		for (std::string::reverse_iterator iter = output.rbegin(); iter != output.rend(); ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << "\n";
	}

	graph.SingleSourceShortestPath(4);
	parent = graph.GetSingleSourceParent();
	std::cout << std::setw(6) << "Vertex"
		<< std::setw(32) << "Path from source z to vertex";
	std::cout << "\n----------------------------------" << std::endl;
	for (int node = 0; node < 5; node++)
	{
		int _node = node;
		output = "";
		for (int i = parent.size() - 1; i >= 0; i--)
		{
			if (parent[i].node == _node)
			{
				_node = parent[i].weight;
				if (_node < 0)
					break;
				output += nodes[_node];
			}
		}
		std::cout << std::setw(5) << nodes[node];
		std::cout << std::setw(12);
		for (std::string::reverse_iterator iter = output.rbegin(); iter != output.rend(); ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << "\n";
	}
}

int main()
{
	std::cout << "Test Case: 1\n=========================" << std::endl;
	Graph G1("fig1.csv");
	G1.Show("t1");
	std::cout << "Generated t1.dot" << std::endl;

	std::cout << "\nTest Case: 2\n=========================" << std::endl;
	Graph G2("fig2.csv");
	G2.Show("t2");
	std::cout << "Generated t2.dot" << std::endl;

	std::cout << "\nTest Case: 3\n=========================" << std::endl;
	Graph G3("fig3-w.csv");
	G3.Show("t3");
	std::cout << "Generated t3.dot" << std::endl;

	std::cout << "\nTest Case: 4\n=========================" << std::endl;
	TestCase4(G1);

	std::cout << "\nTest Case: 5\n=========================" << std::endl;
	Graph G5;
	TestCase5(G5);

	std::cout << "\nTest Case: 6\n=========================" << std::endl;
	Graph G6;
	TestCase6(G6);

	std::cout << "\nTest Case: 7\n=========================" << std::endl;
	Graph G7("fig3-w.csv");
	TestCase8(G7);

	std::cout << "\nTest Case: 8\n=========================" << std::endl;
	Graph G8("fig4.csv");
	TestCase8(G8);

	std::cout << "\nTest Case: 9\n=========================" << std::endl;
	Graph G9("fig3-w.csv");
	TestCase9(G9);

	std::cout << "\nTest Case: 10\n=========================" << std::endl;
	TestCase10(G8);

	std::cout << "\nTest Case: 11\n=========================" << std::endl;
	Graph G11("fig3-w.csv");
	G11.SingleSourceShortestPath(0);
	G11.Show("t11");
	std::cout << "Generated t11.dot" << std::endl;

	std::cout << "\nTest Case: 12\n=========================" << std::endl;
	Graph G12("fig4.csv");
	G12.SetDirection(UNDIRECTED);
	G12.SingleSourceShortestPath(0);
	G12.Show("t12");
	std::cout << "Generated t12.dot" << std::endl;

	return 0;
}
