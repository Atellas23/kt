// Creem una ruta pel joc de sobres
#include "sobres.hpp"
using namespace std;

int main() {
    // llegeixo noms de les localitzacions
    vector<string> places;
    for (int i = 0; i < NUM_LOCALITZACIONS; ++i) places.push_back("lloc" + to_string(i + 1));
    random_shuffle(places.begin(), places.end());
    vector<vector<string>> circuit_correcte(NUM_EQUIPS);
    map<pair<int, string>, string> incorrecte;
    cout << "pre-for" << endl;
    for (int equip = 0; equip < NUM_EQUIPS; ++equip) {
        cout << "podre entrar una string en un vector<string>?" << endl;
        circuit_correcte[equip].push_back(places[equip]);  // localització inicial
        cout << "SI" << endl;
        for (int seguent = 1; seguent < NUM_EQUIPS; ++seguent) {
            incorrecte[{equip, circuit_correcte[equip].back()}] = places[(equip - seguent) < 0 ? NUM_LOCALITZACIONS + equip - seguent : equip - seguent];
            circuit_correcte[equip].push_back(places[equip + seguent]);
        }
    }
    cout << "post-for" << endl;

    ofstream output;
    output.open("circuit.txt");
    for (int equip = 0; equip < NUM_EQUIPS; ++equip) {
        output << "EQUIP #" << equip + 1 << endl;
        for (int lloc = 0; lloc < (int)circuit_correcte[equip].size(); ++lloc) {
            output << "Localització correcta #" << lloc + 1 << ": " << circuit_correcte[equip][lloc] << endl;
            output << "\tSi s'equivoquen, van a la localització " << incorrecte[{equip, circuit_correcte[equip][lloc]}] << endl;
        }
        output << string(10, '-') << endl
               << endl;
    }
}