(defrule rordenar
	?h <-(dato ?x)
	(not (dato ?y &: (< ?y ?x)))
=>
(retract ?h) 
(printout t ?x crlf)
)

(deffacts los-datos
	(dato 6)
	(dato 1.3)
	(dato 2)
	(dato -1)
	(dato 5.3)
)