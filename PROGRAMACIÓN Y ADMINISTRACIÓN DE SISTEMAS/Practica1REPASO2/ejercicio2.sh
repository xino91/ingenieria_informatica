#!/bin/bash

#Ejercicio2: Script que reciba como argumento un parámetro que será un directorio y un segundo argumento
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


if [ $# -lt 1 ] || [ $# -gt 2 ];   #Quitar barras, porque falla????????????????
then 
	echo "ERROR: debe introducir $0 <directorio> <bytes>(opcional)"
	echo -e "\n" 
	exit 1
fi

intro=0

#Si hemos pasado un solo argumento 
if [ $# -eq 1 ];
then 
	tam=0
	
	
	for x in $(find $1 -size +"$tam"c)
	do
		if [ "$intro" -eq 0 ];
		then
			echo -e "\n"
			echo "Ruta; Nombre; LongitudUsuario; grupoID; Tamaño; Permisos; Ejecutable"
			intro=1
		fi
		
			if [ -x $x ];
			then
				ejecutable=1
			else
				ejecutable=0
			fi
			
		filename=$(stat -c "%n" $x)
		nombre=$(basename $x)
		let longitudusuario=$(stat -c "%U" $x | wc -m)-1
		grupoId=$(stat -c "%g" $x)
		tamano=$(stat -c "%s" $x)
		permisos=$(stat -c "%A" $x)

		echo "$filename; $nombre; $longitudusuario; $grupoId; $tamano; $permisos; $ejecutable"
		
	done | sort -n -k5 -t ";"
	
else	#Hemos pasado dos argumentos
	
	tam=$2
	
	for x in $(find -size "$tam"c -or -size +"$tam"c)
	do
		if [ "$intro" -eq 0 ];
		then
			echo -e "\n"
			echo "Ruta; Nombre; LongitudUsuario; grupoID; Tamaño; Permisos; Ejecutable"
			intro=1
		fi
		
			if [ -x $x ];
			then
				ejecutable=1
			else
				ejecutable=0
			fi
			
		filename=$(stat -c "%n" $x)
		nombre=$(basename $x)
		let longitudusuario=$(stat -c "%U" $x | wc -m)-1
		grupoId=$(stat -c "%g" $x)
		tamano=$(stat -c "%s" $x)
		permisos=$(stat -c "%A" $x)

		echo "$filename; $nombre; $longitudusuario; $grupoId; $tamano; $permisos; $ejecutable"
		
	done | sort -n -k5 -t ";" 
fi
	
	
	




