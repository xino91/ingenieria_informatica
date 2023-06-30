#!/bin/bash

#Este ejercicio es una modificacion del ejercicio3.sh. Crear un script que reciba 
#como primer arguemtno una carpeta (opcional) y un segundo argumento que será un
#tamaño en bytes(obligatorio). El script debe buscar todos los ficheros que estén
#alojados en el directorio (y no en las subcarpetas). Si no se pasa la carpeta del
#como argumento se deberá buscar en la carpeta de trabajo actual y todas las 
#subcarpetas. Se debe contar el número de ficheros menores o iguales al tamaño
#encontrados y la suma total de sus tamaños asi como de los mayores o iguales al 
#tamaño encontrados y la suma total de sus tamaños así como de los mayores o iguales
#al tamaño. Ademas de esto, se deberán mostrar de cada fichero
#-Numero de lineas del fichero
#-Extension del fichero completa
#-ID numerica del usuario propietario
#-Una R si el fichero tiene permisos de escritura y una r en caso de que no.
#--------------------------
#Esta lista debe estar ordenada alfabeticamente y de forma inversa por la extension
#del archivo, para separar los campos, utilizar el caracter "+"
#Una vez mostrados los ficheros, se deberá de hacer na copia de seguridad de los 
#ficheros grandes, que serán guardadas en el directorio de trabajo actual con el
#formato dia-año.tar.gz donde dia será el numero de dia del año (0-366).

if [ $# -lt 1 ] || [ $# -ge 3 ];
then 
	echo "ERROR: Debe introducir $0 <nombre_directorio> (opcional) y un tamaño en byte (obligatorio)"
	echo -e "\n"
	exit 1
fi

echo -e "\n"

contador1=0
tamano1=0
contador2=0
tamano2=0
intro=0

# 2 Argumentos
if [ $# -eq 2 ]
then 

#----------------CONTAMOS MENORES---------------------------	
	for x in $(find $1 -maxdepth 1 -size "$2"c -type f -or -size -"$2"c -type f)
	do
		let contador2=$contador2+1
		tam=$(stat -c "%s" $x)
		let tamano2=$tamano2+$tam
		
	done
	echo "El numero de fichero menores o iguales al umbral es $contador2 y la suma de sus bytes es $tamano2"
#-------------------------------------------------------------

#------------CONTAMOS MAYORES------------------------------
	for x in $(find $1 -maxdepth 1 -size "$2"c -type f -or -size +"$2"c -type f)
	do
		let contador1=$contador1+1
		tam=$(stat -c "%s" $x)
		let tamano1=$tamano1+$tam
		
	done
	
	echo "El numero de fichero menores o iguales al umbral es $contador1 y la suma de sus bytes es $tamano1"
		echo -e "\n"
#-----------------------------------------------------------

echo "Nombre+Lineas+Extension+Permisos"

#---IMPRIMIMOS DATOS FICHEROS---------------------
		for x in $(find $1 -maxdepth 1 -type f)
		do
		
			if [ -w $x ];  # -x  --> si tiene permisos escritura
			then 
				permisos="R"  
			else
				permisos="r"  
			fi
			
	#---------RECOLECCION DATOS---------------
			nombre=$(basename $x)
			lineas=$(cat $x | wc -l)
			extension=$(basename $x | cut -d "." -f 2,3,4,5)
			
			echo "$nombre+$lineas+$extension+$permisos"
		done | sort -r -k3 -t "+"
		
	#-----COPIA SEGURIDAD FICHEROS GRANDES---------------
dia=`date +%j`
ano=`date +%Y`
nExist=0
	echo "---------------------------------------------------------_"
	echo "S van a comprimir los ficheros grandes en el fichero $dia-$ano.tar.gz"
		for x in $(find $1 -maxdepth 1 -size +"$2"c -type f)
		do
			miArray[$nExist]=$x
			let nExist=$nExist+1
			
		done
		
	tar -czvf $dia-$ano.tar.gz ${miArray[*]}
#-------------------------------------------------------------------
fi #2 argumentos 


#############################################################################

# 1 Argumento que sera tamaño en bytes
if [ $# -eq 1 ]
then 

#----------------CONTAMOS MENORES---------------------------	
	for x in $(find -size "$1"c -type f -or -size -"$1"c -type f)
	do
		let contador2=$contador2+1
		tam=$(stat -c "%s" $x)
		let tamano2=$tamano2+$tam
		
	done
	echo "El numero de fichero menores o iguales al umbral es $contador2 y la suma de sus bytes es $tamano2"
#-------------------------------------------------------------

#------------CONTAMOS MAYORES------------------------------
	for x in $(find -size "$1"c -type f -or -size +"$1"c -type f)
	do
		let contador1=$contador1+1
		tam=$(stat -c "%s" $x)
		let tamano1=$tamano1+$tam
		
	done
	
	echo "El numero de fichero menores o iguales al umbral es $contador1 y la suma de sus bytes es $tamano1"
		echo -e "\n"
#-----------------------------------------------------------

echo "Nombre+Lineas+Extension+Permisos"

#---IMPRIMIMOS DATOS FICHEROS---------------------
		for x in $(find -type f)
		do
		
			if [ -w $x ];  # -x  --> si tiene permisos escritura
			then 
				permisos="R"  
			else
				permisos="r"  
			fi
			
	#---------RECOLECCION DATOS---------------
			nombre=$(basename $x)
			lineas=$(cat $x | wc -l)
			extension=$(basename $x | cut -d "." -f 2,3,4,5)
			
			echo "$nombre+$lineas+$extension+$permisos"
		done | sort -r -k3 -t "+"
		
dia=`date +%j`
ano=`date +%Y`
nExist=0
	echo "---------------------------------------------------------_"
	echo "S van a comprimir los ficheros grandes en el fichero $dia-$ano.tar.gz"
		for x in $(find -size +"$1"c -type f)
		do
			miArray[$nExist]=$x
			let nExist=$nExist+1
			
		done
		
	tar -czvf $dia-$ano.tar.gz ${miArray[*]}
fi #1 argumentos




