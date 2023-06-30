(defrule r-ordenados
	(vectot ?vname $?)
	(exists
		(and
		  (vector ?vname $? ?x ?y $?)
		  (test (> ?y ?x))
		)
	)
=>
	(printout t "+ el vector " ?vname " no esta ordenado" crlf)
)

(deffacts los-datos
	(vector v1 2 2 3 8 9)
	(vector v2 1 3 2 8 7)
)
	