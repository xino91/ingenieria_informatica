#!/bin/bash

#ejercicio1) Desarrollar un script que reciba un único argumento que será un directorio. 
#En primer lugar, contar cuantos ficheros hay con extensin.c y cuantos con extension.h
#Además, el script debe mostar la lista de ficheros con extencion .c o .h contenidos en ese
#directorio, ordenados según el numero de caracteres de cada fichero (de mayor a menor) e 
#indicar también en el listador el numero de lineas y de caracteres.

echo -e "\n"

#-----------------------------------------------------
#	CONTROL DE ARGUMENTOS
#-----------------------------------------------------

if [ $# -ne 1 ];
then
	echo "ERROR: Debe introducir $0 <nombre_directorio>"
	echo -e "\n"
	exit 1
fi


#------------------------------------------------------
#	CONTAJE DE ARCHIVOS
#------------------------------------------------------

contador_c=0;
contador_h=0;

#Buscamos los archivos .c mediante un for y vamos incrementano contador_c cada vez
#cada vez que encontremos uno
for x in $(find $1 -name "*.c")
do
	let contador_c=$contador_c+1;
done

#Buscamos los archivos .h mediante un for y vamos incrementando contador_h cada vez
#que que encontremos uno
for x in $(find $1 -name "*.h")
do
	let contador_h=$contador_h+1;
done

#Imprimimos la cantidad de archivos .c y .h por pantalla
echo "Tenemos $contador_c ficheros con extensión .c y $contador_h con extensión .h"
echo -e "\n"


#-----------------------------------------------------------
#	IMPRESIÓN DE ARCHIVOS
#----------------------------------------------------------

#Buscamos los archivos con extensión .c o .h
for x in $(find $1 -name "*.c" && find -name "*.h")
do
	echo "El fichero $x tiene $(cat $x | wc -l) lineas y $(cat $x |wc -m) caracteres y $(cat $x | wc -w) palabras"
	
	#sort -n  --> Este parámetro nos sirve para ordenar los campos numericos por su valor numerico
	#     -r  --> Nos permite una ordenacion inversa, ordena de mayor a menor 
	#            (-n para ordenar de menor a mayor)
	#-k8      --> Le indica a sort que ordene según lo introducido en la columna 8
done | sort -nr -k8

echo -e "\n"








