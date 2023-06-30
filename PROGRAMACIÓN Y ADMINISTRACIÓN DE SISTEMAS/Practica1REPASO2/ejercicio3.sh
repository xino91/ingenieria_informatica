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

if [ $# -lt 1 ] || [ $# -ge 4 ];
then 
	echo -e "\n"
	echo "ERROR: debe introducir <directorio> <umbral1> <umbral2> , siendo el directorio obligatorio"
	exit 1
fi

#UMBRALES
if [ $# -eq 1 ]  #No ha introducido umbrales, los ponemos por defecto
then 
	umbral1=10000
	umbral2=100000
else
	umbral1=$2
	umbral2=$3
fi

directorioactual=$(pwd)	#Directorio donde vamos a crear las carpetas

if [ -e $directorioactual/pequenos ] && [ -e $directorioactual/medianos ] && [ -e $directorioactual/grandes ];
then 
	echo "Las carpetas de salida ya existen, se va a proceder a borrarlas..."
	echo -e "\n"
	
	rm -d -r $directorioactual/pequenos
	rm -d -r $directorioactual/medianos
	rm -d -r $directorioactual/grandes
fi

#Creamos las carpetas 
mkdir $directorioactual/pequenos
mkdir $directorioactual/medianos
mkdir $directorioactual/grandes


#Clasificamos los archivos y guardamos en su correspondiente carpetas

for x in $(find $1)
do
	tam=$(stat -c "%s" $x)
	
	if [ $tam -lt $umbral1 ];
	then	
		if [ -f $x ];
		then
			cp $x $directorioactual/pequenos
		fi
		
	else 
		if [ $tam -gt $umbral2 ];
		then
			if [ -f $x ];
			then 
				cp $x $directorioactual/grandes
			fi
		else
			if [ -f $x ];
			then 
				cp $x $directorioactual/medianos
			fi
		fi
	fi
done

echo "Ficheros guardados en sus correspondientes carpetas"



