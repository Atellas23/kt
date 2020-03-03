#include "lib/header.hh"
using namespace std;

int main(int argc, char **argv)
{

    if (argc != 3)
    {
        cout << "Ei, error!\n";
        string name(argv[0]);
        cout << "La sintaxi es " + name + " data.csv\n serveis.csv";
        exit(0);
    }

    // colonia C = read_csv(argv[1]);
    colonia C = test_read_csv(argv[1]);
    // vector<llista> left;
    vector<bool> served_yesterday(C.gent.size(), false);

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

    /* llista serveis_nens = {"parar_taula", "exteriors+pregaria", "interior",
                                   "lavabos", "desparar_taula", "plats+peroles"};
    llista serveis_monitors = serveis_nens;
    serveis_monitors.push_back("berenar");
    serveis_monitors.push_back("imaginaria"); */
    map<string, int> cap;
    llista serveis_nens = read_serveis(argv[2], cap);

    vector<day> kt;
    grup &working_class = C.gent;
    vector<double> prob(working_class.size(), 1);
    map<int, map<string, bool>> has_done;
    int n = C.gent.size();
    has_done_init(has_done, n, serveis_nens);
    for (int dia = 0; dia < 10; ++dia)
    {
        day d;
        for (auto &s : serveis_nens)
        {
            grup temp;
            default_random_engine gen;
            discrete_distribution<int> d1(prob.begin(), prob.end()); // triem un xaval random,
                                                                     // amb probabilitat mes
                                                                     // gran com mes dies fa
                                                                     // que no fa cap servei.
            while ((int)temp.size() < cap[s])
            { // potencial de cada servei es cap[s]
                int random_nen = d1(gen);
                // uniform_int_distribution<int> d2(0, 6);
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
        for (int i = 0; i < n; ++i)
        {
            if (not working_class[i].working_today)
                prob[working_class[i]._id] *= 2;
        }
        // push_back del dia 1
        // reverse
        // push_back del dia 10
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
