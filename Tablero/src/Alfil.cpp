#include "Alfil.h"


Alfil::Alfil(char col)
{
	color = col;
	tipo = ALFIL;
}

State Alfil::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	auto fichaDestino = casillas[cas2.getfila()][cas2.getcolumna()].getficha();

	char colorDestino = casillas[cas2.getfila()][cas2.getcolumna()].getcolor();

	int direccionFil = (filaOrigen < filaDestino) ? 1 : -1;
	int direccionCol = (columnaOrigen < columnaDestino) ? 1 : -1;

	if (abs(filaOrigen - filaDestino) == abs(columnaOrigen - columnaDestino))
	{
		int i = filaOrigen + direccionFil;
		int j = columnaOrigen + direccionCol;

		while (i != filaDestino && j != columnaDestino)
		{
			if (casillas[i][j].getficha() != 0)
				return INVALIDO;
			i += direccionFil;
			j += direccionCol;
		}
		if (fichaDestino == 0)
		{
			return NORMAL;
		}
		if (color != colorDestino)
		{
			return NORMAL;
		}
		else
			return INVALIDO;

	}
	return INVALIDO;
}

std::vector<Casilla*> Alfil::movimientosPosibles(const TABLERO& tablero, Casilla& origen) {
	std::vector<Casilla*> posibles;
	int fila = origen.getfila();
	int col = origen.getcolumna();

	// Direcciones diagonales: {fila_offset, col_offset}
	const int dirs[4][2] = {
		{-1, -1}, {-1, 1},  // Arriba-izquierda, Arriba-derecha
		{1, -1},  {1, 1}    // Abajo-izquierda, Abajo-derecha
	};

	for (auto& dir : dirs) {
		int f = fila + dir[0];
		int c = col + dir[1];

		// Recorrer la diagonal hasta el borde del tablero o una pieza
		while (f >= 0 && f < 8 && c >= 0 && c < 8) {
			Piezas* ficha_en_destino = tablero[f][c].getficha();

			if (ficha_en_destino == nullptr) {
				// Casilla vacía, es un movimiento posible
				posibles.push_back(const_cast<Casilla*>(&tablero[f][c]));
			}
			else {
				// Casilla ocupada
				if (ficha_en_destino->getColor() != this->getColor()) {
					// Es una pieza del oponente, se puede capturar
					posibles.push_back(const_cast<Casilla*>(&tablero[f][c]));
				}
				// Si es del mismo color o se captura, no se puede seguir avanzando en esta dirección
				break;
			}
			f += dir[0];
			c += dir[1];
		}
	}
	return posibles;
}

void Alfil::dibujar(float x, float y)
{
	if (color == 'B')
	{
		Sprite* alfilB = Imagen::crearImagen("imagenes/Yoda.png", x, y, tam, tam);
	}
	if (color == 'N')
	{
		Sprite* alfilN = Imagen::crearImagen("imagenes/Doku_1.png", x, y, tam9, tam10);
	}
}


char Alfil::getColor()
{
	return color;
}

Tipo_pieza Alfil::getTipo()
{
	return tipo;
}