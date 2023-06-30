#!/bin/bash


#REalizar un script que aplique una copia de seguridad de ficheros o directorios. Todos los 
#ficheros o directoriors que se pasen por argumento en la linea de comandos al script se
#comprimiran juntos en un único fichero copia-usuario-fecha.tar.gz, donde uduario es el 
#usuario que está ejecutando el script y fecha es la fecha en segundos desde el 1 enero 1970.
#Una vez comprimidos, los archivos se moverán a la carpeta ~/Copia. Si la carpeta no existe,
#hay que crearla. Al invocar el script, todos los ficheros de la carpeta ~/Copia con una
#antiguedad mayor a 200 segundos, deberan ser borrados.


if [ $# -eq 0 ]
then
	echo "ERROR: Se necesita al menos un fichero o directorio a comprimir"
	echo -e "\n" 
	exit 1

fi


#----------------------------------------
#	BORRADO DE ARCHIVOS
#----------------------------------------

#Borramos los archivos del directorio copia cuya antiguedad sea mayor a 200 segundos
# -type f --> escogemos solo los ficheros
# while read x --> Vamos recorriendo todos los ficheros

if [ -d $HOME/Copia ]
then 
	find $HOME/Copia/ - type f | while read x
	
	do 
		seg=$(date +%s) #Segundos desde el 1 enero de 1970 "man date"
		modif=$(stat -c "%Y" $x) #Ultima modificacion del fichero
		
		diferencia=$(($seg - $modif))
		
		if [ diferencia -gt 200 ];
		then
			rm $x
			echo "Se ha borrado $x, llevaba $diferencia segundos sin modificarse"
		fi
	done
fi


#-------------------------------------
#	ARRAY DE ARCHIVOS VÁLIDOS
#------------------------------------

let nExist=0 #Variable para contabilizar los ficheros o directorios pasados que si existen

#Comprimimos los ficheros o directorios y los movemos al directorio Copia.
#for x --> iteramos sobre la lista de argumentos ($1, $2, $3, ...)

for x
do
	if [ -e $x ];
	then 
		fecha=$(date +%s)
		
		#Si existe, lo pasamos a uun array (ignorando los que no esxisten). Este Array 
		#este array será el que comprimamos.
		
		Array[$nExist]="$x"
		let nExist=$nExist+1
	else 
		echo "El argumento <$x> no existe."
	fi
done

#Si no se ha introducido ningún argumento válido, termina la ejecución
if [ nExist -eq 0 ]
then
	echo "No se ha introducido ningún argumento válido. Terminamos la ejecución"
	exit 1
fi

















