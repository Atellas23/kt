#ifndef CMN_H
#define CMN_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
using namespace std;

typedef set<string> ss;

/** DECLARACIÓ DE LA CLASSE SERVEI. */
class servei {
private:
  ss munis;
  ss nens;
  string name;
public:
  servei(string name);
  virtual ~servei();

  ss getMunis();
  ss getNens();
  ss getName();
};

typedef set<servei> dia;
typedef vector<dia> KT;

void error();


#endif /* CMN_H */

//commonlib.o: commonlib.cc commonlib.h
