#pragma once
#include "Tablero.h"
#include "Casilla.h"
#include "Peon.h"
#include "Rey.h"
#include "Torre.h"
#include "Caballo.h"
#include "Alfil.h"
#include "ETSIDI.h"
#include <vector>
#include "Boton.h"
#include "Vineta.h"

using namespace ETSIDI;							//Para no tener que poner ETSIDI:: siempre
using TABLERO = array<array<Casilla, 8>, 8>;	//Decimos que TABLERO equivale a el array de arrays (ahorramos escribir mucho)

class Coordinador
{
private:
	//General--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Sprite Estrella{ "imagenes/inicio/ESTRELLA.png", 0, 0, 20, 25 };
	Sprite MenuInicial{ "imagenes/inicio/MENU4.png", 0, 0, 96, 64 };

	Sprite BotonInterrogacion{ "imagenes/inicio/BOTON_INTERROGACION.png", 0, 0, 20, 20 };
	Sprite BotonInterrogacion2{ "imagenes/inicio/BOTON_INTERROGACION2.png", 0, 0, 20, 20 };

	//Creditos---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Sprite Titulo1Creditos{ "imagenes/recursos/T1.png", 0, 0, 15, 15 };
	Sprite Titulo3Creditos{ "imagenes/recursos/T3.png", 0, 0, 15, 15 };
	Sprite ChessWarsCreditos{ "imagenes/recursos/CW3.png", 0, 0, 19, 15 };
	Sprite FondoEstrellas{ "imagenes/recursos/FONDO_ESTRELLAS.png", 0, 0, 96, 64 };

	//Volumen---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Sprite TextoVolumen{ "imagenes/recursos/TextoVolumen.png", 0,0,20,20 };
	Sprite Volumen0{ "imagenes/recursos/Volumen0.png", 0,0,30,25 };
	Sprite Volumen25{ "imagenes/recursos/Volumen25.png", 0,0,15,15 };
	Sprite Volumen50{ "imagenes/recursos/Volumen50.png", 0,0,15,15 };
	Sprite Volumen75{ "imagenes/recursos/Volumen75.png", 0,0,15,15 };
	Sprite Volumen100{ "imagenes/recursos/Volumen100.png", 0,0,15,15 };
	//viñeta
	//Sprite vineta{ "imagenes/vineta.png", -4,3,70,75 };
	
	//Biomas
	Sprite recuadroBioma{ "imagenes/recuadro_biomas3.png", 0, 0, 10, 9 };

	GLdouble modelviewMatrix[16];
	GLdouble projectionMatrix[16];
	GLint viewportCoords[4];


protected:
	enum Estado { INICIO, DUELO, BIOMA, AJUSTES, SONIDO, MUSICA, AYUDA, CREDITOS, NORMAS, MOVIMIENTOS, VINETA,FIN_JUEGO };
	enum Cancion { CANCION1, CANCION2, CANCION3 };
	std::string mensajeFinJuego{ "" }; // Para almacenar el mensaje de victoria
	char colorGanador{ '\0' };           // 'B' o 'N'
	

private:
	Estado estado;
	Estado estado_anterior;
	Cancion cancion;
	Cancion cancion_anterior;
	char turnoActual; // 'B' para blancas, 'N' para negras

