#!/bin/bash
#Escribir un script que lea la informacion de la carpeta /proc/ e imprima:

# Modelo de procesador y megahercios, tamaño de la cache, identidicacion del vendedor, numero 
#maximo de hilos de ejecucion

cat /proc/cpuinfo | sed -r -e '1,9!d' | sed -r -e 's/model name.*:(.*)/Modelo de procesador: \1/' | sed -r -e 's/cpu MHz.*:(.*)/Megahercios: \1/' | sed -r -e 's/cache size.*:(.*)/Tamaño de caché: \1/' | sed -r -e 's/vendor_id.*:(.*)/ID vendedor: \1/' | grep -E '^(M|N|T|I|P)'


hilos=$(grep -o -E 'processor' /proc/cpuinfo | wc -l)

echo "Numero de hilos máximo de ejecución: $hilos"

cat /proc/partitions
cat /proc/mounts



