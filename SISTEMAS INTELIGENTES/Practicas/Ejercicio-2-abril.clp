(defrule ordenar
	?h <- (datos ?nombre $?ini ?x ?y &: (> ?x ?y) $?fin)

=>
	(retract ?h)
	(assert (datos ?nombre $?ini ?y ?x $?fin))
)