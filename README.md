# Programa de repartiment de serveis

Aquest programa genera, donada una llista de nens i serveis, un repartiment dels serveis de colònies durant els 10 dies.

## Pre-requisits

### Windows

Caldria tenir instal·lats `make` i `pandoc`, dues utilitats <u>**imprescindibles**</u> per poder fer anar el programa.

#### `make`

Si es té [Chocolatey](https://chocolatey.org/install) instal·lat, la instal·lació es redueix a executar en una línia de comandes la següent instrucció:

```shell
choco install make
```

Si no es té instal·lat, cal seguir [aquestes instruccions](http://gnuwin32.sourceforge.net/packages/make.htm).

#### `pandoc`

Per instal·lar-lo, cal seguir les instruccions [d'aquest link](https://pandoc.org/installing.html).

### Linux / MacOS

`make` ja hauria de venir instal·lat. Per instal·lar `pandoc`, s'ha d'executar la següent instrucció en un terminal:

```shell
sudo apt-get install pandoc
```

## Tutorial for dummies

Aquí explicaré com fer funcionar el programa pel públic general.

**Pas 1:** executar l'aplicació `config.exe`. Aquesta, en principi, hauria de crear un altre executable, anomenat `serveis.exe`.

**Pas 2:** posar a la carpeta `data` l'arxiu `.csv` amb la llista de nens i l'arxiu amb la llista de serveis. Si no es posa la llista de serveis, el programa repartirà els nens amb el llistat per defecte, que està especificat més avall.

## Paràmetres d'entrada

### Paràmetres per defecte

## Format de sortida

## Explicació del funcionament en profunditat

### Restriccions

```shell
pandoc result.md -o Serveis.html
```

## Suggerències