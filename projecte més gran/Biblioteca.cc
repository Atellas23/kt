#include "Biblioteca.h"

using namespace std;

string bolder(string& s) {
  string aux = "\e[1m" + s + "\e[0m";
  return aux;
}

void help() {
  string S = "Serveis";
  string E = "Entrada:";
  string F = "Sobre el format:";
/** Descripció de la funció; */
  cout << bolder(S) << ':' << espai << "Aquest programa reparteix una colònia"
  << " i el seu equip de monitors en els diferents serveis que "
  << "s'han de fer en una casa de colònies" << endl << endl;
/** Entrada; */
  cout << bolder(E) << endl;
  cout << espai << "argument 1:" << espai << "nom del fitxer amb la llista de nens i monitors."
  << endl << "S'ha de posar un fitxer 'serveis.txt' a la mateixa carpeta on està el programa, amb un servei per línia i acabat" << endl
  << " per la paraula clau 'end'." << endl << endl;
/** Sobre el format; */
  cout << bolder(F) << endl << "A la llista, els nens i els monitors han d'estar"
  << " separats per '----', i la llista ha d'acabar amb la paraula clau 'end'." << endl;
}

void error() {
  cerr << "Si no saps com va aquest programa, " <<
  "tira './serveis.exe help' i tindràs més instruccions." << endl;
  exit(-1);
}

void hurray() {
  cout << "everything's fine!" << endl;
}
