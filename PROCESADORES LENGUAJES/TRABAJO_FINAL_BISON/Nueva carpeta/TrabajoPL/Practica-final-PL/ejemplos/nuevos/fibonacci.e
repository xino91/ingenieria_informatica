#
  Asignatura:    Procesadores de Lenguajes

  Titulación:    Ingeniería Informática
  Especialidad:  Computación
  Curso:         Tercero
  Cuatrimestre:  Segundo

  Departamento:  Informática y Análisis Numérico
  Centro:        Escuela Politécnica Superior de Córdoba
  Universidad de Córdoba
 
  Curso académico: 2018 - 2019

  Nuevo fichero para el intérprete de pseudocódigo en español: ipe.exe
#

_borrar;
_lugar(10,10);
escribir_cadena(' Numero de iteracion de fibonacci:');

_lugar(11,10);
escribir_cadena(' Introduce un numero entero ');
leer(N);

si (N > 0) entonces

	i := 0;
	j := 1;

	para k desde 1 hasta (N-1) paso 1 hacer
		t := i + j;
		i := j;
		j := t;
	fin_para;

	@ Se muestra el resultado

	_lugar(15,10);
	escribir_cadena(' El valor para ');
	escribir(N _div 1);
	escribir_cadena(' iteraciones es ');
	escribir(j);
	escribir_cadena('\n\n');
	
si_no
	_lugar(13,10);
	escribir_cadena(' Error: El valor tiene que ser mayor a 0\n\n');
fin_si

