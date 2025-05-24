#include "Tablero.h"

Tablero::Tablero()																//Constructor
{
	//Inicializamos los atributos
	f = -1;
	c = -1;

	x = 0;
	y = 0;
	tam_x = 96;
	tam_y = 64;
	
	
	 
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			casilla[i][j].setPosicion(i, j);									//Pasamos la posicion de cada casilla a la propia casilla
			casilla[i][j].setResaltada(false);

			if (i == 0)															//Primera fila de blancas
			{
				if (j == 0 || j == 7)//Torre
				{
					casilla[i][j].setficha(new Torre('B'));
				}

				else if (j == 1 || j == 6)//Caballo
				{
					casilla[i][j].setficha(new Caballo('B'));
					
				}

				else if (j == 2 || j == 5)//Alfil
				{
					casilla[i][j].setficha(new Alfil('B'));
					
				}

				else if (j == 3)//Reina
				{
					casilla[i][j].setficha(new Reina('B'));
					
				}

				else if (j == 4)//Rey
				{
					casilla[i][j].setficha(new Rey('B'));
					
				}
			}

			else if (i == 1)													//Segunda fila de blancas
			{
				casilla[i][j].setficha(new Peon('B'));
			}

			else if (i == 6)													//Segunda fila de negras
			{
				casilla[i][j].setficha(new Peon('N'));
			}

			else if (i == 7)													//Primera fila de negras
			{
				if (j == 0 || j == 7)//Torre
				{
					casilla[i][j].setficha(new Torre('N'));
					
				}

				if (j == 1 || j == 6)//Caballo
				{
					casilla[i][j].setficha(new Caballo('N'));
					
				}

				if (j == 2 || j == 5)//Alfil
				{
					casilla[i][j].setficha(new Alfil('N'));
					
				}

				if (j == 3)//Reina
				{
					casilla[i][j].setficha(new Reina('N'));
					
				}

				if (j == 4)//Rey
				{
					casilla[i][j].setficha(new Rey('N'));
					
				}
			}

			else//Nada
			{
				casilla[i][j].setficha(nullptr);
			}
		}
	}

}

Tablero::~Tablero() {

}


void Tablero::dibuja()															//Dibujamos las piezas y el tablero
{

	for (int i = 0;i < 8;i++)													//Imprime piezas
	{
		for (int j = 0;j < 8;j++)
		{
			casilla[i][j].dibuja();
		}
	}


	fondo_tablero_sprite.draw();

}


bool Tablero::mueve(int fil1, int col1, int fil2, int col2, char turnoActual)
{
	Casilla& origen = casilla[fil1][col1];
	Casilla& destino = casilla[fil2][col2];
	Piezas* fichaOrigen = origen.getficha();

	// Validar que hay una pieza en la casilla de origen
	if (fichaOrigen == nullptr) {
		
		return false;
	}

	// Validar que la pieza en origen pertenece al turno actual
	if (fichaOrigen->getColor() != turnoActual) {
		
		return false;
	}

	// Validar que la casilla de destino no está ocupada por una pieza del mismo color
	Piezas* fichaDestino = destino.getficha();
	if (fichaDestino != nullptr && fichaDestino->getColor() == turnoActual) {
		
		return false;
	}

	// Delegar la comprobación del movimiento específico de la pieza
	State estadoMovimiento = fichaOrigen->comprobarMov(casilla, origen, destino);

	if (estadoMovimiento == INVALIDO) {
		
		return false;
	}
	
	else {
		
		destino.setficha(fichaOrigen);
		origen.setficha(nullptr); // Vaciar la casilla de origen

		
		if (estadoMovimiento == PASANTE) {
			 if (fichaOrigen->getTipo() == PEON) {
			    int fila_peon_capturado = (fichaOrigen->getColor() == 'B') ? fil2 - 1 : fil2 + 1;
			    casilla[fila_peon_capturado][col2].setficha(nullptr);
			 }
			
		}
		
		return true;
	}
}


void Tablero::seleccion(int fil, int col) {
	deseleccionar(); // Esto limpia la selección anterior y los movimientos posibles.

	// Marca la nueva casilla como seleccionada 
	this->f = fil;
	this->c = col;
	// Establece que esta casilla específica debe resaltarse
	if (f >= 0 && f < 8 && c >= 0 && c < 8) { // Asegurarse de que sea una casilla válida
		casilla[f][c].setResaltada(true);
	}

	// Actualiza y resalta los movimientos posibles para la pieza en (fil, col)
	actualizarMovimientosPosibles(fil, col);
}

void Tablero::deseleccionar() {
	// Reinicia las variables de la casilla seleccionada en Tablero
	f = -1;
	c = -1;

	// Itera sobre todas las casillas del tablero y las marca como no resaltadas
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			casilla[i][j].setResaltada(false);
		}
	}
	// También limpia la lista interna de casillas_resaltadas
	casillas_resaltadas.clear();
}
	

void Tablero::actualizarMovimientosPosibles(int fil, int col) {
	// Limpiar la lista anterior de movimientos posibles.
	casillas_resaltadas.clear(); // Esto limpia el vector, pero no desresalta las casillas visualmente.

	// Si hay una pieza en la casilla seleccionada, obtener sus movimientos posibles
	if (fil >= 0 && fil < 8 && col >= 0 && col < 8) {
		Casilla& origen = casilla[fil][col];
		if (origen.getficha() != nullptr) {
			// Obtener la lista de Casilla* que son movimientos posibles
			std::vector<Casilla*> posibles_movs = Movimiento::obtenerMovimientosPosibles(this->casilla, origen);

			// Iterar sobre los movimientos posibles y marcarlos para resaltado
			for (Casilla* c_posible : posibles_movs) {
				if (c_posible != nullptr) {
					c_posible->setResaltada(true); 
					casillas_resaltadas.push_back(c_posible);
				}
			}
		}
	}
}

char Tablero::getPiezaColor(int fila, int columna) const {
	if (fila < 0 || fila >= 8 || columna < 0 || columna >= 8) {
		return ' '; // Coordenadas fuera de rango
	}
	Piezas* pieza = casilla[fila][columna].getficha();
	if (pieza != nullptr) {
		return pieza->getColor();
	}
	return ' '; // Casilla vacía
}

