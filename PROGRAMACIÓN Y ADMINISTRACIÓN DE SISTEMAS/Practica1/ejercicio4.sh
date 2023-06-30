#!/bin/bash 
#ejercicio4) Escribir un script que realice las siguientes acciones:
#Mostrar el número de archivos en el directorio actual, sin contar directorios.
#Mostrar una lista ordenada de los usuarios que hay logeados en el sistema en el instante en
#que se ejecuta el script, eliminando los usuarios repetidos.
#Imprimir el número de veces que aparece un determinado carácter, que se le solicita al
#usuario, en nombres de ficheros contenidos en la carpeta actual o en alguna subcarpeta. Si
#el usuario no indica el carácter en 5 segundos, utilizar la letra ’a’.

echo -e "\n"

#-------------------------------
# 	CONTAJE DE ARCHIVOS
#-------------------------------

#Limpiamos el texto de la consola
clear
										# -e f1 existe fichero
										# -s f1 tamaño mayor que 0?
										# -f f1 es f1 fichero normal
										# -d f1 es f1 un directorio
										# -l f1 es f1 un enlace simbolico
										# -r f1 tienes permiso de escritura sobre f1?
										# -w y -x para escritura y ejecucion

for x in `ls -l`						
do
	if [[ -f $x ]]
	then
		let nArchivos+=1  #Contador de archivos
	fi
done

echo "El numero de archivos en la carpeta actual es $nArchivos"
echo "-----------"


#------------------------------------
# 	USUARIOS LOGEADOS
#-----------------------------------

echo "Esta sería la lista de usuarios conectados en este momento:"

# who --> Muestra información sobre los usuarios que están actualmente logeados
# awk '{print $1}' --> Extrae el nombre de login que se le pase (who)
# sort -k1 --> Ordena según la columna 1 (nombre_login) que se le pasa por tuberías
# uniq --> evita elementos duplicados entre todos los que se le pasen por tuberías

who | awk '{print $1}' | sort -k1 | uniq

echo "----------------"


#--------------------------------------
#	CONTAJE DE CARÁCTER
#-------------------------------------

echo "¿Qué carácter quieres contar?"
read -t5 caracter  #Espera durante 5 segundo para leer por teclado

#Si no se introduce ningún carácter, se tomará 'a' por defecto
if [[ -z $caracter ]]
then 
	caracter=a
fi

#Recorremos los ficheros de la carpeta actual y de las subcarpetas 
# ls -R --> Lista todo, incluyendo subcarpetas y sus ficheros
for x in `ls -R`
do
	if [[ $x =~ $caracter ]]
	then
		let nCaracter+=1
	fi
done 

echo " El carácter '$caracter' aparece $nCaracter veces en nombres de ficheros o carpetas contenidos en la carpeta actual."

echo -e "\n"





