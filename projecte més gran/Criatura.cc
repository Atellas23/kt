#include "Criatura.h"
using namespace std;

Criatura::Criatura(string nom, int q) {
  name = nom;
  hasDone = vector<bool>(q, false);
}

bool Criatura::haFet(int s) {
  return hasDone[s];
}

string Criatura::getName() {
  return name;
}

void Criatura::setName(string nom) {
  this->name = nom;
}

void Criatura::wrkdTdy(int s) {
  hasDone[s] = true;
  workedYesterday = true;
}

vector<bool> Criatura::getDone() {
  return hasDone;
}

Criatura::~Criatura() { }
