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
	promocion_pendiente = false;
	promocion_fila_pendiente = -1;
	promocion_columna_pendiente = -1;
	turnoActual = 'B';
	 
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

/*Tablero::~Tablero() {
	// Itera por todas las casillas del tablero
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			// Si hay una ficha en la casilla, la elimina (libera la memoria)
			if (casilla[i][j].getficha() != nullptr) {
				delete casilla[i][j].getficha();
			}
		}
	}
}*/

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

bool Tablero::mueve(int fil1, int col1, int fil2, int col2, char turnoActual, int peon_doble_avance_fila_anterior_param, int peon_doble_avance_columna_anterior_param)
{
	
	Casilla& origen = casilla[fil1][col1];
	Casilla& destino = casilla[fil2][col2];
	Piezas* fichaOrigen = origen.getficha();

	if (fichaOrigen == nullptr || fichaOrigen->getColor() != turnoActual) {
		return false;
	}

	// Delegar la comprobación del movimiento específico de la pieza
	State estadoMovimiento = fichaOrigen->comprobarMov(casilla, origen, destino,
		peon_doble_avance_fila_anterior_param,
		peon_doble_avance_columna_anterior_param);

	if (estadoMovimiento == INVALIDO) {
		resetPeonDobleAvance();
		return false;
	}
	else {
		// Si el movimiento es válido, actualiza la memoria de la pieza (primer movimiento)
		fichaOrigen->setMemoria(false);

		// Manejo específico de la captura al paso 
		if (estadoMovimiento == PASANTE) {
			destino.setficha(fichaOrigen);
			origen.setficha(nullptr); // Vaciar la casilla de origen

			int fila_peon_capturado = fil1; // El peón capturado está en la fila de origen del atacante
			int col_peon_capturado = col2;  // Y en la columna de destino del atacante

			if (fila_peon_capturado >= 0 && fila_peon_capturado < 8 &&
				col_peon_capturado >= 0 && col_peon_capturado < 8)
			{
				Casilla& casilla_peon_capturado = casilla[fila_peon_capturado][col_peon_capturado];
				Piezas* peon_a_eliminar = casilla_peon_capturado.getficha();

				if (peon_a_eliminar != nullptr &&
					peon_a_eliminar->getTipo() == PEON &&
					peon_a_eliminar->getColor() != fichaOrigen->getColor())
				{
					delete peon_a_eliminar; // Libera la memoria
					casilla_peon_capturado.setficha(nullptr); // Quita el peón
				}
			}
			// Después de un movimiento exitoso (incluido al paso), reseteamos el doble avance.Esto es para que la oportunidad de al paso solo dure un turno.
			resetPeonDobleAvance(); 
			return true;
		}
		// Si es un movimiento NORMAL (avance de 1, 2 o captura diagonal)
		else if (estadoMovimiento == NORMAL) {
			if (destino.getficha() != nullptr) {
				delete destino.getficha();
			}
			destino.setficha(fichaOrigen);
			origen.setficha(nullptr);

			//Detección de promoción de peón
			if (fichaOrigen->getTipo() == PEON && (fil2 == 0 || fil2 == 7)) {
				promocion_pendiente = true;
				promocion_fila_pendiente = fil2;
				promocion_columna_pendiente = col2;
				return true; // Movimiento exitoso, pero con promoción pendiente.
			}

			// Si la pieza movida es un peón y realizó un avance de 2 casillas, actualiza la información
			if (fichaOrigen->getTipo() == PEON && abs(fil2 - fil1) == 2) {
				setPeonDobleAvance(fil2, col2); // Este peón acaba de avanzar 2 casillas
			}
			else {
				// Si no fue un doble avance, reseteamos el registro para 'al paso'.
				resetPeonDobleAvance();
			}
			return true;
		}
	}
	// Si por alguna razón no se gestionó el movimiento 
	resetPeonDobleAvance();
	return false;
	
}


