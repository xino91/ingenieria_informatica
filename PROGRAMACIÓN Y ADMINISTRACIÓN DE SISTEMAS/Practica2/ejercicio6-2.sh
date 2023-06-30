#!/bin/bash
#Desarrollar un script que muestre el contenido del fichero /etx/passwd (y parte del fichero/
#/etc/group) de forma amigable. El script recibirá un único argumento que será una cadena de 
#texto. Solo se mostrarán los usuarios que tengan esa cadena como shell de sistema (comprobar
#que la cadena está justo en ese campo y no en otro).

if [ $# != 1 ]
then
	echo "Numero de argumentos incorrecto"
	exit
fi


if [ $1 == 1 ]
then
	cat /etc/passwd | grep -E '.*\:\*\:[1:9][0-9][0-9][0-9]\:' | sed -r -e 's/^([a-z]*):\*:([0-9]*):*(.*\/home)(.*)/Longname: \1\n->UID: \1\n->GID \3\n->Home: \4\n->Shell por defecto \5/'
	
else
	cat /etc/passwd | sed -r -e 's/^([a-z]*):\*:([0-9]*):([0-9]*):*(.*\/home)(.*)/Longname: \1\n->UID: \2\n->GID \3\n->Home: \4\n->Shell por defecto \5/'

fi
