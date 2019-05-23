#ifndef CRT_H
#define CRT_H

#include "Biblioteca.h"
using namespace std;

/** Classe Criatura; cada nen/a està representat per un objecte
    d'aquesta classe. */
class Criatura {
private:
  string name;
  vector<bool> hasDone;
  bool workedYesterday;
public:
  Criatura(string nom, int q);
  virtual ~Criatura();

  string getName();
  void setName(string nom);
  void wrkdTdy(int s);
  bool haFet(int s);
  vector<bool> getDone();
};

#endif /* CRT_H */
