#!/bin/bash

#Dos parametros ruta, y tamaño en bytes, si solo se pasa la ruta recorrer todo el directorio, si pasamos ruta y tamaño recorrer solo la carpeta pasada, y mostrar solo los ficheros con el tamaño mayor al pasado

if [ $# -lt 1 ] || [ $# -gt 3 ];
then 
	echo "ERROR; debe pasar dos argumentos ruta y tamaño o si lo desea solo pasar la ruta"
	
fi

#Dos argumentos
if [ $# -eq 2 ];
then 
	tam=$2
	
	for x in $(find $1 -maxdepth 1 -size +"$tam"c)
	do
	 	filename=$(stat -c "%n" $x)
		nombre=$(basename $x)
		let longitudusuario=$(stat -c "%U" $x | wc -m)-1
		grupoId=$(stat -c "%g" $x)
		tamano=$(stat -c "%s" $x)
		permisos=$(stat -c "%A" $x)

		echo "$filename; $nombre; $longitudusuario; $grupoId; $tamano; $permisos; $ejecutable"
		
	done | sort -n -k5 -t ";"
	 
fi

