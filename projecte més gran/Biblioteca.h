#ifndef BIBL_H
#define BIBL_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

/** Quantitat de dies. Únicament per finalitats de desenvolupament. */
#define days 10

/** Llista de serveis. */
#define servei0 0
#define servei1 1
#define servei2 2
#define servei3 3
#define servei4 4
#define servei5 5

/** Cosa útil. */
#define espai "    "


/** Quantitat de serveis, es pot canviar. */
/*int n_serv;*/

/** Funcions del programa. */
void help();
void error();
void hurray();

#endif /* BIBL_H */
