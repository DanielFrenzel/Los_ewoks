#include "Peon.h"

Peon::Peon(char col)
{
	//Inicializamos los atributos

	color = col;
	memoria = true;
	capturaPaso = false;
	tipo = PEON;
}

State Peon::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2,
	int peon_doble_avance_fila_anterior,
	int peon_doble_avance_columna_anterior)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();
	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	Piezas* fichaDestino = casillas[filaDestino][columnaDestino].getficha();
	bool esPrimerMovimiento = this->getMemoria();

	State resultadoMovimiento = INVALIDO;

	if (color == 'B') // Para peones blancos
	{
		// Lógica de Movimiento Normal (1 o 2 casillas) - Avance recto
		if (columnaOrigen == columnaDestino && fichaDestino == nullptr) {
			if (filaDestino == (filaOrigen + 1)) { // Mover 1 casilla
				resultadoMovimiento = NORMAL;
			}
			else if (esPrimerMovimiento && filaDestino == (filaOrigen + 2)) { // Mover 2 casillas (primer movimiento)
				if (filaOrigen + 1 < 8 && casillas[filaOrigen + 1][columnaOrigen].getficha() == nullptr) {
					resultadoMovimiento = NORMAL;
				}
			}
		}
		// Lógica de Captura Diagonal (Blanco)
		else if (filaDestino == (filaOrigen + 1) && (abs(columnaDestino - columnaOrigen) == 1))
		{
			if ((fichaDestino != nullptr) && (fichaDestino->getColor() == 'N')) {
				resultadoMovimiento = NORMAL; // Un movimiento de captura también es normal
			}
			else if (fichaDestino == nullptr && // Destino vacío para en passant
				casillas[filaOrigen][columnaDestino].getficha() != nullptr && // Peón adyacente
				casillas[filaOrigen][columnaDestino].getficha()->getTipo() == PEON &&
				casillas[filaOrigen][columnaDestino].getficha()->getColor() == 'N' &&
				(filaOrigen == 4) && // Peón blanco en la 5ª fila (índice 4)
				peon_doble_avance_fila_anterior == filaOrigen &&
				peon_doble_avance_columna_anterior == columnaDestino)
			{
				resultadoMovimiento = PASANTE;
			}
		}
	}
	else if (color == 'N') // Para peones negros
	{
		// Lógica de Movimiento Normal (1 o 2 casillas) - Avance recto
		if (columnaOrigen == columnaDestino && fichaDestino == nullptr) {
			if (filaDestino == (filaOrigen - 1)) { // Mover 1 casilla
				resultadoMovimiento = NORMAL;
			}
			else if (esPrimerMovimiento && filaDestino == (filaOrigen - 2)) { // Mover 2 casillas (primer movimiento)
				if (filaOrigen - 1 >= 0 && casillas[filaOrigen - 1][columnaOrigen].getficha() == nullptr) {
					resultadoMovimiento = NORMAL;
				}
			}
		}
		// Lógica de Captura Diagonal (Negro)
		else if (filaDestino == (filaOrigen - 1) && (abs(columnaDestino - columnaOrigen) == 1))
		{
			if ((fichaDestino != nullptr) && (fichaDestino->getColor() == 'B')) {
				resultadoMovimiento = NORMAL; // Un movimiento de captura también es normal
			}
			else if (fichaDestino == nullptr && // Destino vacío para en passant
				casillas[filaOrigen][columnaDestino].getficha() != nullptr && // Peón adyacente
				casillas[filaOrigen][columnaDestino].getficha()->getTipo() == PEON &&
				casillas[filaOrigen][columnaDestino].getficha()->getColor() == 'B' &&
				(filaOrigen == 3) && // Peón negro en la 4ª fila (índice 3)
				peon_doble_avance_fila_anterior == filaOrigen &&
				peon_doble_avance_columna_anterior == columnaDestino)
			{
				resultadoMovimiento = PASANTE;
			}
		}
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

			// Avance inicial de 2 casillas (solo si es el primer movimiento del peón)
			if (this->getMemoria()) {
				int f_avance2 = fila + 2 * direccion_avance;
				// Verificar que la casilla intermedia también esté vacía para el avance de 2 casillas
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
			Piezas* ficha_adyacente_en_fila_origen = tablero[fila][c_cap].getficha();

			// Condición para captura normal diagonal
			if (ficha_en_destino_diagonal != nullptr && ficha_en_destino_diagonal->getColor() != this->getColor()) {
				posibles.push_back(const_cast<Casilla*>(&tablero[f_avance1][c_cap]));
			}
			// Condición para posible captura al paso (la casilla destino está vacía)
			else if (ficha_en_destino_diagonal == nullptr &&
				ficha_adyacente_en_fila_origen != nullptr &&
				ficha_adyacente_en_fila_origen->getTipo() == PEON &&
				ficha_adyacente_en_fila_origen->getColor() != this->getColor() &&
				((color == 'B' && fila == 4) || (color == 'N' && fila == 3)))
			{
				// Agregamos la casilla de destino vacía donde movería el peón que captura al paso
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