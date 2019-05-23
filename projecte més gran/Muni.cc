#include "Muni.h"
using namespace std;

Muni::Muni(string nom, int q) {
  name = nom;
  hasDone = vector<bool>(q, false);
}

string Muni::getName() {
  return name;
}

bool Muni::haFet(int s) {
  return hasDone[s];
}

Muni::~Muni() { }
