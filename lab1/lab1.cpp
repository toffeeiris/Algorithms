#include <iostream>
#include <cmath>
#include "Stack.h"
#include "DynamicArray.h"
#include "DLinkedList.h"
#include <iomanip>

using namespace std;

int lead(char op)
{
	if (op == '+' || op == '-') return 1;
	else if (op == '*' || op == '/') return 2;
	else if (op == '^') return 3;
	else if (op == 's' || op == 'c') return 4;
	else return 0;
}

bool is_op(char token)
{
    if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^')
        return true;
    else
        return false;
}

bool is_left_associative(char op) {
    return op != '^'; // Все операторы, кроме '^', левосторонние
}

bool shunting_yard(bool fail)
{
    DynamicArray<char> exp;
    DLinkedList<char> res;
    char token, next_token;
    int j = 0;
    while (cin.get(token))
    {
        exp.insert(j, token);
        ++j;
        if (cin.peek() == '\n') break;
    }

    if (is_op(exp[1]) || is_op(exp[j-1]))
    {
        cout << "Ошибка в введенном выражении!" << endl;
        return false;
    }

    Stack<char> ops; //операции 

    for (int i = 0; i < exp.get_size(); i++)
    {
        token = exp[i];
        next_token = exp[i + 1];
        if (isdigit(token))
        {
            if (!isdigit(next_token))
            {
                res.push_back(token);
            }
            else
            {
                res.push_back('(');
                while (isdigit(exp[i]))
                {
                    res.push_back(exp[i++]);
                }
                res.push_back(')');
                i--;
            }
        }
        else if (token == 's' || token == 'c')
        {
            
            if (exp[i + 3] != '(')
            {
                cout << "Ошибка в введенном выражении!" << endl;
                return false;
                break;
            }
            else if ((exp[i - 1] == ')') || isdigit(exp[i - 1]))
            {
                cout << "Ошибка в введенном выражении! Вы пропустили операцию!" << endl;
                return false;
                break;
            }
            else if ((exp[i] == 's' && (exp[i + 1] != 'i' || exp[i + 2] != 'n')) || \
                (exp[i] == 'c' && (exp[i + 1] != 'o' || exp[i + 2] != 's')))
            {
                cout << "Ошибка в введенном выражении! Неверная запись функции!" << endl;
                return false;
                break;
            }
            ops.push(token);
            i += 2;
        }
        else if (is_op(token))
        {
            if (is_op(next_token))
            {
                cout << "Ошибка в введенном выражении! Операции идут подряд!" << endl;
                return false;
                break;
            }

            while (!ops.empty() && lead(ops.top()) > lead(token))
            {
                res.push_back(ops.top());
                ops.pop();
            }

            if (!ops.empty() && lead(ops.top()) == lead(token) && is_left_associative(token)) 
            {
                res.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
        else if (token == '(')
        {
            if (next_token == ')')
            {
                cout << "Ошибка в введенном выражении! Пустое значение в скобках!" << endl;
                return false;
                break;
            }
            ops.push(token);
        }
        else if (token == ')')
        {
            if ((next_token == '(') || isdigit(next_token))
            {
                cout << "Ошибка в введенном выражении! Вы пропустили операцию!" << endl;
                return false;
                break;
            }

            while (!ops.empty() && ops.top() != '(')
            {
                res.push_back(ops.top());
                ops.pop();
            }
            
            if (ops.empty())
            {
                cout << "Ошибка в введенном выражении!" << endl;
                return false;
                break;
            }
            ops.pop(); 
        }
    }

    while (!ops.empty()) 
    {
        if (ops.top() == '(')
        {
            cout << "Ошибка в введенном выражении!" << endl;
            return false;
            break;
        }
        res.push_back(ops.top());
        ops.pop();
    }

    cout << "\nРезультат: ";
    for (int i = 0; i < res.get_size(); i++)
    {
        if (res[i] == 'c')
            cout << "cos";
        else if (res[i] == 's')
            cout << "sin";
        else
            cout << res[i];
    }
    cout << endl;

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
    
    while (true)
    {
        system("cls");
        int ch = 0;
        cout << "Меню:" << endl;
        cout << "1. Функционал двухсвязного списка" << endl;
        cout << "2. Функционал димамического массива" << endl;
        cout << "3. Функционал стека" << endl;
        cout << "4. Алгоритм сортировочной станции" << endl;
        cout << "5. Выход из программы" << endl;
        cout << endl << "*Функционал списка, массива и стека проверяется на числах!! Вводите только их!" << endl << endl;
        ch = input(ch, 5);
        switch (ch)
        {
        case 1:
        {
            DLinkedList<double> my_list;
            bool flag = false;
            while (!flag)
            {
                system("cls");
                int choice = 0;
                cout << "1. Вставить элемент в начало списка" << endl;
                cout << "2. Вставить элемент в конец списка" << endl;
                cout << "3. Удалить элемент" << endl;
                cout << "4. Узнать размер" << endl;
                cout << "5. Вывести список" << endl;
                cout << "6. Вернуться в меню" << endl;
                choice = input(choice, 6);
                switch (choice)
                {
                case 1:
                {
                    double item;
                    cout << "Элемент: ";
                    cin >> item;
                    my_list.push_front(item);
                    system("pause");
                    break;
                }
                case 2:
                {
                    double item;
                    cout << "Элемент: ";
                    cin >> item;
                    my_list.push_back(item);
                    system("pause");
                    break;
                }
                case 3:
                {
                    if (my_list.get_size() == 0)
                        cout << "Список пуст!" << endl;
                    else
                    {
                        int ind;
                        cout << "Индекс: ";
                        cin >> ind;
                        if (ind < 0 || ind >= my_list.get_size())
                            cout << "Индекс вне диапазона!" << endl;
                        else
                            my_list.remove(ind);
                    }
                    

                    system("pause");
                    break;
                }
                case 4:
                {
                    cout << "Текущий размер списка: " << my_list.get_size() << endl;
                    system("pause");
                    break;
                }
                case 5:
                {
                    cout << "Текущее состояние списка: ";
                    if (my_list.get_size() == 0)
                        cout << "(список пуст)" << endl;
                    else
                    {
                        for (int i = 0; i < my_list.get_size(); i++)
                        {
                            cout << my_list[i] << " ";
                        }
                        cout << endl;
                    }
                    system("pause");
                    break;
                }
                case 6:
                {
                    flag = true;
                    break;
                }
                default:
                {
                    cout << "Нет такое пункта!";
                    system("pause");
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            DynamicArray<double> my_array;
            bool flag = false;
            bool create = false;
            while (!flag)
            {
                system("cls");
                int choice = 0;
                cout << "1. Создать массив" << endl;
                cout << "2. Вставить элемент" << endl;
                cout << "3. Удалить элемент" << endl;
                cout << "4. Узнать размер" << endl;
                cout << "5. Изменить значение элемента по индексу" << endl;
                cout << "6. Вывести массив" << endl;
                cout << "7. Вернуться в меню" << endl;
                choice = input(choice, 7);
                switch (choice)
                {
                case 1:
                {
                    if (!create)
                    {
                        int N;
                        double item;
                        cout << "Размер: ";
                        cin >> N;
                        for (int i = 0; i < N; i++)
                        {
                            cout << (i + 1) << ": ";
                            cin >> item;
                            my_array.insert(i, item);
                        }
                        create = true;
                    }
                    else
                    {
                        cout << "Вы уже создали массив! Теперь добавляйте элементы!" << endl;
                    }
                    system("pause");
                    break;
                }
                case 2:
                {
                    if (!create)
                    {
                        cout << "Сначала создайте массив!" << endl;
                    }
                    else
                    {
                        int ind;
                        double item;
                        cout << "Индекс: ";
                        cin >> ind;

                        if (ind < 0)
                            cout << "Индекс не может иметь такое значение!" << endl;
                        else
                        {
                            cout << "Элемент: ";
                            cin >> item;
                            my_array.insert(ind, item);
                        }
                    }

                    system("pause");
                    break;
                }
                case 3:
                {
                    if (create == false)
                    {
                        cout << "Сначала создайте массив!" << endl;
                    }
                    else
                    {
                        int ind;
                        cout << "Индекс: ";
                        cin >> ind;
                        if (ind < 0 || ind >= my_array.get_size())
                            cout << "Индекс вне диапазона!" << endl;
                        else
                            my_array.remove(ind);
                    }

                    system("pause");
                    break;
                }
                case 4:
                {
                    cout << "Текущий размер массива: " << my_array.get_size() << endl;
                    system("pause");
                    break;
                }
                case 5:
                {
                    if (create == false)
                    {
                        cout << "Сначала создайте массив!" << endl;
                    }
                    else
                    {
                        int ind;
                        double item;
                        cout << "Индекс: ";
                        cin >> ind;

                        if (ind < 0 || ind >= my_array.get_size())
                            cout << "Индекс не может иметь такое значение!" << endl;
                        else
                        {
                            cout << "Элемент: ";
                            cin >> item;
                            my_array.change_item(ind, item);
                        }
                    }

                    system("pause");
                    break;
                }
                case 6:
                {
                    if (create == false)
                    {
                        cout << "Массив пуст!" << endl;
                    }
                    else
                    {
                        cout << "Текущее состояние массива: ";
                        for (int i = 0; i < my_array.get_size(); i++)
                        {
                            cout << my_array[i] << " ";
                        }
                        cout << endl;
                    }

                    system("pause");
                    break;
                }
                case 7:
                {
                    flag = true;
                    break;
                }
                default:
                {
                    cout << "Нет такое пункта!" << endl;
                    system("pause");
                    break;
                }
                }
            }
            break;
        }
        case 3:
        {
            Stack<double> my_stack;
            bool flag = false;
            while (!flag)
            {
                system("cls");
                int choice = 0;
                cout << "1. Добавить элемент" << endl;
                cout << "2. Удалить элемент" << endl;
                cout << "3. Вернуть элемент на вершине стека" << endl;
                cout << "4. Вернуться в меню" << endl;
                cout << endl << "Состояние стека: ";
                my_stack.show();
                cout << endl;
                choice = input(choice, 4);
                switch (choice)
                {
                case 1:
                {
                    double item;
                    cout << "Элемент: ";
                    cin >> item;
                    my_stack.push(item);
                    system("pause");
                    break;
                }
                case 2:
                {
                    if (my_stack.empty())
                        cout << "Нечего удалять!" << endl;
                    else
                        my_stack.pop();

                    system("pause");
                    break;
                }
                case 3:
                {
                    if (my_stack.empty())
                        cout << "В стеке ничего нет!" << endl;
                    else
                        cout << "Элемент на вершине стека: " << my_stack.top() << endl;

                    system("pause");
                    break;
                }
                case 4:
                {
                    flag = true;
                    break;
                }
                default:
                {
                    cout << "Нет такое пункта!" << endl;
                    system("pause");
                    break;
                }
                }
            }
            break;
        }
        case 4:
        {
            bool flag = false;
            while (!flag)
            {
                system("cls");
                int choice = 0;
                cout << "1. Ввести выражение" << endl;
                cout << "2. Вернуться в меню" << endl;
                choice = input(choice, 2);
                switch (choice)
                {
                case 1:
                {
                    bool fail = false;
                    while (!fail)
                    {
                        cout << "Ваше выражение: ";
                        fail = shunting_yard(fail);
                    }
                    system("pause");
                    break;
                }
                case 2:
                {
                    flag = true;
                    break;
                }
                default:
                {
                    cout << "Нет такое пункта!";
                    system("pause");
                    break;
                }
                }
            }
            break;
        }
        case 5:
        {
            return 0;
            break;
        }
        }
    }
}
