#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include "UnionFind.h"
#include "DynamicArray.h"
using namespace std;

struct Vertex
{
	int index;
	bool visited;
	string name = " ";
	int name_index;

	Vertex()
	{
		index = -1;
		visited = false;
		name_index = -1;
	}

	Vertex(int my_index, const string& my_name)
	{
		index = my_index;
		visited = false;
		name = my_name;
		name_index = char(my_name[0]) - 65;
	}

	Vertex& operator=(const Vertex& other)
	{
		if (this != &other)
		{
			index = other.index;
			visited = other.visited;
			name = other.name;
			name_index = other.name_index;
		}
		return *this;
	}
};

struct Edge
{
	int weight;
	Vertex v1;
	Vertex v2;

	Edge() : weight(0) {};

	Edge(int my_weight, Vertex my_v1, Vertex my_v2)
	{
		weight = my_weight;
		v1 = my_v1;
		v2 = my_v2;
	}

	Edge& operator=(const Edge& other)
	{
		if (this != &other)
		{
			weight = other.weight;
			v1 = other.v1;
			v2 = other.v2;
		}
		return *this;
	}
};

class Graph
{
	int vertex_num;
	DynamicArray<Vertex> vertex_arr; 
	DynamicArray<Edge> edge_arr;
	int** matrix;

public:
	Graph();
	Graph(int);
	void change_vertex_num(int);
	Graph(const Graph&);
	Graph& operator=(const Graph&);
	~Graph();

	void add_edge(int, int, int);
	void add_vertex(int, const string&);

	bool vertex_existing(const string&);
	bool edge_existing(int, Vertex, Vertex);

	friend void quicksort(DynamicArray<Edge>&, int, int, const string&);
	void show_matrix();
	void Kruskal_alg();

	void DFS();
	void BFS();
};

Graph::Graph()
{
	vertex_num = 0;
	matrix = nullptr;
}

Graph::Graph(int my_vertex_num)
{
	vertex_num = my_vertex_num;

	matrix = new int* [vertex_num];
	for (int i = 0; i < vertex_num; i++)
	{
		matrix[i] = new int[vertex_num];
		for (int j = 0; j < vertex_num; j++)
			matrix[i][j] = 0;
	}
}

void Graph::change_vertex_num(int new_vertex_num)
{
	vertex_num = new_vertex_num;

	matrix = new int*[vertex_num];
	for (int i = 0; i < vertex_num; i++)
	{
		matrix[i] = new int[vertex_num];
		for (int j = 0; j < vertex_num; j++)
			matrix[i][j] = 0;
	}
}

Graph::Graph(const Graph& other)
{
	vertex_num = other.vertex_num;
	vertex_arr = other.vertex_arr;
	edge_arr = other.edge_arr;

	matrix = new int* [vertex_num];
	for (int i = 0; i < vertex_num; i++)
	{
		matrix[i] = new int[vertex_num];
		for (int j = 0; j < vertex_num; j++)
			matrix[i][j] = 0;
	}
}

Graph& Graph::operator=(const Graph& other)
{
	if (this != &other)
	{
		for (int i = 0; i < vertex_num; i++)
			delete[] matrix[i];

		delete[] matrix;

		vertex_num = other.vertex_num;
		vertex_arr = other.vertex_arr;
		edge_arr = other.edge_arr;

		matrix = new int* [vertex_num];
		for (int i = 0; i < vertex_num; i++)
		{
			matrix[i] = new int[vertex_num];
			for (int j = 0; j < vertex_num; j++)
				matrix[i][j] = other.matrix[i][j];
		}
	}
	return *this;
}

Graph::~Graph()
{
	for (int i = 0; i < vertex_num; i++)
		delete[] matrix[i];

	delete[] matrix;
}

bool Graph::vertex_existing(const string& curr_name)
{
	if (vertex_arr.get_size() == 0)
		return false;

	for (int i = 0; i < vertex_arr.get_size(); i++)
	{
		if (vertex_arr[i].name == curr_name)
			return true;
	}
	return false;
}

bool Graph::edge_existing(int my_weight, Vertex my_v1, Vertex my_v2)
{
	if (edge_arr.get_size() == 0)
		return false;

	for (int i = 0; i < edge_arr.get_size(); i++)
	{
		bool con1 = (edge_arr[i].v1.name == my_v1.name) || (edge_arr[i].v1.name == my_v2.name);
		bool con2 = (edge_arr[i].v2.name == my_v2.name) || (edge_arr[i].v2.name == my_v1.name);
		bool con3 = (edge_arr[i].weight == my_weight);

		if (con1 && con2 && con3)
			return true;
	}
	return false;
}

