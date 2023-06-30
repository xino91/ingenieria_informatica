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


n_secreto := random()*100 _div 1;
limite_it := 8;
numero:= -1;

_borrar;
_lugar(10,10);
escribir_cadena(' Bienvenido al juego de la patata caliente');

mientras((numero <> n_secreto) _y (limite_it > 0)) hacer

	escribir_cadena('\n\n\t\tIntroduce un número: ');
	leer(numero);

	si (numero > n_secreto) entonces
		escribir_cadena('\n\t\tMás bajo\n');
	fin_si

	si (numero < n_secreto) entonces
		escribir_cadena('\n\t\tMás alto\n');
	fin_si

	limite_it := limite_it - 1;
fin_mientras

_borrar;
_lugar(10,10);

si (numero = n_secreto) entonces
	escribir_cadena('Enhorabuena has ganado!\n\n');
si_no
	escribir_cadena('\n\n\tLa patata ha explotado, vuelve a intentarlo\n\n');
fin_si

