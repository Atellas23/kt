#include "commonlib.h"
using namespace std;

/** VARIABLES GLOBALS. */
ss colonia;
ss monitors;
ss serveis;
int n_nens;
int n_muni;
int n_serv;
KT kt(10);


int main(int argc, char *argv[]) {
  if (argc < 3) error();
  else {
    string temp;
    ifstream persones;
    persones.open(argv[1]);
    while (getline(persones, temp) and temp != "----") colonia.insert(temp);
    n_nens = colonia.size();
    ss::iterator it;
    for (it=colonia.begin(); it!=colonia.end(); ++it) cout << *it << endl;
    while (getline(persones, temp) and temp != "end") monitors.insert(temp);
    n_muni = monitors.size();
    for (it=monitors.begin(); it!=monitors.end(); ++it) cout << *it << endl;
    persones.close();
    ifstream llistaServeis;
    llistaServeis.open(argv[2]);
    temp = "";
    while (getline(llistaServeis, temp) and temp != "end") serveis.insert(temp);
    n_serv = serveis.size();
    /** Llegim la colonia i els serveis a repartir. */
  }
}
