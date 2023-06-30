NAME=principal

#
OBJECTS = $(NAME).o funcionesAuxiliares.o Grafo.o Lado.o Vertice.o punto2D.o

#
CPPFLAGS = -c -g -Wall -ansi -O2

INCLUDES = funcionesAuxiliares.hpp Grafo.hpp Lado.hpp Vertice.hpp punto2D.hpp macros.hpp

# Macros predefinidas
#
# $@: nombre del objetivo
# $^: todas las dependencias
# $<: primera dependencia
#

objetivo: $(NAME).exe

#Opciones para NO depurar los asertos
ndebug: CPPFLAGS += -DNDEBUG 
ndebug: objetivo

# Primer objetivo 
$(NAME).exe: $(OBJECTS)
			@echo "Generando " $@
			@g++ $^ -o $@
#
$(NAME).o: $(NAME).cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
funcionesAuxiliares.o: funcionesAuxiliares.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
punto2D.o: punto2D.cpp punto2D.hpp 
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
Vertice.o: Vertice.cpp Vertice.hpp 
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
Lado.o: Lado.cpp Lado.hpp 
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
Grafo.o: Grafo.cpp Grafo.hpp \
						Lado.hpp \
						Vertice.hpp punto2D.hpp
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<





# Generación de la documentación
doc: Doxyfile 
	@echo "Generando la documentación con doxygen"
	@doxygen
  
# Borrado
.PHONY: clean  
clean:
	@echo "Borrando los ficheros superfluos"
	@rm -f $(OBJECTS) *~ 
