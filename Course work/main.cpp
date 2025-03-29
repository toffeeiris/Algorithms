#include "Application.h"

int main()
{
    setlocale(LC_ALL, "Rus");
    Application a(4, "matrix.txt");
    if (a.file_reading()) 
    {
        a.run();
    }
}
