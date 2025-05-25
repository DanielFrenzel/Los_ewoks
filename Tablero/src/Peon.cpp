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
	char colorDestino = cas2.getcolor();

	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	Piezas* fichaOrigen = casillas[filaOrigen][columnaOrigen].getficha();
	Piezas* fichaDestino = casillas[filaDestino][columnaDestino].getficha();

	bool esPrimerMovimiento = this->getMemoria(); // Obtiene la memoria de este peón.

	this->capturaPaso = false; // Resetear cada vez que se comprueba un movimiento

	if (color == 'B') // Para fichas blancas
	{
		
		if (filaDestino == (filaOrigen + 1) && (abs(columnaDestino - columnaOrigen) == 1)
			&& (fichaDestino == nullptr) // importante: debe ser casilla vacía para en passant
			&& (columnaDestino != columnaOrigen) // Asegura que no es avance recto
			&& (casillas[filaOrigen][columnaDestino].getficha() != nullptr) // Que haya un peón en la columna de destino en la fila de origen
			&& (casillas[filaOrigen][columnaDestino].getficha()->getTipo() == PEON) // Que sea un peón
			&& (casillas[filaOrigen][columnaDestino].getficha()->getColor() != this->getColor()) // Que sea un peón enemigo
			&& (filaOrigen == 4)) 
		{
			return PASANTE;
		}


		//  Lógica de Movimiento Normal (1 o 2 casillas) ---
		if (columnaOrigen == columnaDestino && fichaDestino == nullptr) { // Avance recto, a casilla vacía
			if (filaDestino == (filaOrigen + 1)) { // Movimiento de 1 casilla
				this->setMemoria(false); 
				return NORMAL;
			}
			if (esPrimerMovimiento && filaDestino == (filaOrigen + 2)) { // Movimiento de 2 casillas (primer movimiento)
				// Verificar que la casilla intermedia también esté vacía
				if (casillas[filaOrigen + 1][columnaOrigen].getficha() == nullptr) {
					this->setMemoria(false);
					return NORMAL;
				}
			}
		}

		// --- Lógica de Captura Diagonal ---
		if (filaDestino == (filaOrigen + 1) && (abs(columnaDestino - columnaOrigen) == 1) // Captura diagonal
			&& (fichaDestino != nullptr) && (fichaDestino->getColor() == 'N')) // Destino ocupado por pieza negra
		{
			return NORMAL; // Un movimiento de captura también es normal
		}

		// Si ninguna condición anterior se cumple
		return INVALIDO;

	}
	if (color == 'N') // Para fichas negras
	{
		// Lógica de Captura al Paso (En Passant) 
		if (filaDestino == (filaOrigen - 1) && (abs(columnaDestino - columnaOrigen) == 1)
			&& (fichaDestino == nullptr)
			&& (columnaDestino != columnaOrigen)
			&& (casillas[filaOrigen][columnaDestino].getficha() != nullptr)
			&& (casillas[filaOrigen][columnaDestino].getficha()->getTipo() == PEON)
			&& (casillas[filaOrigen][columnaDestino].getficha()->getColor() != this->getColor())
			&& (filaOrigen == 3)) 
		{
			return PASANTE;
		}

		// Lógica de Movimiento Normal (1 o 2 casillas)
		if (columnaOrigen == columnaDestino && fichaDestino == nullptr) { // Avance recto, a casilla vacía
			if (filaDestino == (filaOrigen - 1)) { // Movimiento de 1 casilla
				this->setMemoria(false);
				return NORMAL;
			}
			if (esPrimerMovimiento && filaDestino == (filaOrigen - 2)) { // Movimiento de 2 casillas (primer movimiento)
				// Verificar que la casilla intermedia también esté vacía
				if (casillas[filaOrigen - 1][columnaOrigen].getficha() == nullptr) {
					this->setMemoria(false);
					return NORMAL;
				}
			}
		}

		// Lógica de Captura Diagonal 
		if (filaDestino == (filaOrigen - 1) && (abs(columnaDestino - columnaOrigen) == 1) // Captura diagonal
			&& (fichaDestino != nullptr) && (fichaDestino->getColor() == 'B')) // Destino ocupado por pieza blanca
		{
			this->setMemoria(false);
			return NORMAL; // Un movimiento de captura también es normal
		}

		// Si ninguna condición anterior se cumple
		return INVALIDO;
	}
	return INVALIDO; // Si el color no es ni 'B' ni 'N'
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
			if (this->getMemoria()) { // getMemoria() indica si es el primer movimiento
				int f_avance2 = fila + 2 * direccion_avance;
				// Verificar que la casilla intermedia también esté vacía para el avance de 2 casillas
				if (tablero[f_avance2][col].getficha() == nullptr && tablero[f_avance1][col].getficha() == nullptr) {
					posibles.push_back(const_cast<Casilla*>(&tablero[f_avance2][col]));
				}
			}
		}
	}

	// Capturas diagonales
	const int cols_captura[2] = { col - 1, col + 1 };
	for (int c_cap : cols_captura) {
		if (f_avance1 >= 0 && f_avance1 < 8 && c_cap >= 0 && c_cap < 8) {
			Piezas* ficha_en_destino = tablero[f_avance1][c_cap].getficha();
			if (ficha_en_destino != nullptr && ficha_en_destino->getColor() != this->getColor()) {
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