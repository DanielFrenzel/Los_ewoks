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
	peon_doble_avance_columna_anterior = -1;
	peon_doble_avance_fila_anterior = -1;
	 
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


	Sprite fondoTablero(rutasFondo[bioma].c_str(), 0, 0, 96, 64);
	fondoTablero.draw();

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
		// Antes de mover, verificar si este movimiento es un avance de peón de dos casillas para marcarlo como susceptible de captura al paso.
		if (fichaOrigen->getTipo() == PEON && abs(fil2 - fil1) == 2) {
			setPeonDobleAvance(fil2, col2); // Este peón acaba de avanzar 2 casillas
		}
		// Si el movimiento es PASANTE, se realiza la captura especial
		if (estadoMovimiento == PASANTE) {
			// El peón se mueve a la casilla detrás del peón capturado
			destino.setficha(fichaOrigen);
			origen.setficha(nullptr); // Vaciar la casilla de origen

			// Eliminar el peón capturado, que está en la misma columna de destino pero en la fila de origen del peón capturado.
			int fila_peon_capturado = (fichaOrigen->getColor() == 'B') ? fil2 - 1 : fil2 + 1;
			// Asegurarse de que el peón a capturar es de hecho un peón del color correcto y que está en la posición esperada para en passant.
			if (casilla[fila_peon_capturado][col2].getficha() != nullptr &&
				casilla[fila_peon_capturado][col2].getficha()->getTipo() == PEON &&
				casilla[fila_peon_capturado][col2].getficha()->getColor() != fichaOrigen->getColor())
			{
				delete casilla[fila_peon_capturado][col2].getficha(); // Libera la memoria
				casilla[fila_peon_capturado][col2].setficha(nullptr); // Quita el peón
			}
			return true;
		}
		// Si es un movimiento NORMAL (avance de 1, 2 o captura diagonal)
		else if (estadoMovimiento == NORMAL) {
			// Si había una ficha en destino, liberamos su memoria antes de sobreescribir
			if (destino.getficha() != nullptr) {
				delete destino.getficha();
			}
			destino.setficha(fichaOrigen); // Mueve la pieza
			origen.setficha(nullptr); // Vaciar la casilla de origen
			return true;
		}
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

	// Delegamos completamente la lógica de filtrado a Movimiento::obtenerMovimientosFiltrados.
	std::vector<Casilla*> movimientos_filtrados_y_validos =
		Movimiento::obtenerMovimientosFiltrados(this->casilla, origen, turnoActual);

	// Ahora, simplemente resaltamos todas las casillas que nos ha devuelto la función filtrada.
	for (Casilla* destino : movimientos_filtrados_y_validos) {
		destino->setResaltada(true);
		casillas_resaltadas.push_back(destino);
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

// Implementación de los nuevos métodos
void Tablero::resetPeonDobleAvance() {
	peon_doble_avance_columna_anterior = -1;
	peon_doble_avance_fila_anterior = -1;
}

void Tablero::setPeonDobleAvance(int fil, int col) {
	peon_doble_avance_fila_anterior = fil;
	peon_doble_avance_columna_anterior = col;
}

void Tablero::set_Bioma(int i)
{
	bioma = i;
}