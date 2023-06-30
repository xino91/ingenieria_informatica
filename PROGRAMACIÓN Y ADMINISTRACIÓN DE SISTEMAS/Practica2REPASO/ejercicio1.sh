#!/bin/bash

#1) Mostrar aquellas lineas que contienen la duracion de la pelicula (uno o más dígitos 
# al principio de la linea, un espacio y la secuencia "min".

#if [ $# -ne 1 ] 
#then 
#	echo "Error en la invocación del programa. $0 Peliculas.txt"
#	exit 1
#fi

echo "1) Línea duración de la pelicula"

cat peliculas.txt | grep -E --colour '.+hr .+min'
#sleep 1
echo -e "\n"

echo "2) Línea país de la película: "

#cat peliculas.txt | grep -E --colour '\-(.*)-'
#sleep 1
echo -e "\n"

echo "3) Sólo el país de la pelicula"

#cat peliculas.txt | grep --colour -E -o '\-.*\-' | tr -d '-'
#sleep 1
echo -e "\n"

echo "4) Nº peliculas 2016 y del 2017"

peliculas2016=$(cat peliculas.txt | grep -E --colour '2016' |wc -l)
peliculas2017=$(cat peliculas.txt | grep -E --colour '2017' |wc -l)

#echo "Peliculas 2016 son: $peliculas2016"
#echo "Peliculas 2017 son: $peliculas2017"
#sleep 1 
echo -e "\n"

echo "5) Mostrar todo el fichero pero sin líneas vacías"

#cat peliculas.txt | sed '/^$/d'
#sleep 1
echo -e "\n"

echo "6) Imprimir lineas que empiezen por 'E' (sin tener en cuenta los espacios)"

#cat peliculas.txt | grep -E '(^ *)+E'
#sleep 1

echo "7) Mostrar aquellas líneas del fichero que contengan una letra 'd', 'l', o 't', una vocal, y la misma letra a continuación"

#cat peliculas.txt | grep -E --colour '([dlt])[aeiou]\1'
#sleep 1
echo -e "\n"


echo "8) Imprimir todas aquellas lineas que tengan, en total 8 vocales 'a' o mas (mayusculas o minusculas y no necesariamente seguidos"

#cat peliculas.txt | grep -E --colour '([Aa].*){8,}'
#sleep 1
echo "\n"

echo "9) Imprimir todas aquellas lienas que terminan con tres puntos ('...') y no empiezan por espacio utilizando el operador de repeticion \{...\} o {...}"

#cat peliculas.txt | grep -E --colour '\.{3,3}$' | sed -r -e '/^ /d'
#sleep	
echo "\n"

echo "10) Utilizar sed para mostrar, entre comillas dobles, las vocales con tilde (mayusculas o minisculas)"

#cat peliculas.txt | sed -r -e 's/([áéíóú])/"\1"/g'











