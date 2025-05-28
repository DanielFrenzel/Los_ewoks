#include "Movimiento.h"

Piezas* Movimiento::pieza = nullptr;		//Hay que definir la variable estatica fuera de la clase tambienS

Movimiento::Movimiento()
{
	//Inicializamos los atributos

	pieza = nullptr;
}


//-------------------------------------------Setter
void Movimiento::setPieza(Piezas* p)
{
	pieza = p;
}

std::vector<std::pair<Casilla*, Casilla*>> Movimiento::obtenerTodasLasCapturasPosibles(const TABLERO& tablero, char colorDelJugador,
    int peon_doble_avance_fila_anterior, int peon_doble_avance_columna_anterior) {
    std::vector<std::pair<Casilla*, Casilla*>> capturas_detectadas;

    for (int r_origen = 0; r_origen < 8; ++r_origen) {
        for (int c_origen = 0; c_origen < 8; ++c_origen) {
            Casilla& origen_casilla = const_cast<Casilla&>(tablero[r_origen][c_origen]);
            Piezas* pieza_en_origen = origen_casilla.getficha();

            if (pieza_en_origen != nullptr && pieza_en_origen->getColor() == colorDelJugador) {
                // Obtener los movimientos brutos de esta pieza (no necesita los datos de en passant aquí)
                std::vector<Casilla*> movs_posibles_de_pieza = pieza_en_origen->movimientosPosibles(tablero, origen_casilla);

                for (Casilla* destino_casilla : movs_posibles_de_pieza) {
                    State estado_mov_actual = pieza_en_origen->comprobarMov(const_cast<TABLERO&>(tablero), origen_casilla, *destino_casilla,
                        peon_doble_avance_fila_anterior, peon_doble_avance_columna_anterior);

                    if (estado_mov_actual == NORMAL && destino_casilla->getficha() != nullptr &&
                        destino_casilla->getficha()->getColor() != colorDelJugador) {
                        // Es una captura normal
                        capturas_detectadas.push_back({ &origen_casilla, destino_casilla });
                    }
                    else if (estado_mov_actual == PASANTE) {
                        // Es una captura al paso
                        capturas_detectadas.push_back({ &origen_casilla, destino_casilla });
                    }
                }
            }
        }
    }
    return capturas_detectadas;
}

// Obtener movimientos filtrados para una pieza según la regla de captura 
std::vector<Casilla*> Movimiento::obtenerMovimientosFiltrados(const TABLERO& tablero, Casilla& origen, char turnoActual,int peon_doble_avance_fila_anterior, int peon_doble_avance_columna_anterior) {
    std::vector<Casilla*> movimientos_validos;

    Piezas* pieza_seleccionada = origen.getficha();
    if (pieza_seleccionada == nullptr || pieza_seleccionada->getColor() != turnoActual) {
        return movimientos_validos;
    }

    // Obtener todas las posibles capturas en el tablero para el jugador actual
    std::vector<std::pair<Casilla*, Casilla*>> todas_las_capturas_disponibles =
        Movimiento::obtenerTodasLasCapturasPosibles(tablero, turnoActual,
            peon_doble_avance_fila_anterior, peon_doble_avance_columna_anterior);


    // Obtener todos los movimientos posibles (brutos) de la pieza seleccionada
    std::vector<Casilla*> movimientos_brutos_de_pieza = pieza_seleccionada->movimientosPosibles(tablero, origen);

    // Aplicar la regla de captura obligatoria
    if (!todas_las_capturas_disponibles.empty()) {
        // Si hay al menos una captura disponible en el tablero para este jugador: solo permitir movimientos de captura de la pieza seleccionada
        for (Casilla* destino : movimientos_brutos_de_pieza) {
            State estado_mov_actual = pieza_seleccionada->comprobarMov(const_cast<TABLERO&>(tablero), origen, *destino,peon_doble_avance_fila_anterior, peon_doble_avance_columna_anterior);

            if (estado_mov_actual == NORMAL && destino->getficha() != nullptr && destino->getficha()->getColor() != turnoActual) {
                movimientos_validos.push_back(destino);
            }
            else if (estado_mov_actual == PASANTE) {
                movimientos_validos.push_back(destino);
            }
        }
    }
    else {
        // Si no hay capturas disponibles en el tablero para este jugador: todos los movimientos posibles son válidos.
        movimientos_validos = movimientos_brutos_de_pieza;
    }
    return movimientos_validos;
}