#!/bin/bash

#1) Desarrollar un script que reciba un unico argumento que será un directorio. En
# primer lugar, contar cuantos ficheros hay con extensión .c y cuantos con extensión
# .h. Además, el script debe mostrar la lista de ficheros con extension .c o .h 
# contenidos en ese directorio, ordenados según el número de caracteres cada fichero
# (de mayor a menor) e indicar también en el listado el numero de líneas y de
# caracteres.

echo -e "\n"

if [ $# -ne 1 ];
then
	echo "ERROR en la línea de argumentos, debe introducir un directorio."
	echo -e "/n"
fi

contador_c=0
contador_h=0

#Buscamos los ficheros con extension .c
for x in $(find $1 -name "*.c")
do
	let contador_c=$contador_c+1	#No dejar espacio despues del =
done 

for x in $(find $1 -name "*.h")
do
	let contador_h=$contador_h+1	#No dejar espacio despues del =
done 

#Imprimimos los contadores de los ficheros .c .h
echo "Tenemos $contador_c ficheros con extension .c y $contador_h con extension .h"
echo -e "\n"

#Imprimimos los ficheros por el numero de caracteres de cada uno (mayor a menor)
for x in $(find $1 -name "*.c" && find $1 -name "*.h")
do
	echo "El fichero $x tiene $(cat $x | wc -l) lineas y $(cat $x |wc -m) caracteres y $(cat $x | wc -w) palabras"
	
done | sort -nr -k8
#sort -n  --> Este parámetro nos sirve para ordenar los campos numericos por su valor numerico
	#     -r  --> Nos permite una ordenacion inversa, ordena de mayor a menor 
	#            (-n para ordenar de menor a mayor)
	#-k8      --> Le indica a sort que ordene según lo introducido en la columna 8

echo -e "\n"
