#!/bin/bash

#Utilizandp sed, hacer un script que, dado el fichero de texto peliculas.txt elimine las lineas
#vacias y los subrayados, extraiga el titulo de la pelicula y lo situe en la una linea
#independiente como "Titulo: xxx", la fecha de estreno como "|-> Fecha estreno: xxx",formatee
#el director y el reparto como "|-> Director: xxx" y |-> Reparto: xxx" y la duracion
#como "|-> Duracion: xxx". El script recibira el nombre del fichero por la linea de comandos. 

if [ $# != 1 ]
then
	echo "Numero de argumentos incorrecto"
	echo "Ejecuta ./ejercicio2.sh peliculas.txt"
	exit
fi 

sed -r -e '/^$/d' $1 | sed -r -e '/==*/d' | sed -r -e 's/Dirigida por/|-> Director:/' | sed -r -e 's/^(\(.*\))(.*)/|-> Fecha de estreno: \1/g' | sed -r -e 's/^Reparto:/|-> Reparto: /' | sed -r -e 's/([0-9].*n$)/|-> Duracion: \1/' | sed -r -e '/^(\ )/d' | sed -r -e 's/^(\¡*[A-Z].*)/Titulo: \1/'
