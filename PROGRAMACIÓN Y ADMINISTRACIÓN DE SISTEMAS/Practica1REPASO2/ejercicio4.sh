#!/bin/bash 
#ejercicio4) Escribir un script que realice las siguientes acciones:
#Mostrar el número de archivos en el directorio actual, sin contar directorios.
#Mostrar una lista ordenada de los usuarios que hay logeados en el sistema en el instante en
#que se ejecuta el script, eliminando los usuarios repetidos.
#Imprimir el número de veces que aparece un determinado carácter, que se le solicita al
#usuario, en nombres de ficheros contenidos en la carpeta actual o en alguna subcarpeta. Si
#el usuario no indica el carácter en 5 segundos, utilizar la letra ’a’.


narchivos=0

#CONTAJE DE ARCHIVOS 
for x in $(ls -l)
do
	if [ -f $x ];
	then 
		let narchivos=$narchivos+1;
	 
	fi
done

echo "Tenemos $narchivos archivos en el directorio actual, sin contar subcarpetas"
echo -e "\n"


#LISTA ORDENADA USUARIOS LOGEADOS

echo "Usuarios logeados en este momento"

who | awk '{print $1}' | sort -k1 | uniq

echo "----------------"


#IMPRIMIR CARACTER QUE SE LE SOLICITA AL USUARIO

echo "¿Que carácter quieres contar? Introduzcalo"
read -t5 caracter

if [[ -z $caracter ]]
then 
	caracter=a
fi

ncaracter=0

for x in `ls -R`
do
	if [[ $x =~ $caracter ]]
	then 
		let ncaracter=$ncaracter+1;
	fi
done 
	
	echo "El caracter $caracter apacerece $ncaracter veces en nombres de ficheros o carpetas contenidos en carpeta actual"
	echo -e "\n"






