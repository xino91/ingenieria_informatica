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
#
  ASCII Arts por Veronica Karlsson (https://www.asciiart.eu/people/body-parts/hand-gestures)
#
mov_CPU := random()*100 _div 1;
mov_CPU := mov_CPU _mod 3;
mov_HUMANO := -1;
gana_HUMANO := -1;
_borrar;
_lugar(10, 10);
escribir_cadena('Bienvenido al juego de PIEDRA-PAPEL-TIJERA');
mientras((mov_HUMANO < 0) _o (mov_HUMANO > 2))hacer
	escribir_cadena('\n\n\t\t| PIEDRA = 0 | PAPEL = 1 | TIJERA = 2 |');
	escribir_cadena('\n\n\t\tIntroduce tu movimiento: ');
	leer(mov_HUMANO);
fin_mientras
_borrar;
_lugar(10, 10);
escribir_cadena('\t     [ CPU ]             [ HUMANO ]   \n');
//C++
if(mov_CPU == 0){
	if(mov_HUMANO == 0){
		gana_HUMANO = 2;
		/*
		        _______        _______
		-------'   ____)      (____   '-------
		          (_____)    (_____)
		          (_____)    (_____)
		          (____)      (____)
		-------.__(___)        (___)__.-------
		*/
		escribir_cadena("\t\t        _______        _______\n\t\t-------\'   ____)      (____   \'-------\n\t\t          (_____)    (_____)\n\t\t          (_____)    (_____)\n\t\t          (____)      (____)\n\t\t-------.__(___)        (___)__.-------\n");
	}
	if(mov_HUMANO == 1){
		gana_HUMANO = 1;
		/*
		        _______             _______
		-------'   ____)       ____(____   '---
		          (_____)     (______
		          (_____)    (_______
		          (____)      (_______
		-------.__(___)         (__________.---
		*/
		escribir_cadena("\t\t        _______             _______\n\t\t-------\'   ____)       ____(____   \'---\n\t\t          (_____)     (______\n\t\t          (_____)    (_______\n\t\t          (____)      (_______\n\t\t-------.__(___)         (__________.---\n");
	}
	if(mov_HUMANO == 2){
		gana_HUMANO = 0;
		/*
		        _______             _______
		-------'   ____)       ____(____   '---
		          (_____)     (______
		          (_____)    (__________
		          (____)           (____)
		-------.__(___)             (___)__.---
		*/
		escribir_cadena("\t\t        _______             _______\n\t\t-------\'   ____)       ____(____   \'---\n\t\t          (_____)     (______\n\t\t          (_____)    (__________\n\t\t          (____)           (____)\n\t\t-------.__(___)             (___)__.---\n");
	}
}
if(mov_CPU == 1){
	if(mov_HUMANO == 0){
		gana_HUMANO = 0;
		/*
		    _______            _______
		---'   ____)____      (____   '-------
		          ______)    (_____)
		          _______)   (_____)
		         _______)     (____)
		---.__________)        (___)__.-------
		*/
		escribir_cadena("\t\t    _______            _______\n\t\t---\'   ____)____      (____   \'-------\n\t\t          ______)    (_____)\n\t\t          _______)   (_____)\n\t\t         _______)     (____)\n\t\t---.__________)        (___)__.-------\n");
	}
	if(mov_HUMANO == 1){
		gana_HUMANO = 2;
		/*
		    _______                 _______
		---'   ____)____       ____(____   '---
		          ______)     (______
		          _______)   (_______
		         _______)     (_______
		---.__________)         (__________.---
		*/
		escribir_cadena("\t\t    _______                 _______\n\t\t---\'   ____)____       ____(____   \'---\n\t\t          ______)     (______\n\t\t          _______)   (_______\n\t\t         _______)     (_______\n\t\t---.__________)         (__________.---\n");
	}
	if(mov_HUMANO == 2){
		gana_HUMANO = 1;
		/*
		    _______                 _______
		---'   ____)____       ____(____   '---
		          ______)     (______
		          _______)   (__________
		         _______)          (____)
		---.__________)             (___)__.---
		*/
		escribir_cadena("\t\t    _______                 _______\n\t\t---\'   ____)____       ____(____   \'---\n\t\t          ______)     (______\n\t\t          _______)   (__________\n\t\t         _______)          (____)\n\t\t---.__________)             (___)__.---\n");
	}
}
if(mov_CPU == 2){
	if(mov_HUMANO == 0){
		gana_HUMANO = 1;
		/*
		    _______            _______
		---'   ____)____      (____   '-------
		          ______)    (_____)
		       __________)   (_____)
		      (____)          (____)
		---.__(___)            (___)__.-------
		*/
		escribir_cadena("\t\t    _______            _______\n\t\t---\'   ____)____      (____   \'-------\n\t\t          ______)    (_____)\n\t\t       __________)   (_____)\n\t\t      (____)          (____)\n\t\t---.__(___)            (___)__.-------\n");
	}
	if(mov_HUMANO == 1){
		gana_HUMANO = 0;
		/*
		    _______                 _______
		---'   ____)____       ____(____   '---
		          ______)     (______
		       __________)   (_______
		      (____)          (_______
		---.__(___)             (__________.---
		*/
		escribir_cadena("\t\t    _______                 _______\n\t\t---\'   ____)____       ____(____   \'---\n\t\t          ______)     (______\n\t\t       __________)   (_______\n\t\t      (____)          (_______\n\t\t---.__(___)             (__________.---\n");
	}
	if(mov_HUMANO == 2){
		gana_HUMANO = 2;
		/*
		    _______                 _______
		---'   ____)____       ____(____   '---
		          ______)     (______
		       __________)   (__________
		      (____)               (____)
		---.__(___)                 (___)__.---
		*/
		escribir_cadena("\t\t    _______                 _______\n\t\t---\'   ____)____       ____(____   \'---\n\t\t          ______)     (______\n\t\t       __________)   (__________\n\t\t      (____)               (____)\n\t\t---.__(___)                 (___)__.---\n");
	}
}
si(gana_HUMANO = 0)entonces
	escribir_cadena('\n\nHAS PERDIDO\n\n');
fin_si
si(gana_HUMANO = 1)entonces
	escribir_cadena('\n\nHAS GANADO\n\n');
fin_si
si(gana_HUMANO = 2)entonces
	escribir_cadena('\n\nEMPATE\n\n');
fin_si