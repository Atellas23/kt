#include "header.hh"

int total = 0;
ifstream input;
string blue = "blue";
string red = "red";

colonia read_gent(const string &file_path)
{
    cout << "Entry point for read_gent" << endl;
    ifstream in(file_path);
    colonia a;
    int nens = 0, monitors = 0;
    grup temp_gent;
    while (not in.eof())
    {
        bool type;
        string type_string;
        // string cognom1, cognom2, nom;
        string cognom1, nom;
        in >> type;
        // char aux;
        // in >> aux;
        getline(in, type_string, ',');
        type = type_string == "1";
        getline(in, nom, ',');
        getline(in, cognom1);
        // getline(in, cognom2, ',');

        // cout << nom + " " + cognom1 + " " + cognom2 << endl;

        // persona temp = {total++, type, nom + " " + cognom1 + " " + cognom2, false};
        persona temp = {total++, type, nom + " " + cognom1, false};

        temp_gent.push_back(temp);

        type ? ++monitors : ++nens;

        // cout << "Nom: " << nom + ' ' + cognom1 + ' ' + cognom2 << endl;
        // cout << "Monitor: " << (type ? "True" : "False") << endl;
        // cout << endl;
    }
    in.close();
    colonia T = {temp_gent, monitors, nens};
    return T;
}

void colonia::print(option a)
{
    if (a != tots)
    {
        for (auto &p : gent)
        {
            if (p.monitor == (a == monitors))
                cout << (p.monitor ? "M\t" : "n\t") << p.nom << endl;
        }
    }
    else
    {
        for (auto &p : gent)
            cout << (p.monitor ? "M\t" : "n\t") << p.nom << endl;
    }
}

colonia test_read_csv(const string &file_path)
{
    ifstream in(file_path);
    colonia a;
    int nens = 0, monitors = 0;
    grup temp_gent;
    while (not in.eof())
    {
        string cognom1 = " ", nom;
        getline(in, nom, ',');
        getline(in, cognom1);

        // cout << nom + " " + cognom1 + " " + cognom2 << endl;

        persona temp = {total++, true, nom + " " + cognom1, false};

        temp_gent.push_back(temp);

        ++monitors;

        // cout << "Nom: " << nom + ' ' + cognom1 + ' ' + cognom2 << endl;
        // cout << "Monitor: " << (type ? "True" : "False") << endl;
        // cout << endl;
    }
    in.close();
    colonia T = {temp_gent, monitors, nens};
    return T;
}

/* 
   | Header      | Header      |
   | ----------- | ----------- |
   | Text        | Text        |
   | Text        | Text        |
 */

llista read_serveis(const string &file_path, map<string, int> &cap)
{
    llista res;
    ifstream in(file_path);
    string temp;
    while (getline(in, temp) and temp != "end")
        res.push_back(temp);
    for (int i = 0; i < (int)res.size(); ++i)
        in >> cap[res[i]];
    return res;
}

bool format(const vector<day> &c, const llista &serveis)
{
    ofstream out;
    string nl = "<br />";
    string rcolor = "</span>";
    string folder = "./tables/";
    for (int i = 0; i < (int)serveis.size(); ++i)
    {
        string filename = folder + serveis[i] + ".md";
        out.open(filename);
        out << "# " + serveis[i] << endl;
        out << "|";
        for (int j = 1; j <= 10; ++j)
            out << "Dia " + to_string(j) + "|";
        out << endl
            << "|";
        for (int j = 0; j < 10; ++j)
            out << "-----|";
        out << "|" << endl;
        for (auto &dia : c)
        {
            out << "|";
            for (auto &n : dia[i].persones)
                out << n.nom << nl;
        }
        out << "|";
        out.close();
    }
    return true;
}

void has_done_init(map<int, map<string, bool>> &m, int n_nens, llista &serveis)
{
    for (int i = 0; i < n_nens; ++i)
    {
        for (auto &s : serveis)
            m[i][s] = false;
    }
}

string lcolor(string &col)
{
    return "<span style='color:" + col + "'>";
}

table format2(const vector<day> &c, const llista &serveis)
{
    string nl = "<br />";
    string rcolor = "</span>";
    table res;
    for (int i = 0; i < 10; ++i)
    {
        res.header.push_back("Dia " + to_string(i + 1));
        llista avui;
        for (auto &s : c[i])
        {
            string temp_today_contents;
            temp_today_contents.append("**" + lcolor(blue) + s.nom + rcolor + "**" + nl);
            int count = 0;
            for (auto &p : s.persones)
                temp_today_contents.append(to_string(++count) + " " + p.nom + nl);
            avui.push_back(temp_today_contents);
        }
        res.contents.push_back(avui);
    }
    return res;
}

vector<llista> transpose(vector<llista> &m)
{
    // assuming the dimensions are constant through matrix elements...
    vector<llista> new_matrix(m[0].size(), llista(m.size()));
    for (int i = 0; i < (int)m[0].size(); ++i)
    {
        for (int j = 0; j < (int)m.size(); ++j)
            new_matrix[i][j] = m[j][i];
    }
    return new_matrix;
}

bool md_format(table &t)
{
    ofstream out("result.md");
    out << "# Serveis KT\n";
    out << "|";
    for (auto &s : t.header)
        out << s << "|";
    out << endl
        << "|";
    for (int i = 0; i < (int)t.header.size(); ++i)
        out << "----------|";
    t.contents = transpose(t.contents);
    for (auto &row : t.contents)
    {
        out << endl
            << "|";
        for (auto &text : row)
            out << text << "|";
    }
    out.close();
    return true;
}

double soroll()
{
    default_random_engine gen;
    normal_distribution<double> d(0.0, 0.5);
    return d(gen);
}