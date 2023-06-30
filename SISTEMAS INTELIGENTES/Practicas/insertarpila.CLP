(defrule rpush
	?p  <- (pila $?valores)
	?pu <- (push ?x)
=>
(retract ?p)
(retract ?pu)
(assert (pila ?x $?valores))
(printout t "valor insertado: " ?x crlf)
) 