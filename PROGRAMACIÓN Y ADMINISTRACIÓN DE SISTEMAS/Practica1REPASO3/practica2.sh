#!/bin/bash

#Crear un script que ejecute los comandos adeucados de grep

echo "1)Mostrar aquellas lineas que contienen la duracion de la pelicula"
cat peliculas.txt | grep -E '[0-9]hr'

echo -e "\n"
echo "2)Mostrar aquellas lineas que continen el pais de la pelicula con guiones"
cat peliculas.txt | grep -E '\-*-'

echo -e "\n"
echo "3)Igual al ejercicio anterior pero mostrar solo los paises"
cat peliculas.txt | grep -E -o '\-.*\-' | tr -d "-"

echo -e "\n" 
echo "4)Contar cuantas peliculas son del 2016 y cuantas del 2017"
c16=0
c17=0
c16=$(cat peliculas.txt | grep -E '2016' | wc -l)
c17=$(cat peliculas.txt | grep -E '2017' | wc -l)

echo "Peliculas 2016 son: $c16"
echo "Peliculas 2017 son: $c17"
echo -e "\n"

echo "5)Mostrar todo el fichero pero sin lineas vacias"
cat peliculas.txt | grep -E -v '^$'

echo -e "\n" 
echo "6)Mostrar aquellas lineas que empiezan por la letra E (haya o no espacios ante ella"
cat peliculas.txt | grep -E '(^ *)+E'

echo -e "\n" 
echo "7)Lineas que contienen d,l o t, una vocal y la misma letra"  
cat peliculas.txt | grep -E --colour '([dlt])[aeiou]\1'

echo -e "\n"
echo "8)Lineas que contienen ocho aes o mas"
cat peliculas.txt | grep -E '([Aa].*){8,}'

echo -e "\n"
echo "9)Lineas que terminan con tres puntos y no empiezan por espacio"
cat peliculas.txt | grep -E --colour '\.{3,3}$' | sed -r -e '/^ /d'

echo -e "\n"
echo "10)Mostrar entre comillas las vocales con tilde"
cat peliculas.txt | sed -r -e 's/([áéíóúÁ])/"\1"/g'












