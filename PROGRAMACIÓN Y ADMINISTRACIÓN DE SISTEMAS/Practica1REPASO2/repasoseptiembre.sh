#!/bin/bash

#Cuando pasemos dos parametros, el primero será una ruta y el segundo un tamaño en bytes , debemos imprimir por pantalla datos con el comando stat de todos los ficheros con tamaño superior al pasado, no podrá entrar en las subcarpetas. Si pasamos solo un parametro deberá hacer lo mismo de la carpeta actual, entrando a todas las sucarpetas. Al principio de cada linea deberá mostrar "tenemos x archivos leidos"
if [ $# -lt 1 ] || [ $# -gt 2 ];
then
	echo "ERROR en al pasar los parámetros"
	echo -e "\n"
	exit 1
fi

intro=0

#Dos parametros
if [ $# -eq 2 ];
then 
	if [ "$intro" -eq 0 ];
	then 
		echo "Fichero; Nombre; LongitudUsuario; Tamano; Fecha; UsuarioID; GrupoID; CadenaPermisos; Ejecutable"
	fi
		
		for x in $(find $1 -maxdepth 1 -type f -size +"$2"c)
		do
			if [ -x $x ]
			then 
				ejecutable=1
			else
				ejecutable=0
			fi
			
			fichero=$(stat -c "%n" $x)
			nombre=$(basename $x)
			let longitud=$(stat -c "%U" $x | wc -m)-1
			tamano=$(stat -c "%s" $x)
			seg=$(stat -c "%X" $x)
			usuarioID=$(stat -c "%u" $x)
			grupoID=$(stat -c "%g" $x)
			permisos=$(stat -c "%A" $x)
			extension=$(basename $x | cut -d "." -f 2)
			
			echo "$fichero; $nombre; $longitud; $tamano; $seg; $usuarioID; $grupoID; $permisos; $ejecutable; $extension"
			
		done | sort -k2 -t "-"
fi

if [ $# -eq 1 ];
then
	if [ "$intro" -eq 0 ];
	then 
		echo "Fichero; Nombre; LongitudUsuario; Tamano; Fecha; UsuarioID; GrupoID; CadenaPermisos; Ejecutable"
	fi
	
		for x in $(find -type f -size +"$1"c)
		do
			if [ -x $x ]
			then 
				ejecutable=1
			else
				ejecutable=0
			fi
			
			fichero=$(stat -c "%n" $x)
			nombre=$(basename $x)
			let longitud=$(stat -c "%U" $x | wc -m)-1
			tamano=$(stat -c "%s" $x)
			seg=$(stat -c "%X" $x)
			usuarioID=$(stat -c "%u" $x)
			grupoID=$(stat -c "%g" $x)
			permisos=$(stat -c "%A" $x)
			extension=$(basename $x | cut -d "." -f 2)
			
			echo "$fichero; $nombre; $longitud; $tamano; $seg; $usuarioID; $grupoID; $permisos; $ejecutable; $extension"
			
		done | sort -k2 -t "-"
fi
	
	
	
	