void Tablero::seleccion(int fil, int col, char turnoActual) { 
	deseleccionar(); // Limpiar cualquier resaltado anterior.

	Casilla& casilla_seleccionada_actual = casilla[fil][col];
	Piezas* pieza_en_casilla_seleccionada = casilla_seleccionada_actual.getficha();

	// Verificar si la pieza seleccionada pertenece al jugador actual.
	if (pieza_en_casilla_seleccionada == nullptr || pieza_en_casilla_seleccionada->getColor() != turnoActual) {
		return; // No hay pieza del turno actual o es inválida para seleccionar.
	}

	// Obtener todas posibles capturas en el tablero para el jugador actual.
	std::vector<std::pair<Casilla*, Casilla*>> todas_las_capturas_disponibles =
		Movimiento::obtenerTodasLasCapturasPosibles(this->casilla, turnoActual,peon_doble_avance_fila_anterior,peon_doble_avance_columna_anterior);

	//  Aplicar la regla de captura obligatoria estricta a la selección de la pieza.
	if (!todas_las_capturas_disponibles.empty()) {
		// Hay capturas obligatorias en el tablero.Solo queremos permitir la selección de una pieza que puede realizar esas capturas.
		bool pieza_seleccionada_puede_realizar_captura_obligatoria = false;
		for (const auto& captura_par : todas_las_capturas_disponibles) {
			if (captura_par.first == &casilla_seleccionada_actual) {
				pieza_seleccionada_puede_realizar_captura_obligatoria = true;
				break;
			}
		}

		if (!pieza_seleccionada_puede_realizar_captura_obligatoria) {
			// Si hay capturas obligatorias, pero la pieza seleccionada no es una de las que puede capturar, no permitimos la selección.
			return;
		}
	}

	// Si llegamos hasta aquí, la selección es válida.
	this->f = fil;
	this->c = col;
	if (f >= 0 && f < 8 && c >= 0 && c < 8) {
		casilla[f][c].setResaltada(true); // Resaltar la casilla seleccionada
	}

	// Finalmente, actualizamos y resaltamos los movimientos posibles para la pieza seleccionada.
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
		return;
	}

	// Delegamos completamente la lógica de filtrado a Movimiento::obtenerMovimientosFiltrados.
	std::vector<Casilla*> movimientos_filtrados_y_validos =
		Movimiento::obtenerMovimientosFiltrados(this->casilla, origen, turnoActual,peon_doble_avance_fila_anterior,peon_doble_avance_columna_anterior);

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

void Tablero::promocionarPeon(int fila, int columna, char tipo_pieza_elegida, char color_peon) {
	if (fila < 0 || fila >= 8 || columna < 0 || columna >= 8) return;

	Piezas* peon_a_promocionar = casilla[fila][columna].getficha();
	if (peon_a_promocionar == nullptr || peon_a_promocionar->getTipo() != PEON || peon_a_promocionar->getColor() != color_peon) {
		// Puede que se intente promocionar una casilla incorrecta
		return;
	}

	delete peon_a_promocionar; // Libera la memoria del peón actual
	casilla[fila][columna].setficha(nullptr); // Vaciar la casilla

	Piezas* nueva_pieza = nullptr;
	switch (tipo_pieza_elegida) {
	case 'A': nueva_pieza = new Alfil(color_peon); break;
	case 'C': nueva_pieza = new Caballo(color_peon); break;
	case 'R': nueva_pieza = new Reina(color_peon); break;
	case 'T': nueva_pieza = new Torre(color_peon); break;
	//default: nueva_pieza = new Reina(color_peon); // Por defecto si hay un error
	}

	casilla[fila][columna].setficha(nueva_pieza);

	resetPromocionPendiente(); // Resetear el flag de promoción
}

bool Tablero::tieneMovimientosPosibles(char colorJugador) const {
	// Iterar por todas las casillas del tablero
	for (int fila = 0; fila < 8; ++fila) {
		for (int col = 0; col < 8; ++col) {
			const Casilla& casilla_origen = casilla[fila][col];
			Piezas* pieza = casilla_origen.getficha();

			// Si hay una pieza en esta casilla y es del color del jugador actual
			if (pieza != nullptr && pieza->getColor() == colorJugador) {
				// Obtener todos los movimientos legales (incluyendo capturas obligatorias). Se usan los getters del tablero para el peón de doble avance si es necesario.
				std::vector<Casilla*> movimientos_legales = Movimiento::obtenerMovimientosFiltrados(casilla,const_cast<Casilla&>(casilla_origen), colorJugador,peon_doble_avance_fila_anterior,peon_doble_avance_columna_anterior 
				);
				if (!movimientos_legales.empty()) {
					return true; // Se encontró al menos un movimiento posible para esta pieza
				}
			}
		}
	}
	return false; // No se encontraron movimientos posibles para ninguna pieza del jugador
}