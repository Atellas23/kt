#ifndef MUNI_H
#define MUNI_H

#include "Biblioteca.h"
using namespace std;

/** Classe Muni; cada monitor està representat per un objecte
    d'aquesta classe. */
class Muni {
private:
  string name;
  vector<bool> hasDone;
public:
  Muni(string nom, int q);
  virtual ~Muni();

  string getName();
  bool haFet(int s);
};

#endif /* MUNI_H */
