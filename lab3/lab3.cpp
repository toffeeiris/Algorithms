#include <iostream>
#include <fstream>
#include "BinaryTree.h"
#include "AVLTree.h"
#include "DynamicArray.h"

using namespace std;

bool bracket_notation(BinaryTree<int> &b, bool fail, vector<int> &nums)
{
    DynamicArray<char> exp;
    stack<BT_node<int>*> t_items;
    char token, next_token;
    int open = 0, close = 0;
    
    ifstream file("input.txt");

    if (!file)
    {
        cout << endl << "Не удалось открыть файл!" << endl;
        return false;
    }

    while (file.get(token))
    {
        exp.push_back(token);
        if (token == '\n') break;
    }
    file.close();

    for (int i = 0; i < exp.get_size(); i++)
        cout << exp[i];
    cout << endl;

    if (exp[0] != '(' || exp[exp.get_size() - 1] != ')' || exp.get_size() == 0)
    {
        cout << "Ошибка в скобочной записи!";
        return false;
    }

    BT_node<int>* curr = nullptr;
    for (int i = 1; i < exp.get_size() - 1; i++)
    {
        token = exp[i];
        next_token = exp[i + 1];

        if (isdigit(token))
        {
            int number = 0;
            while (i < (exp.get_size() - 2) && isdigit(exp[i]))
            {
                number *= 10;
                number += (exp[i++] - '0');
            }
            i--;
            nums.push_back(number);

            if (curr == nullptr)
            {
                b = BinaryTree<int>(number);
                curr = b.get_root();
                t_items.push(curr);
            }
            else
            {
                if (!b.has_l_child(curr))
                {
                    curr = b.l_child_add(curr, number);
                    t_items.push(curr);
                }
                else if (!b.has_r_child(curr))
                {
                    curr = b.r_child_add(curr, number);
                    t_items.push(curr); 
                }
                else if (b.has_l_child(curr) && b.has_r_child(curr))
                {
                    cout << "Это не двоичное дерево!";
                    return false;
                    break;
                }

            }
        }
        else if (token == '(')
        {
            if (next_token == '(' || next_token == ')')
            {
                cout << "Ошибка в скобочной записи!";
                return false;
                break;
            }
            open++;
        }
        else if (token == ')')
        {
            close++;
            if (!t_items.empty())
                t_items.pop();

            if (!t_items.empty())
                curr = t_items.top();
        }
    }

    if (open != close)
    {
        cout << "Ошибка в скобочной записи!";
        return false;
    }

    return true;
}

int input(int ch, int n)
{
    bool check = false;
    while (!check)
    {
        cout << "> ";
        if (!(cin >> ch) || ch < 0 || ch > n || cin.peek() != '\n')
        {
            cout << "Некорректный ввод!" << endl;
            cin.clear();
            check = false;
            while (cin.get() != '\n');
        }
        else check = true;
    }
    return ch;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    bool created = false;
    BinaryTree<int> b;
    vector<int> nums;

    while (true)
    {
        system("cls");
        int ch = 0;
        cout << "Меню:" << endl;
        cout << "1. Проверить алгоритм для парсинга скобочной записи" << endl;
        cout << "2. Обход двоичного дерева" << endl;
        cout << "3. Функционал АВЛ дерева" << endl;
        cout << "4. Выход из программы" << endl;
        ch = input(ch, 4);
        switch (ch)
        {
        case 1:
        {
            if (created)
            {
                BinaryTree<int> new_b;
                b = new_b;
                vector<int> new_nums;
                nums = new_nums;
            }

            cout << endl << "Ваше выражение: ";
            created = bracket_notation(b, created, nums);
            if (!created)
            {
                cout << endl << "Попробуйте изменить запись двоичного дерева! Она неверна!" << endl << endl;
                created = false;
            }
            else
            {
                cout << "Двоичное дерево создано!" << endl << endl;
                created = true;
            }
            system("pause");
            break;
        }
        case 2:
        {
            if (created)
            {
                BT_node<int>* my_root = b.get_root();
                cout << endl << "Варианты обхода: ";
                cout << "\n1. Прямой: ";
                b.pre_order(my_root);
                cout << "\n\n2. Центрированный: ";
                b.in_order(my_root);
                cout << "\n\n3. Обратный: ";
                b.post_order(my_root);
                cout << endl << endl;
            }
            else
            {
                cout << "Снанача прочитайте корректную скобочную запись!" << endl;
            }

            system("pause");
            break;
        }
        case 3:
        {
            if (created)
            {
                bool flag = false;
                AVLTree<int> avl(nums[0]);
                AVL_node<int>* avl_root;
                //создание авл дерева на основе скобочной записи
                for (int i = 1; i < nums.size(); i++)
                    avl.insert(nums[i]);

                while (!flag)
                {
                    system("cls");
                    int choice = 0;
                    cout << "1. Вставить элемент" << endl;
                    cout << "2. Удалить элемент" << endl;
                    cout << "3. Поиск элемента" << endl;
                    cout << "4. Обход в ширину" << endl;
                    cout << "5. Обход в глубину (3 вида)" << endl;
                    cout << "6. Вернуться в меню" << endl;
                    choice = input(choice, 6);
                    switch (choice)
                    {
                    case 1:
                    {
                        int new_node;
                        cout << "Введите значение для нового элемента: ";
                        cin >> new_node;
                        avl.insert(new_node);
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        int rem_node;
                        cout << "Введите значение, которое хотите удалить: ";
                        cin >> rem_node;
                        avl.remove(rem_node);
                        cout <<"Элемент удален!" << endl;
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        int s_node;
                        cout << "Введите значение, которое хотите найти: ";
                        cin >> s_node;
                        avl_root = avl.get_root();
                        AVL_node<int>* found_node = avl.search(avl_root, s_node);
                        if (found_node == nullptr)
                        {
                            cout << endl << "Такого значения нет в дереве!" << endl;
                        }
                        else
                        {
                            cout << endl << "Данное значение есть в дереве!" << endl;
                            cout << "Вот информация об этом узле:" << endl;
                            avl.get_info(found_node);
                            cout << endl;
                        }
                        system("pause");
                        break;
                    }
                    case 4:
                    {
                        avl_root = avl.get_root();
                        cout << endl << "Обход в ширину: " << endl;
                        avl.breadth_search(avl_root);
                        cout << endl;
                        system("pause");
                        break;
                    }
                    case 5:
                    {
                        avl_root = avl.get_root();
                        cout << endl << "Обход в глубину: " << endl;
                        cout << "\n1. Прямой: ";
                        avl.pre_order_search(avl_root);
                        cout << "\n\n2. Центрированный: ";
                        avl.in_order_search(avl_root);
                        cout << "\n\n3. Обратный: ";
                        avl.post_order_search(avl_root);
                        cout << endl;
                        system("pause");
                        break;
                    }
                    case 6:
                    {
                        flag = true;
                        break;
                    }
                    }
                }
            }
            else
            {
                cout << "Снанача создайте двоичное дерево!" << endl;
            }
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