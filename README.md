# Programa de repartiment de serveis

Aquest programa genera, donada una llista de nens i serveis, un repartiment dels serveis de colònies durant els 10 dies.

## Pre-requisits

### Windows

Caldria tenir instal·lats `make`, `pandoc` i `gcc`, tres utilitats <u>**imprescindibles**</u> per poder fer anar el programa.

#### `make`

Si es té [Chocolatey](https://chocolatey.org/install) instal·lat, la instal·lació es redueix a executar en una terminal la següent instrucció:

```shell
choco install make
```

Si no es té instal·lat, cal seguir [aquestes instruccions](http://gnuwin32.sourceforge.net/packages/make.htm).

#### `pandoc`

Per instal·lar-lo, cal seguir les instruccions [d'aquest link](https://pandoc.org/installing.html).

#### `gcc`

És força important tenir instal·lat també el compilador de C/C++ per excel·lència, `gcc`. Per fer això, cal seguir [aquestes instruccions](https://gcc.gnu.org/install/binaries.html).

### Linux / MacOS

Per instal·lar els tres pre-requisits, s'han d'executar les següents instruccions en un terminal:

```shell
sudo apt-get install build-essential
sudo apt-get install pandoc
```

Un cop instal·lats els pre-requisits, s'ha de modificar `req.txt` i posar "sí" o "yes" al costat de cadascun.

## Tutorial for dummies

Aquí explicaré com fer funcionar el programa pel públic general.

**Pas 1:** Instal·lar els pre-requisits, explicats a l'apartat de sobre.

**Pas 2:** Fer doble clic a l'arxiu `setup.exe`. Això comprova que s'hagin instal·lat els pre-requisits, i després  compila el programa. També comprova que funcioni tot amb un llistat de nens per defecte.

**Pas 3:** Posar a la carpeta `data` l'arxiu `.csv` amb la llista de nens i **anomenar-lo `nens.csv`**, i l'arxiu amb la llista de serveis `serveis.dat`. Aquest últim ha de tenir un format concret, consulteu l'apartat de paràmetres d'entrada.

## Paràmetres d'entrada

- **Llista de nens:** la llista de nens ha de ser un arxiu `.csv`, fàcilment exportable des de MS Excel o Google Sheets. Bàsicament, és un format que separa les cel·les com

```.csv
cognom1,cognom2,nom
cognom1,cognom2,nom
		...
		...
		...
cognom1,cognom2,nom
```

en un arxiu de text que es pot editar amb qualsevol editor.

- **Llista de serveis:** la llista de serveis ha de ser

### Paràmetres per defecte

## Format de sortida

## Explicació del funcionament en profunditat

### Restriccions

#### Càlcul del hard-limit numèric
$80$.
```shell
pandoc result.md -o Serveis.html
```

## Suggerències

## To-Do / Futures actualitzacions

- Fer servir cues i/o piles per decidir més fàcil i rapidament quins nens poden fer feina avui i quins no.
- Establir el hard limit numèric de número de persones per no haver de repetir serveis.
- Fer la instal·lació més senzilla (remember the drama `linux_macOS_config.sh`)