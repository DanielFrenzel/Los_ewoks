#include "Coordinador.h"
#include "freeglut.h"
#include "ETSIDI.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

//Movimiento del raton----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::MovRaton(int x, int y)  //Indica que casilla se ha pulsado según 
{
	float x_base = x / escalaX;
	float y_base = y / escalaY;
	
	int fil_tablero_resaltar = -1;
	int col_tablero_resaltar = -1;

	
		// Verificar si el ratón está sobre el área del tablero usando TUS COORDENADAS
		if (x_base >= TABLERO_X_INICIO && x_base < (TABLERO_X_INICIO + TABLERO_ANCHO_TOTAL) &&
			y_base >= TABLERO_Y_INICIO && y_base < (TABLERO_Y_INICIO + TABLERO_ALTO_TOTAL))
		{
			// Calcular coordenadas relativas dentro del tablero
			float relative_x = x_base - TABLERO_X_INICIO;
			float relative_y = y_base - TABLERO_Y_INICIO;

			// Calcular columna usando ancho de casilla
			col_tablero_resaltar = static_cast<int>(relative_x / CASILLA_ANCHO);
			// Calcular fila invirtiendo Y, usando Talto de casilla
			fil_tablero_resaltar = 7 - static_cast<int>(relative_y / CASILLA_ALTO);

			if (estado == DUELO) { // Solo si estamos en el estado de juego
				if (col_tablero_resaltar >= 0 && col_tablero_resaltar < 8 &&
					fil_tablero_resaltar >= 0 && fil_tablero_resaltar < 8) {

					// Solo actualiza la casilla sobre el ratón
					tablero.setMouseOver(fil_tablero_resaltar, col_tablero_resaltar);
				}
				else {
					// Si el ratón está fuera del tablero, limpiar cualquier resaltado de mouse-over
					tablero.clearMouseOver();
				}
			}
			else {
				// Si no estamos en el estado de duelo, limpiar mouse-over del tablero
				tablero.clearMouseOver();
			}
		}
	
	botonSalida.actualizaResaltado(x_base, y_base);
	botonAtras.actualizaResaltado(x_base, y_base);
	botonAltavozON.actualizaResaltado(x_base, y_base);
	botonAltavozOFF.actualizaResaltado(x_base, y_base);
	switch (estado)
	{
	case INICIO:
		botonDuelo.actualizaResaltado(x_base, y_base);
		botonBioma.actualizaResaltado(x_base, y_base);
		botonAjustes.actualizaResaltado(x_base, y_base);
		break;
	case AJUSTES:
		botonSonidoGeneral.actualizaResaltado(x_base, y_base);
		botonMusica.actualizaResaltado(x_base, y_base);
		botonAyuda.actualizaResaltado(x_base, y_base);
		botonCreditos.actualizaResaltado(x_base, y_base);
		break;
	case AYUDA:
		botonNormas.actualizaResaltado(x_base, y_base);
		botonMovimientos.actualizaResaltado(x_base, y_base);
		break;

	case MUSICA:
		botonMusica1.actualizaResaltado(x_base, y_base);
		botonMusica2.actualizaResaltado(x_base, y_base);
		botonMusica3.actualizaResaltado(x_base, y_base);
		break;
	case BIOMA:
		botonMapa1.actualizaResaltado(x_base, y_base);
		botonMapa2.actualizaResaltado(x_base, y_base);
		botonMapa3.actualizaResaltado(x_base, y_base);
		botonMapa4.actualizaResaltado(x_base, y_base);
		break;
	}


}
//para controlar el click--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::mouse(int button, int state, int x, int y)
{
	float x_base = x / escalaX;
	float y_base = y / escalaY;
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
		if (botonSalida.ratonEncima(x_base,y_base)) exit(0);
		if (!pulsado_sonido && botonAltavozON.ratonEncima(x_base, y_base)) {
			pulsado_sonido = true;
			musica();
			return;
		}
		
		if (pulsado_sonido && botonAltavozOFF.ratonEncima(x_base, y_base)) {
			pulsado_sonido = false;
			musica();
			return;
		}
		if (botonAtras.ratonEncima(x_base,y_base)&&estado!=INICIO)
		{
			estado = memoria_Estado.back();
			memoria_Estado.pop_back();			
		}
		if (estado == INICIO)
		{
			if (botonDuelo.ratonEncima(x_base, y_base))
			{
				memoria_Estado.push_back(INICIO);
				estado = VINETA;
				return;
			}
			if (botonBioma.ratonEncima(x_base, y_base))
			{
				memoria_Estado.push_back(INICIO);
				estado_anterior = estado;
				estado = BIOMA;
				return;
			}
			if (botonAjustes.ratonEncima(x_base, y_base))
			{
				memoria_Estado.push_back(INICIO);
				estado_anterior = estado;
				estado = AJUSTES;
				return;
			}
		}

		if (estado == VINETA)
		{
			estado = DUELO;
			turnoActual = 'B';
		}
				
		if (estado == AJUSTES)
		{			
			
			if (botonSonidoGeneral.ratonEncima(x_base, y_base))
			{
				memoria_Estado.push_back(AJUSTES);
				estado_anterior = estado;
				estado = SONIDO;
				return;
			}
			if (botonMusica.ratonEncima(x_base, y_base))
			{
				memoria_Estado.push_back(AJUSTES);
				estado_anterior = estado;
				estado = MUSICA;
				return;
			}
			if (botonAyuda.ratonEncima(x_base, y_base))
			{
				memoria_Estado.push_back(AJUSTES);
				estado_anterior = estado;
				estado = AYUDA;
				return;
			}
			if (botonCreditos.ratonEncima(x_base, y_base))
			{
				memoria_Estado.push_back(AJUSTES);
				estado_anterior = estado;
				estado = CREDITOS;
				activacion_titulo1 = true;
				activacion_titulo2 = false;
				tiempo_titulo1 = 0.0f;
				flote_titulo = 0.0f;
				musica_creditos_activada = false;
				musica();
				return;
			}
		}
		if (estado == AYUDA)
		{
			if (botonNormas.ratonEncima(x_base, y_base))
			{
				estado = AYUDA;
				system("start https://www.ajedrezeureka.com/ajedrez-pierde-gana/"); //Comando para abrir el navegador
				return;
			}
			if (botonMovimientos.ratonEncima(x_base, y_base))
			{
				memoria_Estado.push_back(AYUDA);
				estado_anterior = estado;
				estado = MOVIMIENTOS;
				return;
			}
		}
		if (estado == BIOMA)
		{
			if (botonMapa1.ratonEncima(x_base, y_base)) {
				mapaSeleccionado = 1;
			}
			else if (botonMapa2.ratonEncima(x_base, y_base)) {
				mapaSeleccionado = 2;
			}
			else if (botonMapa3.ratonEncima(x_base, y_base)) {
				mapaSeleccionado = 3;
			}
			else if (botonMapa4.ratonEncima(x_base, y_base)) {
				mapaSeleccionado = 4;
			}
			switch (mapaSeleccionado) {
			case 1: recuadroBioma.setPos(botonMapa1.getX(), botonMapa1.getY()); break;
			case 2: recuadroBioma.setPos(botonMapa2.getX(), botonMapa2.getY()); break;
			case 3: recuadroBioma.setPos(botonMapa3.getX(), botonMapa3.getY()); break;
			case 4: recuadroBioma.setPos(botonMapa4.getX(), botonMapa4.getY()); break;
			}
			return;
		}
	}
}



