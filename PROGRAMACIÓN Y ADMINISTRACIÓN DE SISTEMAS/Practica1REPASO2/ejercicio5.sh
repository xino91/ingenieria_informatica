#!/bin/bash


#REalizar un script que aplique una copia de seguridad de ficheros o directorios. Todos los 
#ficheros o directoriors que se pasen por argumento en la linea de comandos al script se
#comprimiran juntos en un único fichero copia-usuario-fecha.tar.gz, donde usuario es el 
#usuario que está ejecutando el script y fecha es la fecha en segundos desde el 1 enero 1970.
#Una vez comprimidos, los archivos se moverán a la carpeta ~/Copia. Si la carpeta no existe,
#hay que crearla. Al invocar el script, todos los ficheros de la carpeta ~/Copia con una
#antiguedad mayor a 200 segundos, deberan ser borrados. 

if [ $# -eq 0 ];
then 
	echo "Se necesital al menos un directorio o un fichero para comprimir"
	echo -e "\n"
	exit 1
fi

echo $(pwd)
# BORRAMOS LOS ARCHIVOS DEL DIRECTORIO CUYA ANTIGUEDAD SEA MAYOR A 200 SEGUNDOS
if [ -d $(pwd)/Copia ];
then 
	for x in $(find $(pwd)/Copia -type f)
	do
		#Segundos desde 1 enero de 1970, hay que indicar a date que utilice +
		mod=$(stat -c "%Y" $x)
		rm -r $(pwd)/Copia
		
		echo "Se ha borrado el Directorio $(pwd)/Copia"
		echo -e "\n"
	done
fi


nExist=0 #variable para el contabilizar el vector 

#ARRAY DE ARCHIVOS VALIDOS
#si eliminamos la parte in Lista Iteramos sobre la linea de argumentos $1 $2 $3 .....
for x		
do
	if [ -e $x ];
	then 
		seg=$(date +"%s")
		miArray[$nExist]=$x
		let nExist=$nExist+1
	else
		echo "El argumento <$x> no existe"
	fi
done



#Comprimimos el array 
#tar czf:
#c --> Crea un nuevo archivo
#z --> Comprime el archivo usando gzip
#f --> Nombre del archivo
#Si puesieramos czvf, v --> Muestra el proceso durante la creación del archivo

tar -czf copia-$USER-$fecha.tar.gz ${miArray[*]}
echo "Comprimiendo los archivos..."


#Creamos la carpeta Copia si no existe
if [ ! -e $(pwd)/Copia ];
then 
	echo "Creando la carpeta de copia"
	mkdir $(pwd)/Copia
fi

#Movemos el archivo comprimido al directorio Copia
mv copia-$USER-$fecha.tar.gz $(pwd)/Copia/

echo "La copia de seguridad se ha creado correctamente"
echo -e "\n"








	
	
	