	//Botone varios
	Boton botonSalida{ "imagenes/inicio/Boton_salida.png", "imagenes/inicio/Boton_salida2.png", 20, 20 };
	Boton botonAtras{ "imagenes/inicio/BOTON_ATRAS.png", "imagenes/inicio/BOTON_ATRAS2.png", 4, 4 };
	Boton botonAltavozON{ "imagenes/inicio/BOTON_ALTAVOZ.png", "imagenes/inicio/BOTON_ALTAVOZ1.5.png", 5, 5 };
	Boton botonAltavozOFF{ "imagenes/inicio/BOTON_ALTAVOZ2.png", "imagenes/inicio/BOTON_ALTAVOZ2.5.png", 5, 5 };
	//Inicio
	Boton botonDuelo{ "imagenes/inicio/BOTON_DUELO.png", "imagenes/inicio/BOTON_DUELO2.png", 15, 15 };
	Boton botonBioma{ "imagenes/inicio/BOTON_BIOMA.png", "imagenes/inicio/BOTON_BIOMA2.png", 15, 15 };
	Boton botonAjustes{ "imagenes/inicio/BOTON_AJUSTES.png", "imagenes/inicio/BOTON_AJUSTES2.png", 15, 15 };
	//Duelo
	Boton botonInterrogacion{ "imagenes/inicio/BOTON_INTERROGACION.png","imagenes/inicio/BOTON_INTERROGACION2.png", 4, 4 };
	//Bioma
	Boton botonMapa1{ "imagenes/Tablero_Fondo_Hoch.png", "imagenes/Tablero_Fondo_Hoch2.png", 10, 9 };
	Boton botonMapa2{ "imagenes/Fondo_tablero_Tatooine.png", "imagenes/Fondo_tablero_Tatooine2.png", 10, 9 };
	Boton botonMapa3{ "imagenes/Fondo_tablero_sorgan.png", "imagenes/Fondo_tablero_sorgan2.png",  10, 9 };
	Boton botonMapa4{ "imagenes/Tablero_Fondo_Hoch.png", "imagenes/Tablero_Fondo_Hoch2.png",  10, 9 };
	//Ajustes
	Boton botonSonidoGeneral{ "imagenes/inicio/BOTON_SONIDO.png", "imagenes/inicio/BOTON_SONIDO2.png", 15, 15 };
	Boton botonMusica{ "imagenes/inicio/BOTON_MUSICA.png", "imagenes/inicio/BOTON_MUSICA2.png", 15, 15 };
	Boton botonAyuda{ "imagenes/inicio/BOTON_AYUDA.png", "imagenes/inicio/BOTON_AYUDA2.png", 15, 15 };
	Boton botonCreditos{ "imagenes/inicio/BOTON_CREDITOS.png", "imagenes/inicio/BOTON_CREDITOS2.png", 15, 15 };
	//Ayuda
	Boton botonNormas{ "imagenes/inicio/BOTON_NORMAS.png", "imagenes/inicio/BOTON_NORMAS2.png", 15, 15 };
	Boton botonMovimientos{ "imagenes/inicio/BOTON_MOVIMIENTOS.png", "imagenes/inicio/BOTON_MOVIMIENTOS2.png", 15, 15 };
	//Musica
	Boton botonMusica1{ "imagenes/inicio/cancion1.png", "imagenes/inicio/Cancion1Seleccionada.png", 15, 15 };
	Boton botonMusica2{ "imagenes/inicio/cancion2.png", "imagenes/inicio/Cancion2Seleccionada.png", 15, 15 };
	Boton botonMusica3{ "imagenes/inicio/cancion3.png", "imagenes/inicio/Cancion3Seleccionada.png", 15, 15 };
	//Movimientos
	Boton botonPeonB{ "imagenes/R2D2(1).png", "imagenes/WhitePawn.png", 10, 10 };
	Boton botonPeonN{ "imagenes/Droide_or.png", "imagenes/BlackPawn.png", 10, 10 };
	Boton botonAlfilB{ "imagenes/Yoda.png", "imagenes/WhiteBishop.png", 10, 10 };
	Boton botonAlfilN{ "imagenes/Doku_or.png", "imagenes/BlackBishop.png", 10, 10 };
	Boton botonCaballoB{ "imagenes/Windu.png", "imagenes/WhiteKnight.png", 10, 10 };
	Boton botonCaballoN{ "imagenes/BobaFet_or.png", "imagenes/BlackKnight.png", 10, 10 };
	Boton botonReinaB{ "imagenes/Rey(1).png", "imagenes/WhiteQueen.png", 10, 10 };
	Boton botonReinaN{ "imagenes/Vader_or.png", "imagenes/BlackQueen.png", 10, 10 };
	Boton botonReyB{ "imagenes/Obiwan(1).png", "imagenes/WhiteKing.png", 10, 10 };
	Boton botonReyN{ "imagenes/Palpatine(1).png", "imagenes/BlackKing.png", 10, 10 };
	Boton botonTorreB{ "imagenes/Chewy(1).png", "imagenes/WhiteRook.png", 10, 10 };
	Boton botonTorreN{ "imagenes/Superdroide_or.png", "imagenes/BlackRook.png", 10, 10 };
	Boton botonReglas{ "imagenes/inicio/Boton_Reglas.png", "imagenes/inicio/Boton_Reglas2.png", 15,15 };

	int mapaSeleccionado = 1;
	Tablero tablero;	//Creamos matriz de casillas
	Vineta vineta;
	int ficha;
	Peon peon;
	Rey rey;
	Torre torre;
	Caballo caballo;
	Alfil alfil;
	bool turno = 0;
	int fil1, fil2, col1, col2, fil3, col3;
	bool flag = false;
	//bool resaltar_altavoz = 0;
	bool pulsado_sonido = 0; //Servira para cambiar el icono de sonido
	//Variables para las animaciones
	float bote = 0.0f;
	float angulo_bote = 0.0f;
	float anim_CW = 0.0f;
	bool subiendo_bote = 1;
	float flote_titulo = 0.0f;
	float tamx, tamy;
	bool activacion_titulo2 = 0;
	float tiempo_titulo1 = 0.0f;
	bool activacion_titulo1 = 0;
	bool musica_creditos_activada = 0;
	bool activacion_titulo3 = 0;
	float movimiento_titulo3 = 0.0f;
	float tiempoespera_titulo3 = 0.0f;
	//Variable musica
	int musica_actual = -1; // -1: ninguna, 0: menu, 1: creditos
	//Variables para el rescalado (nos ayuda a que el juego funcione en cualqier pantalla)
	int ancho_ventana = 1920;
	int alto_ventana = 1080;
	float escalaX = 1.0f;
	float escalaY = 1.0f;

