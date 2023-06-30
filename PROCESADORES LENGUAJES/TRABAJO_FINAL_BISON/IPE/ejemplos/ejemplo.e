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

  Fichero de ejemplo nº 5 para el intérprete de pseudocódigo en español: ipe.exe
#

@ Bienvenida

_borrar;

_lugar(10,10);

escribir_cadena('Introduce tu DNI --> ');

leer_cadena(nombre);

_borrar;
_lugar(10,10);

escribir_cadena(' Bienvenido/a << ');

escribir_cadena('>> Acaba de iniciar su servicio de biblioteca');

_lugar(40,10);
escribir_cadena('Pulsa una tecla para continuar');
leer_cadena(pausa);

libro1:='El maravilloso mundo de la informática';
cant1:=5;

libro2:='No Pierdas el tiempo, crea tu propio lenguaje';
cant2:=8;

libro3:='El Capitán Alatriste';
cant3:=1;


repetir 

 @ Opciones disponibles

 _borrar;

 _lugar(10,10);
 escribir_cadena(' Ver Libros Disponibles-----------> 1 ');

 _lugar(11,10);
 escribir_cadena(' Sacar Libro De la Biblioteca ----> 2 ');

 _lugar(12,10);
 escribir_cadena(' Finalizar -----------------------> 0 ');

 _lugar(15,10);
 escribir_cadena(' Elige una opcion ');

 leer(opcion);

 _borrar;

 si (opcion  = 0)
    entonces  
        _lugar(10,10);
       
        escribir_cadena('Gracias por usar nuestro Servicio de biblioteca ');

   si_no
       @ Ver libros disponibles
	si (opcion = 1)
   	    entonces
                _lugar(10,10);
		escribir_cadena(' Libros Disponibles ');

                _lugar(11,10);
		si ( cant1 <> 0 )
			entonces
				escribir_cadena(libro1);
		fin_si
		_lugar(12,10);
        	si ( cant2 <> 0 )
			entonces
				escribir_cadena(libro2);
		fin_si
		_lugar(13,10);
		
        	si ( cant3 <> 0 )
			entonces
				escribir_cadena(libro3);
		fin_si

   	@Servicio de sacar libro
	si_no 
		si (opcion = 2)
			entonces
				 _lugar(10,10);
				escribir_cadena(' Libros Disponibles , Seleccione el deseado:');
					

                		_lugar(11,10);
				si ( cant1 <> 0 )
					entonces
						escribir_cadena(libro1);
						_lugar(12,12);
						escribir_cadena('-------->1');
				fin_si
				_lugar(14,10);
        			si ( cant2 <> 0 )
					entonces
						escribir_cadena(libro2);
						_lugar(15,12);
						escribir_cadena('-------->2');
				fin_si
				_lugar(17,10);
		
        			si ( cant3 <> 0 )
					entonces
						escribir_cadena(libro3);
						_lugar(18,12);
						escribir_cadena('-------->3');
				fin_si
					_lugar(20,10);
					escribir_cadena('Inserte la opcion');
					leer(opcion1);
			
                  		@ Se ordenan los números
				si (opcion1 = 1)
					entonces
						cant1:=cant1-1;
					si_no
						si(opcion1=2)
							entonces
								cant2:=cant2-1;
							si_no
								si(opcion1=3)
									entonces
										cant3:=cant3-1;
									si_no
										_lugar(21,10);
			    							escribir_cadena(' Opcion incorrecta ');
								fin_si
						fin_si
				fin_si
 @ Resto de opciones
 		si_no  
			_lugar(15,10);
		    	escribir_cadena(' Opcion incorrecta ');

 		fin_si
                   

  	fin_si                          
fin_si
 _lugar(40,10); 
 escribir_cadena('\n Pulse una tecla para continuar --> ');
 leer_cadena(pausa);
 
hasta (opcion = 0);             

@ Despedida final

_borrar;
_lugar(10,10);
escribir_cadena('El programa ha concluido');
