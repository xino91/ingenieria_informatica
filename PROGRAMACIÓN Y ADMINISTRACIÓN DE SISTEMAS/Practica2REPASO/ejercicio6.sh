#!/bin/bash

#ejercicio6.sh

#-----------------------------------ENUNCIADO-------------------------------------------
#Desarrollar un script que muestre el contenido del fichero /etc/passwd (y parte del fichero /etc/group) de forma amigable. El script recibirá un único argumento que será una cadena de texto. Solo se mostrarán los usuarios que tengan esa cadena como shell de sistema (comprobar que la cadena está justo en ese campo y no en otro). Por cada usuario se imprimirá:

	#-logname del usuario.

	#-UID del usuario.

	#-groupname de su grupo primario.
	
	#-GID de su grupo primario.
	
	#-Información gecos.
	
	#-Carpeta personal.
	
	#-Shell por defecto.
	
	#-Un 1 si el usuario está actualmente logeado y un 0 en caso contrario.
#---------------------------------------------------------------------------------------

if [ $# -ne 1 ] # Control de invocación del programa (El número de argumentos ha de ser el correcto)
then

	echo "Error en la invocación del programa. Pista: $0 <NombreDeUsuario>"
	exit 1

fi

#En la variable 'lineas' almacenamos la tercera y la segunda columna del archivo /etc/group/ de esta forma: 3ºcolumna,2ºcolumna. 
lineas=$(cat /etc/group | sed -rn 's/^([a-z\-]*):.:([0-9]*):.*/\2,\1/p')

#Hacemos a continuación un for en el que recorremos lo almacenado en la variable 'lineas' para crear un diccionario 'grupo'
for x in $lineas 
do

	indice=$(echo $x | grep -Eo '[0-9]*')
	clave=$(echo $x | grep -Eo '[a-z\-]*')

	grupo["$indice"]="$clave"

done


#Guardamos en la variable 'passwd' solo los elementos del archivo /etc/passwd que se nos pide en el enunciado y que contengan el nombre del usuario (pasado por argumento).
passwd=$(cat /etc/passwd | sed -rn 's/^([a-z\-]*):x:([0-9]*):([0-9]*):([a-zA-Z\-\/]*):([\/a-z]*):([\/a-z]*)/Logname:·\1;->UID:·\2;->Grupo:·xxx;->GID:·\3;->gecos:·\4;->Home:·\5;->Shell_por_defecto:·\6/p' | grep $1)

#Hacemos un for que recorra la variable 'passwd' obtenida antes
for y in $passwd
do
	#Guardamos en la variable 'GUID' el GUID de cada elemento de la variable 'passwd'
	GUID=$(echo "$y" | sed -rn 's/.*GUID:·([0-9]*).*/\1/p')


	#Recorremos dentro del bucle for en el que estamos con otro bucle for el nombre de los usuarios que estan actualmente logueados en el host actual, (ver man users o echo "$(users)" ).
	for z in $(users)
	do
		#Comprobamos que el users que es estamos recorriendo actualmente sea igual al logname si es así marcamos en la variable 'conectado' que lo esta con un 1 y salimos del for.
		if [[ "$(echo "$y" | sed -rn 's/logname:·([a-zA-Z\-]*).*/\1/p')" == "$z" ]]; then

			conectado=1

			break

		else #En caso contrario,marcamos que no esta conectado el usuario con un 0.

			conectado=0

		fi
		
	done
	
	#Imprimimos por pantalla los datos que piden del usuario cuyo nombre se pasa por argumento suprimiendo los ';' y '.' que pusimos en la variable passwd, (ya que es un comando lo que estabamos escribiendo y no había tanta libertad) por saltos de línea y espacios, respectivamente.
	printf "${grupo[$GUID]}-$y" | sed -rn 's/(^[a-z]*)-(.*)xxx(.*$)/\2\1\3/p' | tr ';' '\n' | tr '·' ' '
	
	printf "\nLogueado: $conectado\n"

done