void Coordinador::seleccion(int f1, int c1, char turnoActual)
{
	tablero.seleccion(f1, c1, turnoActual);
}

void Coordinador::cambiarTurno()
{
	 {
		if (turnoActual == 'B')
		{
			turnoActual = 'N';
		}
		else
		{
			turnoActual = 'B';
		}
	}
}

void Coordinador::calcular_Casilla(int button, int state, int x, int y)
{

	float x_base = x / escalaX;
	float y_base = y / escalaY;

	int fil_clic = -1;
	int col_clic = -1;

	// Calcular la casilla clickeada (asegura que está dentro del tablero)
	bool clicEnTablero = false;
	if (x_base >= TABLERO_X_INICIO && x_base < (TABLERO_X_INICIO + TABLERO_ANCHO_TOTAL) &&
		y_base >= TABLERO_Y_INICIO && y_base < (TABLERO_Y_INICIO + TABLERO_ALTO_TOTAL))
	{
		float relative_x = x_base - TABLERO_X_INICIO;
		float relative_y = y_base - TABLERO_Y_INICIO;

		col_clic = static_cast<int>(relative_x / CASILLA_ANCHO);
		fil_clic = 7 - static_cast<int>(relative_y / CASILLA_ALTO);

		if (col_clic >= 0 && col_clic < 8 && fil_clic >= 0 && fil_clic < 8) {
			clicEnTablero = true;
		}
	}

	// --- Manejo de clics del ratón ---
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // Clic izquierdo: Selección o Movimiento
	{
		// Determinar si el jugador actual tiene capturas obligatorias en el tablero.
		std::vector<std::pair<Casilla*, Casilla*>> todas_las_capturas_jugador_actual =
			Movimiento::obtenerTodasLasCapturasPosibles(tablero.getTableroConst(), turnoActual);
		bool hay_captura_obligatoria = !todas_las_capturas_jugador_actual.empty();

		if (flag == false) // No hay pieza seleccionada aún (primer clic)
		{
			if (clicEnTablero) {
				Casilla& casillaClickeada = tablero.getCasilla(fil_clic, col_clic);
				Piezas* piezaClickeada = casillaClickeada.getficha();

				// Validar la selección según la regla de captura obligatoria
				if (piezaClickeada != nullptr && piezaClickeada->getColor() == turnoActual) {
					bool esta_pieza_puede_capturar = false;
					if (hay_captura_obligatoria) {
						// Si hay captura obligatoria, esta pieza solo puede ser seleccionada si puede capturar.
						for (const auto& par : todas_las_capturas_jugador_actual) {
							if (par.first->getfila() == fil_clic && par.first->getcolumna() == col_clic) {
								esta_pieza_puede_capturar = true;
								break;
							}
						}
					}
					else {
						// Si no hay captura obligatoria, cualquier pieza del turno actual puede ser seleccionada.
						esta_pieza_puede_capturar = true;
					}

					if (esta_pieza_puede_capturar) {
						flag = true;
						col1 = col_clic;
						fil1 = fil_clic;
						tablero.seleccion(fil1, col1, turnoActual); 
					}
					else {
						// Clic en una pieza propia que no puede capturar, pero hay otra que sí puede.
						// Deseleccionar y no hacer nada.
						tablero.deseleccionar();
					}
				}
				else {
					// Clic en casilla vacía, pieza del oponente, o clic inválido para seleccionar
					tablero.deseleccionar();
				}
			}
			else {
				// Clic izquierdo fuera del tablero y no hay pieza seleccionada: deseleccionar por si acaso.
				tablero.deseleccionar();
			}
		}
		else // Ya hay una pieza seleccionada (flag == true) (Segundo clic: Intentar mover)
		{
			if (clicEnTablero) {
				col2 = col_clic;
				fil2 = fil_clic;

				Casilla& origen_seleccionada = tablero.getCasilla(fil1, col1);
				Casilla& destino_clickeado = tablero.getCasilla(fil2, col2);

				bool movimiento_valido_por_regla = false;
				// Obtener los movimientos "válidos" para la pieza seleccionada, según la regla de captura obligatoria.
				std::vector<Casilla*> movimientos_filtrados_para_esta_pieza =
					Movimiento::obtenerMovimientosFiltrados(tablero.getTableroConst(), origen_seleccionada, turnoActual); 

				for (Casilla* destino_posible : movimientos_filtrados_para_esta_pieza) {
					if (destino_posible->getfila() == fil2 && destino_posible->getcolumna() == col2) {
						movimiento_valido_por_regla = true;
						break;
					}
				}

				if (movimiento_valido_por_regla) {
					if (tablero.mueve(fil1, col1, fil2, col2, turnoActual)) {
						char oponenteColor = (turnoActual == 'B') ? 'N' : 'B';
						// Contar las piezas del oponente después de que se haya movido la pieza y potencialmente capturado
						if (tablero.contarPiezas(oponenteColor) == 0) {
							estado = FIN_JUEGO;
							if (turnoActual == 'B') {
								mensajeFinJuego = "¡Han ganado los Jedi!";
								colorGanador = 'B';
							}
							else {
								mensajeFinJuego = "¡Han ganado los Sith!";
								colorGanador = 'N';
							}
						}
						else {
							cambiarTurno(); // Solo cambia el turno si el juego no ha terminado
						}
					}
				}
				else {
					// Movimiento inválido (no se movió)
				}

				flag = false;
				tablero.deseleccionar();
			}
			else {
				// Clic izquierdo fuera del tablero
				flag = false;
				tablero.deseleccionar();
			}
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) // Clic derecho: Siempre cancelar la selección
	{
		flag = false;
		tablero.deseleccionar();
	}

}

//Constructor-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Coordinador::Coordinador()
	{
		estado = INICIO;
		turnoActual = 'B'; 
		mensajeFinJuego = "";
		colorGanador = '\0';

		//botones Varios
		botonSalida.setPos(-32, 38);
		botonSalida.setRegion(21.0f, 127.0f, 18.0f, 38.0f);
		botonSalida.setSize(5.0f, 5.0f);
		botonAtras.setPos(35, 29);
		botonAtras.setRegion(1702.0f, 1783.0f, 26.0f, 74.0f);
		botonAltavozON.setPos(40, 29);
		botonAltavozON.setRegion(1816.0f, 1895.0f, 23.0f, 76.0f);
		botonAltavozOFF.setPos(40, 29);
		botonAltavozOFF.setRegion(1816.0f, 1895.0f, 23.0f, 76.0f);

		//botones Inicio
		botonDuelo.setPos(-30, -25);
		botonDuelo.setRegion(122.0f, 452.0f, 915.0f, 1024.0f);
		botonBioma.setPos(0, -25);
		botonBioma.setRegion(795.0f, 1125.0f, 916.0f, 1025.0f);
		botonAjustes.setPos(30, -25);
		botonAjustes.setRegion(1466.0f, 1796.0f, 917.0f, 1025.0f);

		//botones Ajustes
		botonSonidoGeneral.setPos(-30, -25);
		botonSonidoGeneral.setRegion(122.0f, 452.0f, 915.0f, 1024.0f);
		botonMusica.setPos(0, -25);
		botonMusica.setRegion(795.0f, 1125.0f, 916.0f, 1025.0f);
		botonAyuda.setPos(30, -25);
		botonAyuda.setRegion(1466.0f, 1796.0f, 917.0f, 1025.0f);
		botonCreditos.setPos(0, -10);
		botonCreditos.setRegion(795.0f, 1125.0f, 664.0f, 773.0f);

		//Botones Ayuda
		botonNormas.setPos(-30, -25);
		botonNormas.setRegion(122.0f, 452.0f, 915.0f, 1024.0f);
		botonMovimientos.setPos(30, -25);
		botonMovimientos.setRegion(1466.0f, 1796.0f, 917.0f, 1025.0f);

		//Botones Musica
		botonMusica1.setPos(-30, -25);
		botonMusica1.setRegion(105.0f, 450.0f, 874.0f, 1025.0f);
		botonMusica2.setPos(0, -25);
		botonMusica2.setRegion(794.0f, 1120.0f, 874.0f, 1025.0f);
		botonMusica3.setPos(30, -25);
		botonMusica3.setRegion(1464.0f, 1790.0f, 874.0f, 1025.0f);

		//Botones Bioma
		botonMapa1.setPos(-30, -20);
		botonMapa1.setRegion(175.0f, 400.0f, 800.0f, 950.0f);
		botonMapa2.setPos(-10, -20);
		botonMapa2.setRegion(620.0f, 845.0f, 800.0f, 950.0f);
		botonMapa3.setPos(10, -20);
		botonMapa3.setRegion(1075.0f, 1295.0f, 800.0f, 950.0f);
		botonMapa4.setPos(30, -20);
		botonMapa4.setRegion(1520.0f, 1745.0f, 800.0f, 950.0f);

		recuadroBioma.setPos(botonMapa1.getX(), botonMapa1.getY());

		pulsado_sonido = false;
		activacion_titulo2 = false;
		tamx = 0, tamy = 0;
		activacion_titulo1 = false;
		musica_creditos_activada = false;
		activacion_titulo3 = false;
	}
//Animaciones varias de los menus-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::animaciones()
{
	//bote estrella
	angulo_bote += 0.05f; // velocidad del bote
	if (angulo_bote > 2 * 3.14159f)
		angulo_bote = 0.0f;

	bote = sin(angulo_bote) * 1.0f;

	//Creditos (toda la secuencia completa)
	if (estado == CREDITOS)
	{
		
		if (activacion_titulo1==1)
		{
			tiempo_titulo1 += 0.025f;  
			if (tiempo_titulo1 >= 5.0f) {
				activacion_titulo1 = false;
				activacion_titulo2 = true;
				activacion_titulo3 = true;
				movimiento_titulo3 = 0.0f;
				playMusica("sonidos/MusicaCreditos.mp3", true);
			}
		}
		if(activacion_titulo2==1)
		{
			flote_titulo += 0.25f;
			if (flote_titulo >= 60.0f)
			{
				activacion_titulo2 = false;    
			
			}
		}
		if (activacion_titulo3 == 1)
		{
			movimiento_titulo3 += 0.07f;
			if (-120+movimiento_titulo3>100)
			{
				activacion_titulo3 = false;
			}
		
		}
	}
	
}
//Musica-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::musica()
{

	if (pulsado_sonido != 0)
	{
		stopMusica();
		musica_actual = -1;
		return;
	}

	if (estado == CREDITOS &&  musica_actual != 1)
	{
		stopMusica();
		musica_actual = 1;
	}
	else if (estado != CREDITOS && musica_actual != 0)
	{
		playMusica("sonidos/Musica1_100.mp3", true);
		musica_actual = 0;
	}

	
}
 

//Control de volumen
void Coordinador::subirVolumen() {
	if (volumen < 100) {
		volumen += 25;
		stopMusica();
		playMusica(rutasVolumen[(volumen / 25) - 1].c_str(), false);
	}
}
void Coordinador::bajarVolumen() {
	if (volumen > 0) {
		volumen -= 25;
		stopMusica();
		playMusica(rutasVolumen[(volumen / 25) - 1].c_str(), false);
	}
}

//Para dibujar-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::dibuja()
{
	
	//estado = DUELO;
	//Estella de la muerte
	if (estado != CREDITOS && estado != DUELO && estado != VINETA)
	{
		Estrella.setPos(-16, 0 + bote);
		Estrella.draw();
		Estrella.setSize(20, 25);
	}

	//Boton de sonido
	if (pulsado_sonido == 0)
	{
		botonAltavozON.draw();
	}
	else
	{
		botonAltavozOFF.draw();
	}
	//Boton Exit
	botonSalida.draw();

	//Boton de atras
	if(estado!=INICIO) botonAtras.draw();

	//Botones Inicio
	if (estado == INICIO) {
		botonDuelo.draw();
		botonBioma.draw();
		botonAjustes.draw();
		dibujaTurno();
	}

	if (estado == DUELO) {
		stopMusica();
		playMusica("sonidos/Musica1_100.mp3", true);
		tablero.dibuja();
		dibujaTurno();

	}

	if (estado == FIN_JUEGO) {
		ETSIDI::setTextColor(1.0, 0.0, 0.0); // Rojo
		ETSIDI::setFont("fuentes/STARWARS.ttf", 16);
		ETSIDI::printxy(mensajeFinJuego.c_str(), -5.0, 25.0); // Ajusta coordenadas

	}

	if (estado == VINETA)
	{
		vineta.dibujar();
	}

	//Botones AJUSTES
	if (estado == AJUSTES) {
		botonSonidoGeneral.draw();
		botonMusica.draw();
		botonAyuda.draw();
		botonCreditos.draw();
	}
	if (estado == BIOMA){
		recuadroBioma.draw();
		botonMapa1.draw();
		botonMapa2.draw();
		botonMapa3.draw();
		botonMapa4.draw();
	}

	//Botones AYUDA
	if (estado == AYUDA) {
		botonNormas.draw();
		botonMovimientos.draw();

	}

	//Botones MUSICA
	if (estado == MUSICA) {
		botonMusica1.draw();
		botonMusica2.draw();
		botonMusica3.draw();
	}

	//Volumen
	if (estado == SONIDO) {
		TextoVolumen.setPos(0, -26);
		TextoVolumen.draw();
		volumenes[volumen / 25].setPos(0, -25);
		volumenes[volumen / 25].draw();
	}

	//Fondo
	if (estado != CREDITOS)
	{
		MenuInicial.draw();	
	}
	

	//Creditos (toda la secuencia)
	if (estado == CREDITOS)
	{
		if (activacion_titulo1 == 1)
		{
			Titulo1Creditos.setPos(-40, 0);
			Titulo1Creditos.setCenter(0, 0);
			Titulo1Creditos.draw();
			Titulo1Creditos.setSize(80, 20);
		}
		if (activacion_titulo2 == 1)
		{
			tamx = 60 - flote_titulo;
			tamy = 56 - flote_titulo;
			ChessWarsCreditos.setPos(-tamx / 2.0f, -tamy / 2.0f);
			ChessWarsCreditos.draw();
			ChessWarsCreditos.setCenter(0, 0);
			ChessWarsCreditos.setSize(60 - flote_titulo, 60 - flote_titulo);
		}
		if (activacion_titulo3 == 1)
		{
			Titulo1Creditos.setCenter(0, 0);
			Titulo3Creditos.setPos(-37, -125 + movimiento_titulo3);
			Titulo3Creditos.draw();
			Titulo3Creditos.setSize(90, 110);
		}
		
		FondoEstrellas.draw();

		}
	}

	void Coordinador::dibujaTurno()
	{
		glPushMatrix();
		glTranslatef(0, 0, 0); // Ajusta la posición según donde quieras mostrar el texto

		if (estado == DUELO) // Si el juego está en curso, muestra el turno
		{
			ETSIDI::setTextColor(1.0, 1.0, 1.0); // Blanco
			ETSIDI::setFont("fuentes/STARWARS.ttf", 16); // Fuente para el turno
			if (turnoActual == 'B')
			{
				ETSIDI::printxy("Turno de los Jedi", -5.0, 25.0); 
			}
			else
			{
				ETSIDI::printxy("Turno de los Sith", -5.0, 25.0); 
			}
		}
		else if (estado == FIN_JUEGO) // Si el juego ha terminado, muestra el mensaje de victoria
		{
			ETSIDI::setTextColor(1.0f, 0.0f, 0.0f); // Color rojo para el mensaje de victoria
			ETSIDI::setFont("fuentes/STARWARS.ttf", 20); // Fuente más grande para el mensaje final
			ETSIDI::printxy(mensajeFinJuego.c_str(), -15.0f, 15.0f); 
		}
		glPopMatrix();
	}

	//Getters (Por si hiciera falta)---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Coordinador::Estado Coordinador::getEstado() const 
	{
		return estado;
	}


	//Setters (Por si hicera falta)---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void Coordinador::setEstado(Estado nuevo_estado) {
		estado = nuevo_estado;
	}

	void Coordinador::setEstadoAnterior(Estado nuevo_estado_anterior) {
		estado_anterior = nuevo_estado_anterior;
	}

	void Coordinador::actualizarEscalaVentana(int ancho_actual, int alto_actual) {
		escalaX = ancho_actual / 1920.0f;
		escalaY = alto_actual / 1080.0f;
		ancho_ventana = ancho_actual;
		alto_ventana = alto_actual;
	}

	float Coordinador::escalarX(float x) const {
		return x * escalaX;
	}

	float Coordinador::escalarY(float y) const {
		return y * escalaY;
	}
