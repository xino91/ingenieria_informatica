#!/bin/bash

#Ejercicio1 TIPO EXAMEN JUNIO 2018: Script que reciba como primer argumento un directorio y un segundo un tamaño en bytes
#El script (SI SE PASA DOS ARGUMENTOS) debe buscar todos los fichero .c que estén alojados en la carpeta y subcarpetas
#(primer argumento) y con un tamaño mayor(segundo argumento), deberá imprimir por pantalla cada opcion explicada mas abajo 
#El script (SI SOLO SE PASA UN ARGUMENTO), este será el tamaño en bytes, y deberá  buscar todos los ficheros .c que haya
#solamente en el directorio actual sin mirar subcarpetas, deberá imprimir por pantalla los mismo explicado mas abajo.
#0. El nombre del fichero (con ruta).
#1. El nombre del fichero (sin la ruta).
#2. El número de caracteres del nombre del usuario propietario.
#3. La fecha de creación (legible) y del último acceso al fichero (segundos UNIX).
#4. Nombre del usuario propietario
#3. Nombre del grupo propietario.
#5. La cadena de permisos del fichero.
#6. Un 1 si el fichero es ejecutable o un 0 si no lo es.
#Todos los campos se separarán por el caracter ";" y la salida deberá ordenarse númericamente por 
#tamaño (de menor a mayor).

if [ $# -lt 1 ] || [ $# -gt 2 ];
then
	echo "ERROR: debe introducir argumentos, el primero será un directorio(opcional) el segundo es tamano en bytes(obligatorio"
	echo -e "\n"
	exit 1
fi

intro=0	#variable para saber si ya hemos imprimido atributos

#----------------------------------------
#	CONTROL DE ARGUMENTOS 
#----------------------------------------

#Hemos pasado dos argumentos, miramos en todos las carpetas y suubcarpetas
if [ $# -eq 2 ];
then
	tam=$2
	
	if [ "$intro" -eq 0 ];
	then 
		echo "Fichero; Nombre; LongitudUsuario; Tamano; Fecha; UsuarioID; GrupoID; CadenaPermisos; Ejecutable"
	fi
	
		for x in $(find $1 -maxdepth 1 -name "*.c*" -size +"$tam"c)
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
			
			
			echo "$fichero; $nombre; $longitud; $tamano; $seg; $usuarioID; $grupoID; $permisos; $ejecutable"
			
		done | sort -n -k4 -t ";"
		#n -> ordena por valor numerico
fi

#Solo paso un argumento, miramos solo en directorio actual, sin mirar subcarpetas
if [ $# -eq 1 ];
then
	
	if [ "$intro" -eq 0 ];
	then
		echo "Fichero; Nombre; LongitudUsuario; Tamano; Fecha; UsuarioID; GrupoID; CadenaPermisos; Ejecutable"
	fi
		
		for x in `ls -l $1`
		do
			if [ -f $x ]
			then
				echo "hola"
			fi
						
		done | sort -n -k4 -t ";"
fi
	
	
	
	
	
	
			
