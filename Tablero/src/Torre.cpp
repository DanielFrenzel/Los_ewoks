#include "Torre.h"

Torre::Torre(char col)
{
	color = col;
}

State Torre::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	char colorDestino = casillas[cas2.getfila()][cas2.getcolumna()].getcolor();

	if (columnaOrigen == columnaDestino && filaOrigen == filaDestino) // si se le pulsa en el mismo sitio no se ueve
	{
		return INVALIDO;
	}
	if (columnaOrigen == columnaDestino)
	{
		int direccion = (filaOrigen < filaDestino) ? 1 : -1;  // comprueba si tiene que sumar o restar
		for (int i = (filaOrigen + direccion); i != filaDestino; i += direccion)
		{
			if (casillas[i][columnaOrigen].getficha() != 0)
				return INVALIDO;

		}
		return comer(color, colorDestino);

	}
	if (filaOrigen == filaDestino)
	{
		int direccion = (columnaOrigen < columnaDestino) ? 1 : -1;  // comprueba si tiene que sumar o restar
		for (int i = (columnaOrigen + direccion); i != columnaDestino; i += direccion)
		{
			if (casillas[filaOrigen][i].getficha() != 0)
				return INVALIDO; // obstáculo
		}
		return comer(color, colorDestino);
	}
	else return INVALIDO;
}

std::vector<Casilla*> Torre::movimientosPosibles( const TABLERO& tablero,  Casilla& origen) {
	std::vector<Casilla*> posibles;
	int fila = origen.getfila();
	int col = origen.getcolumna();

	const int dirs[4][2] = {
		{1, 0}, {-1, 0},  // vertical (abajo, arriba)
		{0, 1}, {0, -1}   // horizontal (derecha, izquierda)
	};

	for (auto& dir : dirs) {
		int f = fila + dir[0];
		int c = col + dir[1];	
		while (f >= 0 && f < 8 && c >= 0 && c < 8) {
			Piezas* ficha = tablero[f][c].getficha();
			if (ficha == nullptr) {
				posibles.push_back(const_cast<Casilla*>(&tablero[f][c]));
			}
			else {
				if (ficha->getColor() != this->getColor()) {
					posibles.push_back(const_cast<Casilla*>(&tablero[f][c]));  // Comer
				}
				break;  // Obstrucción encontrada
			}
			f += dir[0];
			c += dir[1];
		}
	}

	return posibles;
}




void Torre::dibujar(float x, float y)
{
	if (color == 'B')
	{
		Sprite* torreB = Imagen::crearImagen("imagenes/Chewy.png", x, y, tam, tam);
	}
	if (color == 'N')
	{
		Sprite* torreN = Imagen::crearImagen("imagenes/Superdroide.png", x, y, tam7, tam8);
	}
}

char Torre::getColor()
{
	return color;
}

Tipo_pieza Torre::getTipo()
{
	return tipo;
}