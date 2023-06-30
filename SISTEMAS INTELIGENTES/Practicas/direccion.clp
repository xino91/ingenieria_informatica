(defrule comenzar
	?h <- (iniciar_programa)
=>
	(retract ?h)
	printout t "Iniciando.." crlf)
)