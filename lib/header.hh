#ifndef HDR_H
#define HDR_H

#include <iostream>
#include <algorithm>
#include <map>
#include <random>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
using llista = vector<string>;

enum option
{
    nens,
    monitors,
    tots
};

struct persona
{
    int _id;
    bool monitor;
    string nom;
    bool working_today;
};
using grup = vector<persona>;

struct servei
{
    grup persones;
    string nom;
};

struct colonia
{
    grup gent;
    int n_monitors;
    int n_nens;
    void print(option a);
};

struct table
{
    llista header;
    vector<llista> contents;
};

using day = vector<servei>;

colonia read_gent(const string &file_path);
llista read_serveis(const string &file_path, map<string, int> &cap);
colonia test_read_csv(const string &file_path);
bool format(const vector<day> &c, const llista &serveis);
void has_done_init(map<int, map<string, bool>> &m, int n_nens, llista &serveis);
table format2(const vector<day> &c, const llista &serveis);
bool md_format(table &t);
double soroll();

#endif // !1 HDR_H