#!/bin/bash

#Realizar un script que reciba como argumento el nombre de un directorio y genera un fichero
#fichero.html con el listado de ficheros y/o carpetas de dicho directorio. El script deberá 
#navegar recursivamente por todas las carpetas que haya incluidad en el directorio. Las 
#carpetas deberán representarse en negrita, mientras que los ficheros en tipo de texto normal
#Para agrupar el contenido de cada carpeta utilizaremos una enumeracion(<ul></ul> que estará
#compuesta de un conjunto de elementos (<li><//li>). Para que las carpetas aparezcan en negrita
#puedes utilizar la etiqueta <strong></strong>. El nombre de fichero.html será dir.html, donde
# dir es el nombre de la carpeta


# --------------------------------------------------------------------------
# *** Función recorrerDirectorio ***
# * Función recursiva que recorre los directorios y ficheros que se
#encuentran dentro del directorio pasado por la línea de argumentos.
# * Argumentos que recibe:
# $1: nombre del directorio a analizar
# --------------------------------------------------------------------------
function recorrerDirectorio ()
{
	find "$1" -maxdepth 1 | while read f
	do
		if [ ! -d "$f" ] #Si no es un directorio, es un fichero
		then
			echo -n "<ul>" >> "$FicheroHTML"
			echo -n "<li>$f</li>" >> "$FicheroHTML"
			echo "</ul>" >> "$FicheroHTML"
		else
			if [ "$1" != "$f" ] #Si es un directorio distinto al actual
			then
				echo "<ul>" >> "$FicheroHTML"

				#Escribimos en negrita el nombre del directorio
				echo "<li><strong>$f</strong></li>" >> "$FicheroHTML"
				
				
				#Llamamos recursivamente a la función para escribir el contenido del directorio
				recorrerDirectorio "$f"
				
				echo "</ul>" >> "$FicheroHTML"
			fi
		fi
	done
}

# ----------------------------------
# CONTROL DE ARGUMENTOS
# ----------------------------------

	if [ $# -ne 1 ]
	then
		echo "ERROR: Debe introducir $0 <nombre_directorio>"
		echo -e "\n"
		exit 1
	fi
	
	if [ ! -d "$1" ]
	then
		echo "El argumento <$1> no es un directorio"
		echo -e "\n"
		exit 1
	fi
	
# ----------------------------------
# PROCESAMIENTO
# ----------------------------------

	# readlink -f "$1" --> muestra la ruta completa de $1
	Fichero=$(readlink -f "$1")

	# basename "$Fichero" --> devuelve el nombre del fichero, sin su ruta.
	FicheroHTML="$(basename "$Fichero").html"
	echo "Generando el listado de la carpeta &(basename "$Fichero") sobre el
	fichero $FicheroHTML..."

	# cat > "$FicheroHTML" --> permite introducir todas las líneas que deseemos en FicheroHTML (sobreescribiéndolo si ya
	#existe y creándolo si no) hasta que pulsemos Ctrl+C
	# cat > "$FicheroHTML" << EOF --> permite introducir todas las líneas que deseemos hasta que introduzcamos un carácter
	#concreto, en este caso EOF (fin del fichero HTML)
	
	cat > "$FicheroHTML" << EOF 
	<html>
	<head>
	<title>Listado del directorio $(basename "$Fichero")</title>
	</head>
	<body>
	<h1>Listado del directorio $(basename "$Fichero")</h1>
	EOF

	#Volvemos a llamar a la función recursivamente

	recorrerDirectorio "$Fichero"
	
	# cat >> "$FicheroHTML" << EOF --> añade información a FicheroHTML (sin sobreescribir) hasta introducir EOF
	cat >> "$FicheroHTML" << EOF
	</body>
	</html>
	EOF
echo "Terminado!"
echo -e "\n"
