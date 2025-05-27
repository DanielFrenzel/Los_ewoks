#include "Peon.h"

Peon::Peon(char col)
{
	//Inicializamos los atributos

	color = col;
	memoria = true;
	capturaPaso = false;
	tipo = PEON;
}

State Peon::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();
	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	Piezas* fichaDestino = casillas[filaDestino][columnaDestino].getficha();
	bool esPrimerMovimiento = this->getMemoria();

	this->capturaPaso = false; // Reiniciar para esta comprobaci�n

	State resultadoMovimiento = INVALIDO; // Inicializar a INVALIDO

	if (color == 'B') // Para peones blancos
	{
		// L�gica de Captura al Paso (Blanco)
		if (filaDestino == (filaOrigen + 1) && abs(columnaDestino - columnaOrigen) == 1 &&
			fichaDestino == nullptr && // El destino debe estar vac�o para la captura al paso
			casillas[filaOrigen][columnaDestino].getficha() != nullptr &&
			casillas[filaOrigen][columnaDestino].getficha()->getTipo() == PEON &&
			casillas[filaOrigen][columnaDestino].getficha()->getColor() == 'N' &&
			(filaOrigen == 4)) // El pe�n blanco debe estar en la 5� fila (�ndice 4)
		{
			// La comprobaci�n real de si el pe�n del oponente se movi� 2 casillas justo ahora
			// se har� en la funci�n `mueve` del Tablero con `peon_doble_avance_columna_anterior`.
			// Aqu� solo validamos la forma del movimiento.
			resultadoMovimiento = PASANTE;
		}
		// L�gica de Movimiento Normal (1 o 2 casillas) - Avance recto
		else if (columnaOrigen == columnaDestino && fichaDestino == nullptr) {
			if (filaDestino == (filaOrigen + 1)) { // Mover 1 casilla
				resultadoMovimiento = NORMAL;
			}
			else if (esPrimerMovimiento && filaDestino == (filaOrigen + 2)) { // Mover 2 casillas (primer movimiento)
				// Verificar que la casilla intermedia tambi�n est� vac�a
				if (casillas[filaOrigen + 1][columnaOrigen].getficha() == nullptr) {
					resultadoMovimiento = NORMAL;
				}
			}
		}
		// L�gica de Captura Diagonal (Blanco)
		else if (filaDestino == (filaOrigen + 1) && (abs(columnaDestino - columnaOrigen) == 1) &&
			(fichaDestino != nullptr) && (fichaDestino->getColor() == 'N'))
		{
			resultadoMovimiento = NORMAL; // Un movimiento de captura tambi�n es normal
		}
	}
	else if (color == 'N') // Para peones negros
	{
		// L�gica de Captura al Paso (Negro)
		if (filaDestino == (filaOrigen - 1) && abs(columnaDestino - columnaOrigen) == 1 &&
			fichaDestino == nullptr && // El destino debe estar vac�o para la captura al paso
			casillas[filaOrigen][columnaDestino].getficha() != nullptr &&
			casillas[filaOrigen][columnaDestino].getficha()->getTipo() == PEON &&
			casillas[filaOrigen][columnaDestino].getficha()->getColor() == 'B' &&
			(filaOrigen == 3)) // El pe�n negro debe estar en la 4� fila (�ndice 3)
		{
			// Similar al blanco, el Tablero confirmar� la parte de 'reci�n movido 2 casillas'.
			resultadoMovimiento = PASANTE;
		}
		// L�gica de Movimiento Normal (1 o 2 casillas) - Avance recto
		else if (columnaOrigen == columnaDestino && fichaDestino == nullptr) {
			if (filaDestino == (filaOrigen - 1)) { // Mover 1 casilla
				resultadoMovimiento = NORMAL;
			}
			else if (esPrimerMovimiento && filaDestino == (filaOrigen - 2)) { // Mover 2 casillas (primer movimiento)
				// Verificar que la casilla intermedia tambi�n est� vac�a
				if (casillas[filaOrigen - 1][columnaOrigen].getficha() == nullptr) {
					resultadoMovimiento = NORMAL;
				}
			}
		}
		// L�gica de Captura Diagonal (Negro)
		else if (filaDestino == (filaOrigen - 1) && (abs(columnaDestino - columnaOrigen) == 1) &&
			(fichaDestino != nullptr) && (fichaDestino->getColor() == 'B'))
		{
			resultadoMovimiento = NORMAL; // Un movimiento de captura tambi�n es normal
		}
	}

	// Si el movimiento es v�lido (no es INVALIDO), entonces consume la memoria del pe�n.
	if (resultadoMovimiento != INVALIDO) {
		this->setMemoria(false);
	}

	return resultadoMovimiento;
}

