#!/bin/bash	
#Este ejercicio es una modificacion del ejercicio1 de la practica 2. Realizar un script
#que ejecute los comandos adecuados de grep(sin utilizar sed) egún se indique y realice
#las siguientes tareas sobre el fichero de series.txt

echo "1) Mostrar aquellas lineas que el titulo de libro"
cat series.txt | grep -E '^[0-9]+\.'

echo -e "\n"
echo "2)Eliminar lineas sin informacion revelante"
#cat series.txt | grep -E -v '^$'

echo -e "\n"
echo "3)Mostrar el numero de temporadas"
cat series.txt | grep -E '^[0-9]\ [A-Z]'

