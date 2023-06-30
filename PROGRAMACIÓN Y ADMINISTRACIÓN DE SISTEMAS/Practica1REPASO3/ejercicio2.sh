#!/bin/bash

# 2) Crear un script que reciba como argumento un parámetro que será un directorio
# y un segundo argumento que será un número (número en bytes). El script debe buscar
# todos los ficheros que estén alojados en la carpeta que se pasa como primer 
# argumento, cuyo tamaño en total en bytes sea mayor o igual que el número pasado
# como segundo argumento. Si no se especifica un segundo argumento, el script deberá
# mostrar todos los ficheros (es decir, como si el tamaño fuese 0). Para cada fichero
# -El nombre del fichero(sin la ruta)
# -El número de caracteres del nombre del usuario propietario
# -La fecha de creacion(legibe) y el último acceso al fichero(segundo UNIX)
# -Tamaño en bytes y número de bloques que ocupa en memoria
# -La cadena de permisos del fichero
# -Un 1 si el fichero es ejecutable o un 0 si no lo es.
# -Todos los campos se separarán por el caracter ";" y la salida deberá ordenarse
# númericamente por tamaño (de menor a mayor).

if [ $# -lt 1 ] || [ $# -ge 3 ];
then 
	echo "ERROR en la linea dea arguemntos, debe pasar un directorio (obligatorio), y un tamaño en bytes si lo desea (opcional)"
	echo -e "\n"
	exit 1
	
else	
	#Si recibe solo un parametro tam vale 0 si recibe dos parametros sera $2
	if [ $# -eq 1 ];
	then
		tam=0	
	else
		tam=$2
	fi
fi

#Variable para saber si ya se ha imprimido los nombres de las columnas (variables)
intro=0


for x in $(find $1 -size "$tam"c -or -size +"$tam"c)
do

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
	
	#almacenamos los datos de los ficheros en variables 
	nombre=$(basename $x)
	
	#wc -m --> Muestra la cantidad de caracteres de la cadena que se le pasa. Mediante tuberías,le pasamos el nombre del propietario. Como también cuenta el \n, debemos restarle 1.
	#let --> guarda el valor total de la resta en longitudUsuario, así permitimos que imprima 8 en lugar de 9-1.
	#stat -c " " $x --> Muestra del fichero $x (consultar man):
	#"%U"  --> Nombre del usuario propietario
	let longitudUsuario=$(stat -c "%U" $x | wc -m)-1
	
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
	
echo -e "\n"
	
	
	
	