std::vector<Casilla*> Peon::movimientosPosibles(const TABLERO& tablero, Casilla& origen) {
	std::vector<Casilla*> posibles;
	int fila = origen.getfila();
	int col = origen.getcolumna();
	int direccion_avance = (color == 'B') ? 1 : -1; // +1 para blancas, -1 para negras

	// Avance normal (1 casilla)
	int f_avance1 = fila + direccion_avance;
	if (f_avance1 >= 0 && f_avance1 < 8) {
		if (tablero[f_avance1][col].getficha() == nullptr) {
			posibles.push_back(const_cast<Casilla*>(&tablero[f_avance1][col]));

			// Avance inicial de 2 casillas (solo si es el primer movimiento del pe�n)
			if (this->getMemoria()) { // getMemoria() indica si es el primer movimiento
				int f_avance2 = fila + 2 * direccion_avance;
				// Verificar que la casilla intermedia tambi�n est� vac�a para el avance de 2 casillas
				if (f_avance2 >= 0 && f_avance2 < 8 && tablero[f_avance2][col].getficha() == nullptr && tablero[f_avance1][col].getficha() == nullptr) {
					posibles.push_back(const_cast<Casilla*>(&tablero[f_avance2][col]));
				}
			}
		}
	}

	// Capturas diagonales (incluyendo en passant)
	const int cols_captura[2] = { col - 1, col + 1 };
	for (int c_cap : cols_captura) {
		if (f_avance1 >= 0 && f_avance1 < 8 && c_cap >= 0 && c_cap < 8) {
			Piezas* ficha_en_destino_diagonal = tablero[f_avance1][c_cap].getficha();
			Piezas* ficha_adyacente_en_fila_origen = tablero[fila][c_cap].getficha(); // Pe�n a su lado en su misma fila

			// Condici�n para captura normal diagonal
			if (ficha_en_destino_diagonal != nullptr && ficha_en_destino_diagonal->getColor() != this->getColor()) {
				posibles.push_back(const_cast<Casilla*>(&tablero[f_avance1][c_cap]));
			}
			// Condici�n para posible captura al paso (la casilla destino est� vac�a)
			else if (ficha_en_destino_diagonal == nullptr && // La casilla diagonal de destino debe estar vac�a
				ficha_adyacente_en_fila_origen != nullptr && // Debe haber una pieza adyacente en la fila de origen
				ficha_adyacente_en_fila_origen->getTipo() == PEON && // Debe ser un pe�n
				ficha_adyacente_en_fila_origen->getColor() != this->getColor() && // Debe ser un pe�n enemigo
				((color == 'B' && fila == 4) || (color == 'N' && fila == 3)) // Pe�n en la fila correcta para en passant
				)
			{
				// Agregamos la casilla de destino vac�a donde mover�a el pe�n que captura al paso
				posibles.push_back(const_cast<Casilla*>(&tablero[f_avance1][c_cap]));
			}
		}
	}
	return posibles;	
}



void Peon::dibujar(float x, float y)
{
	//Dibujamos los peones

	if (color == 'B')
	{
		Sprite* peonB = Imagen::crearImagen("imagenes/R2D2.png", x, y, tam, tam);
	}
	if (color == 'N')
	{
		Sprite* peonN = Imagen::crearImagen("imagenes/Droide.png", x, y, tam2, tam3);
	}
}

//-------------------------------------------Getter

char Peon::getColor()
{
	return color;
}

bool Peon::getMemoria()
{
	return memoria;
}

void Peon::setMemoria(bool val)
{
	memoria = val;
}


Tipo_pieza Peon::getTipo()
{
	return tipo;
}