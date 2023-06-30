#!/bin/bash

#Utilizandp sed, hacer un script que, dado el fichero de texto peliculas.txt elimine las lineas
#vacias y los subrayados, extraiga el titulo de la pelicula y lo situe en la una linea
#independiente como "Titulo: xxx", la fecha de estreno como "|-> Fecha estreno: xxx",formatee
#el director y el reparto como "|-> Director: xxx" y |-> Reparto: xxx" y la duracion
#como "|-> Duracion: xxx". El script recibira el nombre del fichero por la linea de comandos.

#if [ $# -ne 1 ]
#then 
#	echo "Error en la invocacion del programa. $0 peliculas.txt"
#	exit 1
#fi

#SED: Como grep (busca) pero permite hacer cambios en las lineas coincidentes
	#opcion -r para usar EREs en vez de BREs
	#opcion -n no imprime las lineas a no ser que se especifiquen con bandera 'p'
	#opcion -e 'comando': ejecutar en comando o comando especificados
	#s/patron/reemplazo/[banderas]
	#/p bandera p: forzamos a imprimir la linea (solo se usa si se usa antes opcion -n)
	
#El primer comando imprime tiene la bandera 'p' Todo lo que no empieze por dirigido, reparto ,=,0-9 o paréntesis ( o sea, imprime el título de la pelicula)

while read linea 
do
	echo $linea | sed -r -e 's/(^[^\ (Dirigido)(Reparto)()0-9=])/\nTitulo: \1/'

done < peliculas.txt
