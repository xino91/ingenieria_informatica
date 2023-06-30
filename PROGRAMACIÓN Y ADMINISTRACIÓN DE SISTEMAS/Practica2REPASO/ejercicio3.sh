#!/bin/bash

#3) Utilizando grep y/o sed para cada una de las siguientes tareas, realizar un script que 
#que reciba un nombre de fichero por la linea de comandos y realice las siguientes tareas:
# - Liste todos los ficheros ocultos de la carpeta personal del usuario ordenados por número
#de caracteres

if [ $# -ne 1 ]
then 
	echo "Error en la invocación del programa. <Programa> <nombre_fichero>"
	exit 1
fi

directorio="/home/$USER"
fichero=$(basename $1) #Almacenamos el nombre del fichero sin la ruta

temp=$(mktemp)
temp2=$(mktemp)

echo "$(ls -a $directorio | grep -E '^\.')" > $temp

for x in $(cat $temp)
do
	caracteres=$(echo $x | wc -m)
	echo "$caracteres $x" >> $temp2
	
done 

echo "1) Listado de ficheros ocultos de la carpeta personal del usuario '$directorio' ordenados por numero de caracteres"

cat $temp2 | sort -nk1 | grep -E '^\.*'	# -n -->Para que lo ordene por valor numerico
		
		
# - Haga una copia del fichero cyuo nombre se ha recibido por la linea de comandos en la que
#se elimininan todas las lineas vacias. El nombre de la copia será FICH.sinLineasVacias,
#siendo FICH el nombre del fichero que ha intorducido el usuario. Esto se hará siempre que #el fichero exista.

echo "Copia sin Líneas vacías"

echo "$(cat $fichero | grep -E '[A-Za-z0-9]')""\n" > fichero.sin_lineas_vacias

echo "Copia Creada en $fichero.sin_lineas_vacias"

# - Liste por pantalla todos los procesos que tú usuario está ejecutando en ese momento.
#Para cada proceso deberás mostrar PID, hore en que se lanzó y nombre del fichero ejecutable
	
	# ps -> Muestra lista de procesos del usuario
	# ps aux -> Muestra lista de proceos de la máquina
		# -u -> Lista información del proceso como por ejemplo el usuario que lo está corriendo, la utilización de Cpu y
		# memoria, etc.

ps -ux | sed -rn 's/(^[A-Za-z]*)\ *([0-9]*)\ *([0-9\.]*)\ *([0-9\.]*\ *[0-9]*\ *[0-9]*)\ *([A-Za-z0-9\?\/]*)\ *([A-Za-z]*)\ *([0-9A-Za-z\:]*)\ *([0-9\:]*)\ *([A-Za-z\/\-]*).*/PID: "\2" Hora: "\7" Ejecutable: "\9"/p'


