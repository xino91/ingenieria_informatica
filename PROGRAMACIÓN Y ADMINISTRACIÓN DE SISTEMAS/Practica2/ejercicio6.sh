#!/bin/bash

if [ $# -ne 1 ]
then 
	echo -e "Error argumentos\n"
else
	old=$IFS #separador actual
	IFS=$'\n'
	if [ $1 == $SHELL ];
	then
		for x in $(cat /etc/passwd)
		do
			y=$(echo $x | sed -n 's/^[^:]\{1,\}:[^:]\{1,\}:\([^:]\{1,\}\):.*/\1/p')
			
			if [ $y -ge 1000 ];
			then
			
				echo $x | sed -n 's/^\([^:]\{1,\}\):[^:]\{1,\}:\([^:]\{1,\}\):\([^:]\{1,\}\):\([^:]\{0,\}\):\([^:]\{1,\}\):\([^:]\{1,\}\)/Logname: \1\n->UID: \2\n->GID: \3\->gecos: \4\n->Home: \5\m->Shell por defecto: \6\n/p'
				
			fi
			
		done
	else
		if [ $1 -eq 0 ];
		then
			echo -e "Se mostraran usuarios cuyo UID sea menor que 1000\n========\n"
			for x in $(cat /etc/passwd)
			do
			
			y=$(echo $x | sed -n 's/^[^:]\{1,\}:[^:]\{1,\}:\([^:]\{1,\}\):.*/\1/p')
			
			if [ $y -lt 1000 ];
			then
				echo $x | sed -n 's/^\([^:]\{1,\}\):[^:]\{1,\}:\([^:]\{1,\}\):\([^:]\{1,\}\):\([^:]\{0,\}\):\([^:]\{1,\}\):\([^:]\{1,\}\)/Logname: \1\n->UID: \2\n->GID: \3\->gecos: \4\n->Home: \5\m->Shell por defecto: \6\n/p'
				
			fi
		done
	else
		echo "El argumento debe ser 1 o 0"
	fi
fi
IFS=$old
			
