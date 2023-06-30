#!/bin/bash

#Ejercicio3) Crear un script que clasifique los ficheros que hay dentro de una carpeta en función #de su tamaño en pequeños, medianos y grandes. El primer argumento del script recibido por lı́nea de
#comandos será la carpeta a procesar (siendo un argumento obligatorio). Habrá dos argumentos
#adicionales y opcionales que serán los umbrales para discernir las tres categorı́as (umbral1 y
#umbral2), de forma que los ficheros pequeños serán todos aquellos cuyo tamaño sea menor que
#2umbral1, los medianos serán aquellos ficheros cuyo tamaño esté entre umbral1 y umbral2 (in-
#cluidos), y los grandes serán los ficheros con tamaño mayor que umbral2. Se supone que los ta-
#maños se especifican en bytes. El valor por defecto para umbral1 y umbral2 será 10000 y 100000,
#respectivamente. El script debe crear tres subcarpetas (pequenos, medianos y grandes) dentro
#de la carpeta en la que se realiza la llamada al script e incluir en cada una los ficheros #correspon-dientes. Si las carpetas ya existen, borrarlas.

#--------------------------------
#	CONTROL DE ARGUMENTOS
#--------------------------------

if [ $# -eq 0 ] || [ $# -ge 4 ];
then 
	echo "ERROR: Debe introducir $0 <nombre_directorio> y, si lo desea, unu umbral inferior y otro superior"
	echo "\n"
	exit 1

	else 
		#Establecemos los valores de los umbrales
		if [ $# -eq 1 ];
		then 
			umbral1=10000
			umbral2=100000
		else
			if [ $# -eq 3 ];
			then
				umbral1=$2
				umbral2=$3
		fi
	fi
	
#----------------------------------
#	COMPROBACION DE CARPETAS
#----------------------------------

if [ -e $1/pequenos ] && [ -e $1/medianos ] && [ -e $1/grandes ]
then
	echo "Las carpetas de salida ya existen, se va a proceder a borrarlas"
	
	# -d -->Borramos los directorios
	# -r -->Borramos respectivamente todo lo que contengan
	
	rm -d -r $1/pequenos
	rm -d -r $1/medianos
	rm -d -r $1/grandes
fi


#Ahora creamos las nuevas carpetas de salida donde se copiarán los ficheros clasificados por tamaño
echo "Creando las carpetas, pequenos,medianos y grandes...."
mkdir pequenos
mkdir medianos
mkdir grandes


#----------------------------------
#	PROCESAMIENTO
#----------------------------------

echo "Copiando los archivos..."

#Clasificamos los ficheros por tamaño
for x in $(find $1)
do
	tam=$(stat -c "%s" $x)  #Tamano del fichero
	
	if [ $tam -lt $umbral1 ];  #Si el tamaño es menor que el umbral1
	then
		if [ -f $x ];  #Comprobamos que es un fichero normal
		then 
			cp $x $1/pequenos  #Copiamos el fichero en la carpeta pequenos
		fi
	else
		if [ $tam -gt $umbral2 ];
		then 
			if [ -f $x ];
			then
				cp $x $1/grandes
			fi
		else 
		
			if [ -f $x ];
			then 
				cp $x $1/medianos
			fi
		fi
	fi
	
	done
fi

echo -e "\n"
		
	
	
	
	
	
