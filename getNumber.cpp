#include "ltn0108Project3_header.h"
int getNumber()
{
    ifstream fin("student.dat");
    if (!fin.is_open())
    {
        cout << "File error." << endl;
        exit(1);
    }

    int count = 0;
    string line;
    while (getline(fin, line))
    {
        // Only count if line is not empty and not garbage
        if (!line.empty())
            ++count;
    }

    fin.close();
    
    cout << "Number of students = " << count << endl;
    return count;
}
