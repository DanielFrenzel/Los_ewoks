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

void Tablero::seleccion(int fil, int col, char turnoActual) { 
	deseleccionar(); // Limpiar cualquier resaltado anterior.
	this->f = fil;
	this->c = col;
	if (f >= 0 && f < 8 && c >= 0 && c < 8) {
		casilla[f][c].setResaltada(true); // Resaltar la casilla seleccionada
	}
	actualizarMovimientosPosibles(fil, col, turnoActual); 
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
	
void Tablero::actualizarMovimientosPosibles(int fil, int col, char turnoActual) { 

	Casilla& origen = casilla[fil][col];
	Piezas* pieza_seleccionada = origen.getficha();

	if (pieza_seleccionada == nullptr || pieza_seleccionada->getColor() != turnoActual) {
		return; // No hay pieza del turno actual seleccionada o es inválida para mostrar movimientos.
	}

	// Obtener todas las posibles capturas en el tablero para el turno actual
	std::vector<std::pair<Casilla*, Casilla*>> todas_las_capturas_disponibles =
		Movimiento::obtenerTodasLasCapturasPosibles(this->casilla, turnoActual); 

	// Obtener todos los movimientos posibles (brutos) de la pieza seleccionada
	std::vector<Casilla*> movimientos_brutos_de_pieza = pieza_seleccionada->movimientosPosibles(this->casilla, origen);

	// Aplicar la regla de captura obligatoria y resaltar
	if (!todas_las_capturas_disponibles.empty()) {
		// Si hay al menos una captura disponible en el tablero para este jugador:
		// Solo resaltar movimientos de captura de la pieza seleccionada.
		for (Casilla* destino : movimientos_brutos_de_pieza) {
			// Verificar si este movimiento es una captura (destino ocupado por pieza enemiga)
			if (destino->getficha() != nullptr && destino->getficha()->getColor() != turnoActual) {
				destino->setResaltada(true);
				casillas_resaltadas.push_back(destino);
			}
		}
	}
	else {
		// Si no hay capturas disponibles en el tablero para este jugador:
		// Resaltar todos los movimientos posibles (vacíos o capturas) de la pieza seleccionada.
		for (Casilla* destino : movimientos_brutos_de_pieza) {
			destino->setResaltada(true);
			casillas_resaltadas.push_back(destino);
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

void Tablero::setMouseOver(int fil, int col) {
	// Desactiva el mouse over en la casilla anterior, si es diferente
	if (fil_mouse_over != -1 && (fil_mouse_over != fil || col_mouse_over != col)) {
		casilla[fil_mouse_over][col_mouse_over].setResaltadaMouseOver(false);
	}
	// Activa el mouse over en la nueva casilla
	if (fil >= 0 && fil < 8 && col >= 0 && col < 8) {
		casilla[fil][col].setResaltadaMouseOver(true);
		fil_mouse_over = fil;
		col_mouse_over = col;
	}
}

void Tablero::clearMouseOver() {
	if (fil_mouse_over != -1) {
		casilla[fil_mouse_over][col_mouse_over].setResaltadaMouseOver(false);
		fil_mouse_over = -1;
		col_mouse_over = -1;
	}
}


void Tablero::resaltarCapturasObligatorias(const std::vector<std::pair<Casilla*, Casilla*>>& capturas_list) {
	deseleccionar(); // Limpia cualquier resaltado previo
	// Marca las casillas de origen y destino de cada par de captura
	for (const auto& par : capturas_list) {
		par.first->setResaltada(true);  // La pieza que debe moverse
		par.second->setResaltada(true); // La casilla donde está la pieza a ser capturada
	}
}

Casilla& Tablero::getCasilla(int fil, int col) {
	return casilla[fil][col];
}

// Contar piezas de un color
int Tablero::contarPiezas(char color_a_contar) const {
	int contador = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (casilla[i][j].getficha() != nullptr && casilla[i][j].getficha()->getColor() == color_a_contar) {
				contador++;
			}
		}
	}
	return contador;
}