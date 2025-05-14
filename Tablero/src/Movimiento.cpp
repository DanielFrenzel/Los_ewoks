#include "Movimiento.h"

Piezas* Movimiento::pieza = nullptr;		//Hay que definir la variable estatica fuera de la clase tambienS

Movimiento::Movimiento()
{
	//Inicializamos los atributos

	pieza = nullptr;
}

void Movimiento::mover(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	//Hacemos los movimientos intercambiando fichas

	if (pieza != nullptr)
	{
		State estadoMovimiento = pieza->comprobarMov(casillas, cas1, cas2);//Importante hacer esto para no ejecutar compMov 2 veces
		if (estadoMovimiento == PASANTE)
		{
			casillas[cas2.getfila()][cas2.getcolumna()].setficha(pieza);
			casillas[cas1.getfila()][cas2.getcolumna()].setficha(nullptr);
			casillas[cas1.getfila()][cas1.getcolumna()].setficha(nullptr);

		}
		if (estadoMovimiento == NORMAL)
		{
			casillas[cas2.getfila()][cas2.getcolumna()].setficha(pieza);
			casillas[cas1.getfila()][cas1.getcolumna()].setficha(nullptr);
		}
	}
}

//-------------------------------------------Setter
void Movimiento::setPieza(Piezas* p)
{
	pieza = p;
}