#include "Caballo.h"

Caballo::Caballo(char col)
{
	color = col;
	tipo = CABALLO;
}

State Caballo::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2, int peon_doble_avance_fila_anterior, int peon_doble_avance_clomuna_anterior)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	char colorDestino = casillas[cas2.getfila()][cas2.getcolumna()].getcolor();

	if (((abs(filaOrigen - filaDestino) == 2 && abs(columnaOrigen - columnaDestino) == 1)
		|| (abs(columnaOrigen - columnaDestino) == 2 && abs(filaOrigen - filaDestino) == 1)))
	{
		if (colorDestino == 0 || color != colorDestino) return NORMAL;
		else return INVALIDO;

	}
	return INVALIDO;
}

std::vector<Casilla*> Caballo::movimientosPosibles(const TABLERO& tablero, Casilla& origen) {
	std::vector<Casilla*> posibles;
	int fila = origen.getfila();
	int col = origen.getcolumna();

	// Movimientos del caballo (L-shape): {fila_offset, col_offset}
	const int dirs[8][2] = {
		{-2, -1}, {-2, 1},  // 2 arriba, 1 izq/der
		{-1, -2}, {-1, 2},  // 1 arriba, 2 izq/der
		{1, -2},  {1, 2},   // 1 abajo, 2 izq/der
		{2, -1},  {2, 1}    // 2 abajo, 1 izq/der
	};

	for (auto& dir : dirs) {
		int f_destino = fila + dir[0];
		int c_destino = col + dir[1];

		// Verificar si la casilla de destino está dentro del tablero
		if (f_destino >= 0 && f_destino < 8 && c_destino >= 0 && c_destino < 8) {
			Piezas* ficha_en_destino = tablero[f_destino][c_destino].getficha();

			if (ficha_en_destino == nullptr || ficha_en_destino->getColor() != this->getColor()) {
				// Casilla vacía o con pieza del oponente, es un movimiento posible
				posibles.push_back(const_cast<Casilla*>(&tablero[f_destino][c_destino]));
			}
		}
	}
	return posibles;
}

void Caballo::dibujar(float x, float y)
{
	if (color == 'B')
	{
		Sprite* caballoB = Imagen::crearImagen("imagenes/Windu.png", x, y, tam, tam);
	}
	if (color == 'N')
	{
		Sprite* caballoN = Imagen::crearImagen("imagenes/BobaFet.png", x, y, tam, tam);
	}
}

char Caballo::getColor()
{
	return color;
}

Tipo_pieza Caballo::getTipo()
{
	return tipo;
}