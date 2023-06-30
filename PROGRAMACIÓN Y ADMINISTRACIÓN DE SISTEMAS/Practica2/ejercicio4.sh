#!/bin/bash
# 4) A partir de un fichero de texto con una serie de direcciones IP(IPs.txt), haz un script que
#sea capaz de hacer un ping a cada una de las direcciones y de imprimirlas en orden según lo que
#tardan en contestar. El nombre del fichero con las IPs se pasará como argumento a la linea de
#comandos. El segundo argumento será el número de segundo que deben pasar antes de dar por 
#muerto al servidor. Deberás investigar sobre el comando ping para configurlo de forma que se 
#mande un solo ping. Si la máquina a la que envía el ping no está activa, el comando ping 
#devolverá un código de error distinto de cero al SO.

if [ $# != 2 ]
then
	echo "Numero de argumentos incorrecto"
	echo "Ejecuta ./ejercicio4.sh IPs.txt <int numero segundos>"
fi

mktemp -d /tmp/auxiliar.txtXXXX	#Este comando creará un archivo temporal, el XXXX será 
#reemplazado con una serie aleatorio de numeros y letras. Siempre que se ejecuta se asegura 
# de que el archivo es unico, es decir siempre creará una archivo vacio


while read IP
do
	ping -c 1 -W $2 IP | sed -r -n e 's/.*time=(.*)\ ms/La IP '$IP' respondió en \1 milisegundos/p' >> /tmp/auxiliar.txt
	
done < $1


sort -n -t ' ' -k 6 /tmp/auxiliar.txt

while read IP
do
	if ping -c 1 -W $2 $IP > /tmp/auxiliar.txt
	then
		echo "No hacer nada" > /tmp/auxiliar.txt
	else
		echo "La IP $IP no respondió tras $2 segundos"
	fi

done < $1

rm /tmp/auxiliar.txt  #Elimina el archivo temporal
