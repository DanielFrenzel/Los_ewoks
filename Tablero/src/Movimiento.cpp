#include "Movimiento.h"

Piezas* Movimiento::pieza = nullptr;		//Hay que definir la variable estatica fuera de la clase tambienS

Movimiento::Movimiento()
{
	//Inicializamos los atributos

	pieza = nullptr;
}

void Movimiento::mover(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	//Hacemos los movimientos intercambiando fichas

	if (pieza != nullptr)
	{
		State estadoMovimiento = pieza->comprobarMov(casillas, cas1, cas2);//Importante hacer esto para no ejecutar compMov 2 veces
		if (estadoMovimiento == PASANTE)
		{
			casillas[cas2.getfila()][cas2.getcolumna()].setficha(pieza);
			casillas[cas1.getfila()][cas2.getcolumna()].setficha(nullptr);
			casillas[cas1.getfila()][cas1.getcolumna()].setficha(nullptr);

		}
		if (estadoMovimiento == NORMAL)
		{
			casillas[cas2.getfila()][cas2.getcolumna()].setficha(pieza);
			casillas[cas1.getfila()][cas1.getcolumna()].setficha(nullptr);
		}
	}
}

//-------------------------------------------Setter
void Movimiento::setPieza(Piezas* p)
{
	pieza = p;
}


//Obtener todas las capturas posibles para un jugador dado 
std::vector<std::pair<Casilla*, Casilla*>> Movimiento::obtenerTodasLasCapturasPosibles(const TABLERO& tablero, char colorDelJugador) {
    std::vector<std::pair<Casilla*, Casilla*>> capturas_detectadas;

    for (int r_origen = 0; r_origen < 8; ++r_origen) {
        for (int c_origen = 0; c_origen < 8; ++c_origen) {
            Casilla& origen_casilla = const_cast<Casilla&>(tablero[r_origen][c_origen]);
            Piezas* pieza_en_origen = origen_casilla.getficha();

            if (pieza_en_origen != nullptr && pieza_en_origen->getColor() == colorDelJugador) {
                std::vector<Casilla*> movs_posibles_de_pieza = pieza_en_origen->movimientosPosibles(tablero, origen_casilla);

                for (Casilla* destino_casilla : movs_posibles_de_pieza) {
                    if (destino_casilla != nullptr && destino_casilla->getficha() != nullptr &&
                        destino_casilla->getficha()->getColor() != colorDelJugador) {
                        capturas_detectadas.push_back({ &origen_casilla, destino_casilla });
                    }
                }
            }
        }
    }
    return capturas_detectadas;
}

// Obtener movimientos filtrados para una pieza según la regla de captura 
std::vector<Casilla*> Movimiento::obtenerMovimientosFiltrados(const TABLERO& tablero, Casilla& origen, char turnoActual) {
    std::vector<Casilla*> movimientos_validos;

    Piezas* pieza_seleccionada = origen.getficha();
    if (pieza_seleccionada == nullptr || pieza_seleccionada->getColor() != turnoActual) {
        return movimientos_validos; // No hay pieza o no es del color correcto.
    }

    //Obtener todas las posibles capturas en el tablero para el jugador actual
    std::vector<std::pair<Casilla*, Casilla*>> todas_las_capturas_disponibles =
        Movimiento::obtenerTodasLasCapturasPosibles(tablero, turnoActual);

    // Obtener todos los movimientos posibles (brutos) de la pieza seleccionada
    std::vector<Casilla*> movimientos_brutos_de_pieza = pieza_seleccionada->movimientosPosibles(tablero, origen);

    // Aplicar la regla de captura obligatoria
    if (!todas_las_capturas_disponibles.empty()) {
        // Si hay captura obligatoria, solo movimientos de captura
        for (Casilla* destino : movimientos_brutos_de_pieza) {
            if (destino->getficha() != nullptr && destino->getficha()->getColor() != turnoActual) {
                movimientos_validos.push_back(destino);
            }
        }
    }
    else {
        // Si no hay captura obligatoria, todos los movimientos posibles
        movimientos_validos = movimientos_brutos_de_pieza;
    }
    return movimientos_validos;
}
