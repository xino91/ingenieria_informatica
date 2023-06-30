#!/bin/bash
clear
directorio="/home/$USER"

echo "listado de archivos ocultos del directorio $directorio"
#fichero temporal super pro
temp=$(mktemp)

for fichero in $(ls -a $directorio)
do
	fich=$(basename $fichero)
	ocultos=$(echo $fich | grep '^\.')

	if [[ $ocultos == $fich ]]
	then
		numLineas=$(echo $ocultos | wc -c)
		echo "$numLineas;$ocultos" >> $temp
	fi
done
#ordenar
cat $temp | sort -n -k 1 | sed -n -e 's/\(.*\);\(.*\)/\2/p'
echo "------------------------------------"
echo -n "El fichero a procesar es $1"
echo ""
fich1="$1.sinlineasvacias"
cat $1 | grep '^.' > $fich1
echo "el fichero sin lineas vacias se ha guardado en $fich1"

echo "Listado de los procesos por el usuario $USER: "
ps -u $USER -o pid,start_time,comm | sed -n -r -e 's/([0-9]+) (([0-9]+):([0-9]+)) (.+$)/PID: \"\1\" Hora: \"\2\" Ejecutable: \"\5\"/p'

