#include "Rey.h"

Rey::Rey(char col)
{
	color = col;
}

State Rey::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	int df = abs(filaOrigen - filaDestino);
	int dc = abs(columnaOrigen - columnaDestino);

	char colorDestino = casillas[cas2.getfila()][cas2.getcolumna()].getcolor();

	if (((df <= 1 && dc <= 1) && !(df == 0 && dc == 0)) && colorDestino != color)
	{
		return NORMAL;
	}
	else return INVALIDO;
}

std::vector<Casilla*> Rey::movimientosPosibles(const TABLERO& tablero, Casilla& origen) {
    std::vector<Casilla*> posibles;
    int fila = origen.getfila();
    int col = origen.getcolumna();

    // Todas las 8 direcciones posibles (1 casilla)
    const int dirs[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},  // Arriba
        {0, -1},            {0, 1},   // Lados
        {1, -1},  {1, 0},  {1, 1}    // Abajo
    };

    for (auto& dir : dirs) {
        int f_destino = fila + dir[0];
        int c_destino = col + dir[1];

        // Verificar límites del tablero
        if (f_destino >= 0 && f_destino < 8 && c_destino >= 0 && c_destino < 8) {
            Piezas* ficha_en_destino = tablero[f_destino][c_destino].getficha();

            if (ficha_en_destino == nullptr || ficha_en_destino->getColor() != this->getColor()) {
                // Casilla vacía o con pieza del oponente
                posibles.push_back(const_cast<Casilla*>(&tablero[f_destino][c_destino]));
            }
        }
    }
    
    return posibles;
}



void Rey::dibujar(float x, float y)
{
	if (color == 'B')
	{
		Sprite* reyB = Imagen::crearImagen("imagenes/Obiwan.png", x, y, tam, tam);
	}
	else if (color == 'N')
	{
		Sprite* reyN = Imagen::crearImagen("imagenes/Palpatine.png", x, y, tam, tam);
	}
}

char Rey::getColor()
{
	return color;
}

Tipo_pieza Rey::getTipo()
{
	return tipo;
}