	 const float TABLERO_X_INICIO = escalarX(604.0f);
	 const float TABLERO_X_FIN = escalarX(1318.0f);
	 const float TABLERO_Y_INICIO = escalarY(223.0f);
	 const float TABLERO_Y_FIN = escalarY(855.0f);
	 const float CASILLA_ANCHO = escalarX(89.25f); // Ancho de una casilla
	 const float CASILLA_ALTO = escalarY(79.0f);    // Alto de una casilla
	// También podemos calcular el ancho y alto total del tablero para los límites
	 const float TABLERO_ANCHO_TOTAL = CASILLA_ANCHO * 8; // 129.625 * 8 = 1037.0
	 const float TABLERO_ALTO_TOTAL = CASILLA_ALTO * 8;   // 97.75 * 8 = 782.0		


	//Variables volumen
	int volumen = 100;
	Sprite volumenes[5] = {
		Sprite("imagenes/recursos/Volumen0.png",  0,0,30,30),
		Sprite("imagenes/recursos/Volumen25.png", 0,0,30,30),
		Sprite("imagenes/recursos/Volumen50.png", 0,0,30,30),
		Sprite("imagenes/recursos/Volumen75.png", 0,0,30,30),
		Sprite("imagenes/recursos/Volumen100.png",0,0,30,30)
	};
	std::string rutasVolumen[4] = {
		"sonidos/BLASTER25.mp3",
		"sonidos/BLASTER50.mp3",
		"sonidos/BLASTER75.mp3",
		"sonidos/BLASTER100.mp3"
	};
	std::string rutasMenu1[4] = {
	  "sonidos/Musica1_25.mp3",
	  "sonidos/Musica1_50.mp3",
	  "sonidos/Musica1_75.mp3",
	  "sonidos/Musica1_100.mp3",
	};
	std::string rutasMenu2[4] = {
		"sonidos/Musica2_25.mp3",
		"sonidos/Musica2_50.mp3",
		"sonidos/Musica2_75.mp3",
		"sonidos/Musica2_100.mp3",
	};
	std::string rutasMenu3[4] = {
		"sonidos/Musica3_25.mp3",
		"sonidos/Musica3_50.mp3",
		"sonidos/Musica3_75.mp3",
		"sonidos/Musica3_100.mp3",
	};
	//Array para fondos
	std::string rutasFondo[4] = {
	  "imagenes/Tablero_Fondo_Hoch.png",
	  "imagenes/Fondo_tablero_Tatooine.png.png",
	  "imagenes/Fondo_tablero_Sorgan.png.png",
	  "imagenes/Tablero_Fondo_Hoch.png",
	};
	vector <Estado> memoria_Estado;
	std::vector<std::pair<Casilla*, Casilla*>> capturas_oponente_pendientes;

public:
	Coordinador();
	void MovRaton(int x, int y);
	void calcular_Casilla(int button, int state, int x, int y);
	void mouse(int button, int state, int x, int y);
	void seleccion(int f1, int c1, char turnoActual);				//pasar la casilla seleccionada al tablero
	void dibuja();//dibujar el juego
	void dibujaTurno();
	void animaciones();
	void musica();

	//Getters
	Estado getEstado() const;
	Estado getEstadoAnterior() const;
	Cancion getCancion() const;
	Cancion getCancionAnterior() const;
	char getTurnoActual() const { return turnoActual; }
	void cambiarTurno();

	//Setters
	void setEstado(Estado nuevo_estado);
	void setEstadoAnterior(Estado nuevo_estado_anterior);
	void setCancion(Cancion nueva_cancion);
	void setCancionAnterior(Cancion nueva_cancion_anterior);

	//Control de volumen
	void subirVolumen();
	void bajarVolumen();


	//Funcions para el escalado de las coordenadas(nos permite que funcione en pantalla completa en cualquier pantalla)
	void actualizarEscalaVentana(int ancho_actual, int alto_actual);
	float escalarX(float x) const;
	float escalarY(float y) const;
};

