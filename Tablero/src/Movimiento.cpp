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
	// 
	//auto fichaPaso = casillas[cas1.getfila()][cas2.getcolumna()].getficha();
	//Peon* peonPaso = dynamic_cast<Peon*>(fichaPaso);
	if (pieza != nullptr)
	{
		if (pieza->comprobarMov(casillas, cas1, cas2))
		{
			/*if (fichaPaso != nullptr)
			{
				casillas[cas2.getfila()][cas2.getcolumna()].setficha(pieza);
				casillas[cas1.getfila()][cas2.getcolumna()].setficha(0);
			}*/
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