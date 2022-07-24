#include "../lib/header.hh"
#define xivato cout << "hey!\n";
using namespace std;
string default_nensDB = "defaults/test2.csv";
string default_serveisDB = "defaults/serveis.dat";
bool defaults;

int main(int argc, char **argv)
{
    // cout << argc << endl;
    string serveisDB, nensDB;
    if (argc != 3)
    {
        if (argc == 2 and (string(argv[1]) == "defaults" or string(argv[1]) == "d"))
        {
            defaults = true;
            serveisDB = default_serveisDB;
            nensDB = default_nensDB;
        }
        else
        {
            cout << "Ei, error!\n";
            cout << "La sintaxi es " + string(argv[0]) + " data.csv serveis.csv";
            exit(0);
        }
    }
    else
    {
        defaults = false;
        nensDB = argv[1];
        serveisDB = argv[2];
    }
    // colonia C = read_csv(argv[1]);
    colonia C = {{}, 0, 0};
    xivato
    if (defaults)
        C = test_read_csv(nensDB);
    else
        C = read_gent(nensDB);
    cout << "gent llegida" << endl;
    // vector<llista> left;
    // vector<bool> served_yesterday(C.gent.size(), false);
    // xivato;

    /*
    nens:
        parar taula
        exterior + pregaria
        interior
        lavabos
        desparar taula
        plats i peroles
    monitors: nens +
        berenar
        imaginaria
    */

    map<string, int> cap;
    llista serveis_nens = read_serveis(serveisDB, cap);
    cout << "serveis llegits" << endl;

    vector<day> kt;
    grup &working_class = C.gent;
    vector<double> prob(working_class.size(), 1.0);
    map<int, map<string, bool>> has_done;
    int n = C.gent.size();
    has_done_init(has_done, n, serveis_nens);
    default_random_engine gen;
    for (int dia = 0; dia < 10; ++dia)
    {
        cout << "Fent el dia " << dia << endl;
        day d;
        for (auto &s : serveis_nens)
        {
            if ((s[0] <= '9' and s[0] >= '0') or s == "end") continue;
            cout << "Fent el servei " << s << endl;
            grup temp;
            discrete_distribution<int> d1(prob.begin(), prob.end()); // triem un xaval random,
                                                                     // amb probabilitat mes
                                                                     // gran com mes dies fa
                                                                     // que no fa cap servei.
            while ((int)temp.size() < cap[s])
            { // potencial de cada servei es cap[s]
                int random_nen = d1(gen);
                if (not working_class[random_nen].working_today and not has_done[random_nen][s])
                {
                    temp.push_back(working_class[random_nen]);
                    working_class[random_nen].working_today = true;
                    has_done[random_nen][s] = true;
                    prob[random_nen] = 1.0;
                }
            }
            d.push_back({temp, s});
        }
        for (auto &nen : working_class)
        {
            if (not nen.working_today)
            {
                prob[nen._id] *= 50 - dia * 3;
                // prob[nen._id] += soroll();
            }
        }
        // push_back del dia 1
        // reverse
        // push_back del dia 10
        // sort(d.begin(), d.end());
        for (auto &nen : working_class)
            nen.working_today = false;
        kt.push_back(d);
    }

    table no_volia_utilitzar_tanta_memoria_pero_buenu = format2(kt, serveis_nens);
    if (md_format(no_volia_utilitzar_tanta_memoria_pero_buenu))
        cout << "success!" << endl;
    // C.print(tots);
    // cout << (format(kt, serveis_nens) ? "success!" : "failure...") << endl;
}
