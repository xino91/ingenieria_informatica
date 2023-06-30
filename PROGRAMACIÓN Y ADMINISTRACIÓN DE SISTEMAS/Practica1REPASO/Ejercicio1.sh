#!/bin/bash

#Ejercicio1.c Cuenta los ficheros con extension .c y .h en un directorio pasado como arguento
#	A continuacion muestrelos ordenador segun el numero de caracteres indica el numero de lineas y caracteres que tienen

echo -e "\n"

if [ $# -ne 1 ];
then 
	echo "ERROR en la invocacion, debe introducir $0 <directorio a buscar>"
	echo -e "\n"
	exit 1
fi


contador_c=0
contador_h=0

#Buscamos en el directorio los .c 
for x in $(find $1 -name "*.c")
do 
	let contador_c=$contador_c+1;  #No dejar espacion despues de = 
done

#Buscamos en el directorio los .h
for x in $(find $1 -name "*.h")
do
	let contador_h=$contador_h+1;
done

#Mostramos resultados
echo "Tenemos $contador_c ficheros con extension .c y $contador_h con extension .h"
echo -e "\n"


#Buscamos los ficheros y contamos sus lineas y caracteres, e imprimos ordenados
for x in $(find $1 -name "*.c" && find $1 -name "*.h")
do
	echo "El fichero $x tiene $(cat $x | wc -l) lineas y $(cat $x | wc -m) palabras"
done | sort -nr -k8

echo -e "\n"
	


	
