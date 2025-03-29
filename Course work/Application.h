#include <fstream>
#include <string>
#include <sstream>

#include "Graph.h"

class Application
{
	int num_options;
    ifstream file;
    Graph g;

public:
	Application(int, const string&);
	~Application();
	void menu();
	void run();
	bool file_reading();
    int input(int, int);
};

Application::Application(int my_num_options, const string& filename) 
{
    num_options = my_num_options;
    file.open(filename);
}

Application::~Application()
{
    if (file.is_open())
        file.close();
}

int Application::input(int ch, int n)
{
    bool check = false;
    while (!check)
    {
        cout << "> ";
        if (!(cin >> ch) || ch < 0 || ch > n || cin.peek() != '\n')
        {
            cout << "������������ ����!" << endl;
            cin.clear();
            check = false;
            while (cin.get() != '\n');
        }
        else check = true;
    }
    return ch;
}

void Application::menu()
{
    system("cls");
    cout << "����:" << endl;
    cout << "1. ��������� �������� ��������" << endl;
    cout << "2. ����� ����� � �������" << endl;
    cout << "3. ����� ����� � ������" << endl;
    cout << "4. ����� �� ���������" << endl;
}

void Application::run()
{
    
    while (true)
    {
        menu();
        int ch = input(0, 4);
        switch (ch)
        {
        case 1:
        {
            cout << endl << "������� ��������� �����:" << endl;
            g.show_matrix();
            cout << endl;
            g.Kruskal_alg();
            cout << endl;
            system("pause");
            break;
        }
        case 2:
        {
            g.DFS();
            cout << endl;
            system("pause");
            break;
        }
        case 3:
        {
            g.BFS();
            cout << endl;
            system("pause");
            break;
        }
        case 4:
        {
            exit(0);
            break;
        }
        }
    }
}

bool Application::file_reading()
{
    if (!file)
    {
        cout << endl << "�� ������� ������� ����!" << endl;
        return false;
    }

    string line;
    int i = 0;
    if (getline(file, line))
    {
        istringstream iss(line);
        string name;
        while (iss >> name)
            g.add_vertex(i++, name);
    }

    g.change_vertex_num(i);

    int row = 0, col = 0;
    while (getline(file, line))
    {
        istringstream iss(line);
        int weight;

        col = 0;
        while (iss >> weight)
        {
            g.add_edge(row, col, weight);
            ++col;
        }
        ++row;
    }
    
    return true;
}