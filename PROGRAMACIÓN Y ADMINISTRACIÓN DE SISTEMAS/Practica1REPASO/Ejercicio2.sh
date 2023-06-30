#!/bin/bash

#Script que reciba como argumento un parámetro que será un directorio y un segundo argumento
#que será un número (número de bytes). El script debe buscar todos los fichero que estén alojados
#en la carpeta que se pasa como primer argumento, cuyo tamaño total en bytes sea mayor o igual
# que el numero pasado como segundo argumento. Si no se especifica un segundo argumento, el script
#deberá mostrar todos los ficheros (es decir, como si el tamaño fuese 0). Para cada fichero,
#habrá que mostrar.
#1. El nombre del fichero (sin la ruta).
#2. El número de caracteres del nombre del usuario propietario.
#3. La fecha de creación (legible) y del último acceso al fichero (segundos UNIX).
#4. Tamaño en bytes y número de bloques que ocupa en memoria.
#5. La cadena de permisos del fichero.
#6. Un 1 si el fichero es ejecutable o un 0 si no lo es.
#Todos los campos se separarán por el caracter ";" y la salida deberá ordenarse númericamente por 
#tamaño (de menor a mayor).

echo -e "\n"

#-----------------------------------------
#	CONTROL DE ARGUMENTOS
#-----------------------------------------

if [ $# -eq 0 ] || [ $# -ge 3 ];  #eq --> igual || -ge -->Mayor o igual
then
	echo "ERROR: Debe introducir $0 <nombre_directorio> y, si lo desea una cantidad en bytes"
	echo "\n"
	exit 1

	#Si solo ha introducido un parámetro (nombre del directorio), la cantidad en bytes será 0
	#y se deberán tener en cuenta todos los ficheros del directorio
	#Si se han introducido dos parámetros, el segundo será la cantidad en bytes y se tendrán en 
	#cuentan solo los ficheros cuyo tamañi sea igual o superior a esa cantidad de bytes.
	else 
		if [ $# -eq 1 ];
		then
			tam=0
		else
			tam=$2
		fi

		
#------------------------------------------
#	PROCESAMIENTO
#------------------------------------------

intro=0  #Variable para saber si ya se han imprimido los nombres de las columnas (variables)

#Buscamos los ficheros cuyo tamaño sea igual o superior al indicado. Escribiendo una c detrás de 
#la variable donde se guardará el número de bytes indicamos que este número se corresponderá 
#especificamente con bytes. Si no pusiéramos nada, el número indicado actuaría, por defecto, como
#cantidad de bloques.

for x in $(find $1 -size "$tam"c -or -size +"$tam"c)		#find [ruta] -user usuario, busca ficheros cuyo nombre usuario
do												#propietario sea "usuario"
	if [ "$intro" -eq 0 ];
	then
		echo -e "\n"
		echo "Nombre; LongitudUsuario; FechaModificacion; FechaAcceso; Tamaño; Bloques; Permisos; Ejecutable"	
		intro=1
	fi
		
	if [ -x $x ];  # -x  --> si es ejecutable
	then 
		ejecutable=1  #Imprimimos un 1 si lo es
	else
		ejecutable=0  #Imprimimos un 0 si no lo es 
	fi
	
	nombre=$(basename $x)   #basename --> Muestra solo el nombre (sin ruta)
	
	#wc -m --> Muestra la cantidad de caracteres de la cadena que se le pasa. Mediante tuberías,le pasamos el nombre del propietario. Como también cuenta el \n, debemos restarle 1.
	#let --> guarda el valor total de la resta en longitudUsuario, así permitimos que imprima 8 en lugar de 9-1.
	
	let longitudUsuario=$(stat -c "%U" $x | wc -m)-1
	
	#stat -c " " $x --> Muestra del fichero $x (consultar man):
	#"%U"  --> Nombre del usuario propietario
	
	fechaModificacion=$(stat -c "%y" $x)  #"%y" -->Ultima fecha modificacion
	fechaAcceso=$(stat -c "%x" $x)  	   #"%x" -->Ultima fecha de acceso
	tamano=$(stat -c "%s" $x)		   #"%s" -->tamaño en bytes
	nBloques=$(stat -c "%b" $x)		   #"%b" -->cantidad de bloques
	permisos=$(stat -c "%A" $x) 		   #"%A" -->Permisos
	
	echo "$nombre; $longitudUsuario; $fechaModificacion; $fechaAcceso; $tamano; $nBloques; $permisos; $ejecutable"
	
	#sort:
	#-n -->Ordena de menor a mayor
	#-k5 -->Indica que ordena segun lo introducido en el campo 5
	# -t ";" --> Indica que el caracter separador de las columnas es el punto y coma
	
done | sort -n -k5 -t ";"
fi
	
echo -e "\n"


	



