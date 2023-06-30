#!/bin/bash

#ejercicio5.sh

#-----------------------------------ENUNCIADO-------------------------------------------
#Escribir un script que lea información de la carpeta /proc/ e imprima:
	#-Modelo de procesador y Megahercios.
	
	#-Tamaño de caché e identificador de vendedor.
	
	#-Número máximo de hilos de ejecución.
	
	#-Puntos de montaje activos, incluyendo el punto de montaje, el dispositivo y el tipo de dispositivo. Ordenarlos de forma alfabética inversa por punto de montaje.

	#-Listado de todas las particiones disponibles, junto con su número de bloques. Ordenarlas de forma alfabética inversa por partición.

#Los ficheros que deberás consultar son /proc/cpuinfo, /proc/mounts y /proc/partitions.
#---------------------------------------------------------------------------------------

if [ $# -ne 0 ] # Control de invocación del programa (El número de argumentos ha de ser el correcto)
then

	echo "Error en la invocación del programa. Pista: $0 "
	exit 1

fi



#En la variable 'modeloproc' almacenaremos el modelo del procesador.
	#Para ello nos quedamos con lo almacenado en "model name: " dentro del archivo /proc/cpuinfo
	#sed: opción -r para usar EREs y opción -n para modo silencioso (para imprimir es necesario poner la bandera /p al final). También usamos la bandera de sustitución s, (s/patrón/reemplazo).
modeloproc=$(cat /proc/cpuinfo | sed -rn 's/model name	: (.*)/Modelo del procesador: \1/p')

#Para obtener el número máximo de hilos,(que almacenaremos en la variable'nMaxHilos') tan sólo deberemos contar el número de cores que hay.
#Por eso contamos el número de líneas en las que se especifica en el fichero /proc/cpuinfo el nombre del procesador.
nMaxHilos="Número máximo de hilos de ejecución: $(printf "$modeloproc\n" | wc -l)"

#cut: corta parte de la salida, al hacer -d '\n' corta a partir de encontrarse un salto de línea de modo que imprime el 1º campo (-f 1) solamente.
modeloproc=$(echo "$modeloproc\n" | cut -d '
' -f 1)
#Para obtener los MegaHercios de la cpu buscamos en el archivo proc/cpuinfo y usamos cut como en el comando anterior para quedarnos con la primera aparición solamente
mhz="$(cat /proc/cpuinfo | sed -rn 's/cpu MHz : (.*)/MegaHercios: \1/p' | cut -d '
' -f 1) Mhz"

#Para obtener el id del vendedor,(que almacenaremos en la variable'idvendedor') tan sólo deberemos buscar en el archivo proc/cpuinfo el campo 'vendor_id: ' y quedarnos con lo almacenado allí. 
#También haremos cut para quedarnos sólo con la primera aparición del identificador.
idvendedor=$(cat /proc/cpuinfo | sed -rn 's/vendor_id	: (.*)/Identificador de vendedor: \1/p' | cut -d '
' -f 1)

#Para obtener el tamaño de la caché haremos lo mismo que anteriormente (buscar en el archivo /proc/cpuinfo el contenido de 'cache size') posteriormente guardaremos la primera aparición de este en la variable 'cache'
cache=$(cat /proc/cpuinfo | sed -rn 's/^cache size	: (.*)/Tamaño de caché: \1/p' | cut -d'
' -f 1)



printf "-Modelo de procesador y MegaHercios: \n"
printf "$modeloproc\n$mhz\n"

printf "Tamaño de caché e identificador de vendedor: \n"
printf "$cache\n$idvendedor\n"

printf "Número máximo de hilos de ejecución."
printf "$nMaxHilos\n"

printf "\n\nPuntos de montaje:\n"

#Buscamos con 'sed' en el archivo /proc/mounts el punto de montaje, el dispositivo y el tipo de este y lo ordenamos de forma alfabética inversa. 
cat /proc/mounts | sed -rn 's/^[a-z]*\ *([a-z/]*)\ *([a-z]*)\ *[a-z]*,[a-z]*,([a-z]*),[a-z]*.*/Punto de montaje: \1,\t Dispositivo: \3, \tTipo de dispositivo: \2/p' | sort -r


printf "\nParticiones y numero de bloques:\n"

#Buscamos con 'sed' en el archivo /proc/partitions las particiones y el número de bloques de cada una.
cat /proc/partitions | sed -rn 's/\ +[0-9]*\ *[0-9]*\ *([0-9]*)\ *([0-9a-z]*)/Partición: \2,\t Número de bloques: \1/p'

