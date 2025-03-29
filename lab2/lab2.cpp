#include <iostream>
#include <locale.h>
#include <ctime>
#include <stack> 
#include "DynamicArray.h"

using namespace std;

bool is_sorted(DynamicArray<int>& arr)
{
    for (int i = 1; i < arr.get_size(); i++)
    {
        if (arr[i - 1] > arr[i]) 
            return false;
    }
    return true;
}

struct couple 
{
    int start;
    int size;
};

int f_minrun(int n) 
{
    int junior_pos = 0;
    while (n >= 64) 
    {
        junior_pos |= (n & 1);
        n >>= 1;
    }
    return (n + junior_pos);
}

void insertion_sort(DynamicArray<int>& arr, int left, int right)
{
    int value, i, j;
    for (i = left + 1; i <= right; i++) 
    {
        value = arr[i];

        for (j = i - 1; j >= left && arr[j] > value; j--)
            arr[j + 1] = arr[j];

        arr[j + 1] = value;
    }
}

void galloping(DynamicArray <int>& arr, DynamicArray <int>& L, DynamicArray <int>& R, int& i, int& j, int& k, int part)
{
    int first, mid, last;
    int key;
    if (part == 1)
    {
        while (j < R.get_size() && i < L.get_size())
        {
            key = R[j];
            first = i;
            last = L.get_size();

            while (first < last)
            {
                mid = first + (last - first) / 2;
                (L[mid] < key) ? (first = mid + 1) : (last = mid);
            }

            while (i < first)
                arr[k++] = L[i++];
            
            arr[k++] = key;
            j++;
        }
    }
    else if (part == 2)
    {
        while (i < L.get_size() && j < R.get_size())
        {
            key = L[i];
            first = j;
            last = R.get_size();

            while (first < last)
            {
                mid = first + (last - first) / 2;
                (R[mid] < key) ? (first = mid + 1) : (last = mid);
            }

            while (j < first)
                arr[k++] = R[j++];
            
            arr[k++] = key;
            i++;
        }
    }
}

void merge(DynamicArray <int>& arr, int left, int mid, int right)
{
    DynamicArray <int> L(mid - left + 1);
    DynamicArray <int> R(right - mid);
    int i, j, k;

    for (i = 0, k = left; k <= mid; k++, i++)
        L.push_back(arr[k]);

    for (j = 0, k = mid + 1; k <= right; k++, j++) 
        R.push_back(arr[k]);


    i = 0; j = 0; k = left;

    int l_num = 0;
    int r_num = 0;

    while (i < L.get_size() && j < R.get_size())
    {
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
            l_num++;
            r_num = 0;
        }
        else
        {
            arr[k++] = R[j++];
            r_num++;
            l_num = 0;
        }

        if (l_num == 7)
            galloping(arr, L, R, i, j, k, 1);
        else if (r_num == 7)
            galloping(arr, L, R, i, j, k, 2);
    }

    while (i < L.get_size()) 
        arr[k++] = L[i++];

    while (j < R.get_size()) 
        arr[k++] = R[j++];
    
}

void timsort(DynamicArray <int>& arr)
{
    int size = arr.get_size();
    int minrun = f_minrun(size);
    int l = 0, r = 0;
    int begin, mid, finish;
    stack<couple> res;
    couple x, y, z;

    while (l < size) 
    {
        r = l;

        //расположение по возрастанию
        while ((arr[r] <= arr[r + 1]) && (r + 1 < size)) 
            r++;
        
        //расположение по убыванию
        if ((arr[r] > arr[r + 1]) && (r + 1 < size)) 
        {
            while ((arr[r] > arr[r + 1]) && (r + 1 < size)) 
                r++;
            
            begin = l;
            finish = r;

            while (begin < finish) 
            {
                swap(arr[begin], arr[finish]);
                begin++;
                finish--;
            }
        }

        if (r - l + 1 < minrun) 
        {
            (l + minrun - 1 < size) ? (r = l + minrun - 1) : (r = size - 1);
        }

        insertion_sort(arr, l, r);
        res.push({ l, r - l + 1 });
        l = r + 1;
    }
    
    if (64 <= arr.get_size())
    {
        while (res.size() > 1)
        {
            x = res.top(); res.pop();
            y = res.top(); res.pop();

            if (res.size() == 0)
            {
                mid = y.start + y.size - 1;
                finish = x.start + x.size - 1;
                merge(arr, y.start, mid, finish);
                res.push({ y.start, y.size + x.size });
            }
            else
            {
                z = res.top(); res.pop();

                if (z.size <= y.size + x.size || y.size <= x.size)
                {
                    if (z.size >= x.size)
                    {
                        mid = z.start + z.size - 1;
                        finish = y.start + y.size - 1;
                        merge(arr, z.start, mid, finish); // z + y
                        res.push({ z.start, z.size + y.size });
                        res.push(x);
                    }
                    else
                    {
                        mid = y.start + y.size - 1;
                        finish = x.start + x.size - 1;
                        merge(arr, y.start, mid, finish); // y + x
                        res.push({ y.start, y.size + x.size });
                        res.push(z);
                    }
                }
                
            }
        }
    }
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
    DynamicArray<int> curr;
    DynamicArray<int> sort_curr;
    int curr_size = 0;

    while (1)
    {
        system("cls");
        int ch = 0;
        cout << "Меню:" << endl;
        cout << "1. Размер массива = " << curr_size << endl;
        cout << "2. Сгенерировать массив и отсортировать" << endl;
        cout << "3. Выход из программы" << endl;
        ch = input(ch, 3);
        switch (ch)
        {
        case 1:
        {
            if (curr_size != 0)
            {
                DynamicArray<int> new_curr;
                curr = new_curr;
                DynamicArray<int> new_sort_curr;
                sort_curr = new_sort_curr;
            }
            bool flag = false;
            while (!flag)
            {
                cout << "Введите размер массива: ";
                if (!(cin >> curr_size) || curr_size < 2 || cin.peek() != '\n')
                {
                    if (curr_size >= 0 && curr_size < 2)
                        cout << "Нет смысла сортировать!" << endl;
                    else
                        cout << "Некорректный ввод! Попробуйте еще раз!" << endl;
                    cin.clear();
                    flag = false;
                    while (cin.get() != '\n');
                }
                else
                    flag = true;
            }
            flag = false;
            break;
        }
        case 2:
        {
            if (curr_size == 0)
                cout << "Массив пуст!" << endl;
            else
            {
                srand(static_cast<unsigned int>(time(0)));
                for (int i = 0; i < curr_size; i++)
                {
                    curr.push_back(rand() % 2001 - 1000);
                    sort_curr.push_back(curr[i]);
                }

                cout << "\nСгенерированный массив - 1 столбец\nОтсортированный массив - 2 столбец\n\n";

                timsort(sort_curr);

               /* if (is_sorted(sort_curr)) 
                    cout << endl << "true" << endl;
                else if (!is_sorted(sort_curr))
                    cout << "false" << endl;*/

                cout << "1\t2\t" << "индекс" << "\n\n";
                for (int i = 0; i < curr_size; i++)
                {
                    cout << curr[i] << "\t" << sort_curr[i] << "\t" << i << "\n";
                }
                cout << endl;
            }

            system("pause");
            break;
        }
        case 3:
        {
            return 0;
            break;
        }
        }
    }
}

