#!/bin/bash


#Crear un script que ejecute los comandos adecuados de grep que permitan realizar las 
#siguientes tareas sobre el fichero de ejemplo peliculas.txt

# 1) Mostrar aquellas lineas que contienen la duracion de la pelicula (unos o mas digitos al 
#principio de la linea, un espacio y la secuencia "min")
echo "*****************************************"
cat peliculas.txt | grep -E --colour '[0-9]+(hr) [0-9]+(min)'
echo "*****************************************"

# 2)Mostrar aquellas lineas que continen el pais de la pelicula (suponemos que siempre aparecera 
#rodeado de guiones p.ej. -Estados Unidos-"
echo "*****************************************"
cat peliculas.txt | grep -E --colour '\-(.*)\-'
echo "*****************************************"

# 3) Similar al ejercicio anterior, pero mostrar solo los paises(sin la linea  completa).
echo "*****************************************"
cat peliculas.txt | grep -E -o --colour '\-(.*)\-' | tr -d '-'
echo "*****************************************"

# 4) Contar cuantas peliculas son del 2016 y cuantas del 2017
echo "*****************************************"
c1=$(grep -E '2016' "peliculas.txt" | wc -l)
c2=$(grep -E '2017' "peliculas.txt" | wc -l)
echo "Hay $c1 peliculas de 2016 y $c2 del 2017"
echo "*****************************************"

# 5) Mostar todo el fichero pero sin lineas vacias
echo "*****************************************"
cat peliculas.txt | sed -r -e '/^$/d'
echo "*****************************************"

# 6) Mostrar aquellas lineas que empiezan por la letra E (haya o no espacion antes de la misma)
echo "*****************************************"
cat peliculas.txt | grep -E --colour '(^ *E)'
echo "*****************************************"

# 7) Mostrar aquellas lineas que contengan una letra 'd', 'l' o 't', una vocal, y la misma
#letra p.ej. "Universidad, "expectativas", "dedicarse"
echo "*****************************************"
cat peliculas.txt | grep -E --colour '(d|l|t)[aeiou]\1'
echo "*****************************************"

# 8) Todas aquellas lineas que tengan, en total, 8 vocales 'a' o mas (mayusculas o minisculas y #no necesariamente seguidas).
echo "*****************************************"
cat peliculas.txt | grep -E --colour '(.*a.*){8,}'
echo "*****************************************"

# 9) Mostrar aquellas lineas que terminan con tres puntos ("...") y no empiezan por espacio
#utilizando el operador repeticion \{...\} o {...}.
echo "*****************************************"
cat peliculas.txt | grep -E --colour '(\.{3,3})' |sed -r -e '/^\ /d'
echo "*****************************************"

# 10) Utilizar sed para mostar, entre comillas dobles, las vocales con tilde(MAYUSC o MINUSC)
echo "****************************************"
cat peliculas.txt | sed -r -e  's/([áéíóú])/"\1"/g'
echo "****************************************"

# s: sustituir una expresion por otra sobre las lineas seleccionadas
#sintaxis: s/patron/reemplazo/[banderas]


