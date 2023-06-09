(deftemplate persona
	(slot nombre (type STRING) (default ?NONE))
	(slot apellidos (type STRING) (default ?NONE))
	(slot altura (type FLOAT) (default 1.65)
	   (range 0.1 3.0))
	(slot edad (type INTEGER) (default 20)
	   (range 1 100))
	(slot color-ojos (type SYMBOL) (default negro)
	  (allowed-symbols negro gris marron verde))
)

(deffacts elenco "Actores y Actrices"
	(persona
	   (nombre "Carlos") (apellidos "Lopez Salgado")
	   (edad 25) (color-ojos gris)
	   (altura 1.72)
	)
	   ;(nombre "Antonio" (apellidos "Ariza Garcia")
	   (edad 26) (color-ojos marron)
	   (altura 1.76)
	)
	   ;(nombre "Jose" (apellidos "Martinez Lopez")
	   (edad 24) (color-ojos negro)
	   (altura 1.87)
 	)
)