void Graph::add_vertex(int curr_index, const string& curr_name)
{
	if (!vertex_existing(curr_name))
	{
		vertex_arr.push_back(Vertex(curr_index, curr_name));
	}
	else
	{
		cout << endl << "Такая вершина уже есть в графе!" << endl;
		return;
	}
}

void Graph::add_edge(int row, int col, int weight)
{
	matrix[row][col] = weight;
	if (weight == 0)
		return;
	else if (!edge_existing(weight, vertex_arr[row], vertex_arr[col]))
		edge_arr.push_back(Edge(weight, vertex_arr[row], vertex_arr[col]));
}

void quicksort(DynamicArray<Edge>& arr, int l, int r, const string& feature)
{
	int pivot1 = 0, pivot2 = 0;
	if (l < r)
	{
		if (feature == "weight")
			pivot1 = arr[r].weight;
		else if (feature == "v1")
		{
			pivot1 = arr[r].v1.name_index;
			pivot2 = arr[r].v2.name_index;
		}
		int i = l - 1;

		for (int j = l; j < r; j++)
		{
			bool con1(false);
			bool con2(false);
			if (feature == "weight")
				con1 = (arr[j].weight < pivot1);
			else if (feature == "v1")
			{
				con1 = (arr[j].v1.name_index < pivot1);
				con2 = (arr[j].v1.name_index == pivot1) && (arr[j].v2.name_index < pivot2);
			}


			if ((con1 && feature == "weight") || ((con1 || con2) && feature == "v1"))
			{
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[r]);
		int p = i + 1;

		quicksort(arr, l, p - 1, feature);
		quicksort(arr, p + 1, r, feature);
	}
}

void Graph::show_matrix()
{
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 0; j < vertex_num; j++)
			cout << setw(5) << matrix[i][j] << " ";

		cout << endl;
	}
}

void Graph::Kruskal_alg()
{
	Graph MST(vertex_num);
	for (int i = 0; i < vertex_arr.get_size(); i++)
		MST.add_vertex(i, vertex_arr[i].name);

	quicksort(edge_arr, 0, edge_arr.get_size() - 1, "weight"); //по весу
	int MST_weight = 0;
	UnionFind uf(vertex_arr.get_size());

	for (int i = 0; i < edge_arr.get_size(); i++)
	{
		if (uf.Union(edge_arr[i].v1.index, edge_arr[i].v2.index))
		{
			MST.add_edge(edge_arr[i].v1.index, edge_arr[i].v2.index, edge_arr[i].weight);
			MST_weight += edge_arr[i].weight;
		}
	}

	quicksort(MST.edge_arr, 0, MST.edge_arr.get_size() - 1, "v1"); //по 1 и 2 вершине
	for (int k = 0; k < MST.edge_arr.get_size(); k++)
	{
		cout << (k + 1) << ". ";
		cout << MST.edge_arr[k].v1.name << " " << MST.edge_arr[k].v2.name << endl;
	}
	cout << endl << "Вес минимального остовного дерева: " << MST_weight << endl;
}

void Graph::DFS()
{
	for (int point = 0; point < vertex_arr.get_size(); point++)
	{
		cout << endl << "Обход относительно вершины " << vertex_arr[point].name << ":" << endl;
		for (int i = 0; i < vertex_arr.get_size(); i++)
			vertex_arr[i].visited = false;

		stack<Vertex> s;
		vertex_arr[point].visited = true;
		s.push(vertex_arr[point]);

		while (!s.empty())
		{
			Vertex v = s.top();
			s.pop();
			cout << v.name << " ";
			for (int i = 0; i < vertex_num; i++)
			{
				if (matrix[i][v.index] != 0 && (vertex_arr[i].visited == false))
				{
					s.push(vertex_arr[i]);
					vertex_arr[i].visited = true;
				}
			}
		}
		cout << endl;
	}
}

void Graph::BFS()
{
	for (int point = 0; point < vertex_arr.get_size(); point++)
	{
		cout << endl << "Обход относительно вершины " << vertex_arr[point].name << ":" << endl;

		for (int i = 0; i < vertex_num; i++)
			vertex_arr[i].visited = false;

		queue <Vertex> q;
		vertex_arr[point].visited = true;
		q.push(vertex_arr[point]);

		while (!q.empty())
		{
			Vertex v = q.front();
			q.pop();
			cout << v.name << " ";
			for (int i = 0; i < vertex_num; i++)
			{
				if (matrix[i][v.index] != 0 && (vertex_arr[i].visited == false))
				{
					q.push(vertex_arr[i]);
					vertex_arr[i].visited = true;
				}
			}
		}
		cout << endl;
	}
}