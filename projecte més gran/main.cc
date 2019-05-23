#include "Criatura.h"
#include "Muni.h"
using namespace std;

/*
struct servei {
  string name;
  vector<Criatura> nins;
  vector<Muni> mns;
};

typedef vector<servei> vs;
typedef vector<vs> vvs;

vvs Serveis(days, vs(n_serv));
*/

vector<Criatura> colonia;
int n_nens;
vector<Muni> monitors;
int n_muni;
int n_serv;

void write_everything();
void setServeis();
void reparteix();

int main(int argc, char *argv[]) {
  if (argc < 2) error();
  string s(argv[1]);
  if (s == "help") help();
  else {
    setServeis();
    /*n_nens = stoi(string(argv[2]));
    n_muni = stoi(string(argv[4]));*/

    ifstream llista;
    string temp;

    /** Llegim la llista de nens. */
    llista.open(argv[1]);
    while (getline(llista, temp) and temp != "----") {
      Criatura personeta(temp, n_serv);
      colonia.push_back(personeta);
    }
    n_nens = colonia.size();
    while (getline(llista, temp) and temp != "end") {
      Muni persona(temp, n_serv);
      monitors.push_back(persona);
    }
    n_muni = monitors.size();
    llista.close();
    write_everything();
  }
  hurray();
}

void write_everything() {
  cout << "Colònia:" << endl;
  for (int i = 0; i < n_nens; ++i) cout << espai << colonia[i].getName() << endl;
  cout << "Monitors:" << endl;
  for (int i = 0; i < n_muni; ++i) cout << espai << monitors[i].getName() << endl;
}

void reparteix() {

}

void setServeis() {
  ifstream input;
  input.open("serveis.txt");
  if (not input.good()) error();
  string serv;
  vector<string> serveis;
  while (getline(input, serv) and serv != "end") serveis.push_back(serv);
  n_serv = serveis.size();
  input.close();
}
