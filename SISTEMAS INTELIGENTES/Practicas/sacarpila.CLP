(defrule rpop
	?p <- (pila ?valor $?cola)
	?po <- (pop)
=>
(retract ?p)
(retract ?po)
(assert (pila $?cola))
(printout t "Valor eliminado: " ?valor crlf)
)