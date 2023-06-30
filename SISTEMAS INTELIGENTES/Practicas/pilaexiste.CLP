(defrule r-inicializar-pila
	"Crear hecho pila si no existe"
	(not pila $?))
=>
(assert (pila))
)