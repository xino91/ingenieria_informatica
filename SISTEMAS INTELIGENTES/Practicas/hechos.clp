(deftemplate persona
	(slot nombre) (slot edad))
(deftemplate casa
	(slot calle) (slot numero))
(deftemplate compra-vecta
	(slot comprador) (slot vendedor)
	(slot casa)
	(slot precio)
	(slot fecha)
)