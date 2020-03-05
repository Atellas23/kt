#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream checker("req.txt");
    string buf1, buf2;
    getline(checker, buf1);
    bool can = true;
    if (buf1 != "REQUIREMENTS:")
    {
        cout << "Error!\nHas modificat el format de l'arxiu de requeriments!" << endl;
        ofstream error_corrector("req.txt");
        error_corrector << "REQUIREMENTS:\nmake no\ngcc no\npandoc no";
        error_corrector.close();
        exit(0);
    }
    for (int i = 0; i < 3; ++i)
    {
        checker >> buf1 >> buf2;
        if (buf2 == "no")
        {
            cout << "Falta instal.lar " + buf1 << endl;
            can = false;
        }
    }
    // assured that make is installed, we go on.
    if (can)
        system("make");
    else
        cout << "Comprova el README" << endl;
    checker.close();
}