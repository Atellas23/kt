#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
using namespace std;

int NUM_LOCALITZACIONS = 17;
int NUM_EQUIPS = 9;

struct Tree {
    string name;
    Tree *correct;
    Tree *incorrect;
    Tree() : correct(nullptr), incorrect(nullptr), name("leaf_subtree") {}

    void insert_correct(string correcte) {
        if (correct == nullptr) {
            correct = new Tree;
            correct->set_name(correcte);
        } else
            correct->insert_correct(correcte);
    }

    void insert_incorrect(string incorrecte) {
        if (incorrect == nullptr) {
            incorrect = new Tree;
            incorrect->set_name(incorrecte);
        } else
            correct->insert_incorrect(incorrecte);
    }
    void set_name(string new_name) { name = new_name; }
};

using circuits = vector<Tree>;

void camins(circuits &res, string file = "") {
    vector<string> llocs;
    if (file == "") {
        cerr << "error: el fitxer de localitzacions està buit!" << endl;
        return;
    }
    ifstream input(file);
    if (not input.good()) {
        cerr << "error: el fitxer de localitzacions no és accessible." << endl;
    }
    string lloc;
    while (getline(input, lloc)) llocs.push_back(lloc);
    NUM_LOCALITZACIONS = llocs.size();

    random_shuffle(llocs.begin(), llocs.end());

    res = circuits(NUM_EQUIPS);

    for (int equip = 0; equip < NUM_EQUIPS; ++equip) {
        res[equip].set_name(llocs[equip]);
        for (int seguent = 1; seguent < NUM_EQUIPS; ++seguent) {
            res[equip].insert_correct(llocs[(equip + seguent) < NUM_LOCALITZACIONS ? equip + seguent : equip + seguent - NUM_LOCALITZACIONS]);
            res[equip].insert_incorrect(llocs[(equip - seguent) < 0 ? NUM_LOCALITZACIONS + equip - seguent : equip - seguent]);
        }
    }
}

void treeDriver() {
    cout << "Quants equips jugaran al joc de sobres? ";
    cin >> NUM_EQUIPS;
    string filename;
    cout << "Escriu el nom del fitxer de localitzacions: ";
    cin >> filename;
    vector<Tree> res(NUM_EQUIPS, Tree());
    camins(res, filename);
    ofstream output;
    output.open("circuits.txt");
    for (int equip = 0; equip < NUM_EQUIPS; ++equip) {
        // res[equip];
        output << "EQUIP #" << equip + 1 << ": comença a " << res[equip].name << endl;
        Tree *placeHolder = &res[equip];
        while (placeHolder->correct != nullptr) {
            output << "**L'equip està a la localització " << placeHolder->name << endl;
            output << "\t- Si encerten la pregunta, van a " << placeHolder->correct->name << endl;
            output << "\t- Si la fallen, van a " << placeHolder->incorrect->name << endl;
            placeHolder = placeHolder->correct;
            output << endl;
        }
        output << "La localització final de l'equip " << equip + 1 << " és " << placeHolder->name << endl;
        output << string(20, '-') << endl
               << endl;
        delete placeHolder;
    }
}