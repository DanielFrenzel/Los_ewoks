#include "Coordinador.h"
#include "freeglut.h"
#include "ETSIDI.h"
#include <cstdlib>
#include <iostream>

//Movimiento del raton----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::MovRaton(int x, int y)  //Indica que casilla se ha pulsado según 
{
	float x_base = x / escalaX;
	float y_base = y / escalaY;
	int fil3 = 0, col3 = 0;
	if ((x >= 100 || x <= 700) && (y >= 0 || y <= 600))
	{
		for (int i = 0;i < 8;i++)
		{
			if ((x >= 100 + (75 * (i))) && (x <= 100 + (75 * (i + 1))))
			{
				col3 = i;
			}
			if ((y >= 0 + (75 * (i))) && (y <= 0 + (75 * (i + 1))))
			{
				fil3 = (7 - i);
			}
		}
		tablero.seleccion(fil3, col3);
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
	//std::cout << "Click en pos juego: (" << x_base << ", " << y_base << ")" << std::endl;
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
			if (x_base >= 1466 && x_base <= 1796 && y_base >= 917 && y_base <= 1025)
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
//Movimiento fichas----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::mueve(int fil1, int col1, int fil2, int col2)  //mueve la ficha de la selección 1 a la 2
{
	tablero.mueve(fil1, col1, fil2, col2);
}

void Coordinador::calcular_Casilla(int button, int state, int x, int y)		//se ha hecho para que al cambiar de resolucion de pantalla no de problema
{
	
	const float tableroXInicio = 441.0f;
	const float tableroXFin = 1478.0f;
	const float tableroYInicio = 151.0f;
	const float tableroYFin = 933.0f;
	const float pasoX = 129.625f;
	const float pasoY = 97.75f;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == false)		//pieza que se quiere mover
	{
	
		if ((x >= escalarX(tableroXInicio) && x <= escalarX(tableroXFin)) &&
			(y >= escalarY(tableroYInicio) && y <= escalarY(tableroYFin)))
		{
			for (int i = 0; i < 8; i++)
			{
				if ((x >= escalarX(tableroXInicio + (pasoX * i))) &&
					(x <= escalarX(tableroXInicio + (pasoX * (i + 1)))))
				{
					flag = true;
					col1 = i;
				}
				if ((y >= escalarY(tableroYInicio + (pasoY * i))) &&
					(y <= escalarY(tableroYInicio + (pasoY * (i + 1)))))
				{
					fil1 = (7 - i);
				}
			}
			//playMusica("sonidos/Sonido_Seleccion.mp3", true);
			tablero.seleccion(fil1, col1);
		}
		
		//playMusica("sonidos/Sonido_Seleccion.mp3", false);
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == true)		//casilla a la que se quiere mover la pieza
	{
	   if ((x >= escalarX(tableroXInicio) && x <= escalarX(tableroXFin)) && (y >= escalarY(tableroYInicio) && y <= escalarY(tableroYFin)))
	{
		for (int i = 0; i < 8; i++)
		{
			if ((x >= escalarX(tableroXInicio + (pasoX * i))) &&
				(x <= escalarX(tableroXInicio + (pasoX * (i + 1)))))
			{
				flag = true;
				col2 = i;
			}
			if ((y >= escalarY(tableroYInicio + (pasoY * i))) &&
				(y <= escalarY(tableroYInicio + (pasoY * (i + 1)))))
			{
				fil2 = (7 - i);
			}
		}
		tablero.mueve(fil1, col1, fil2, col2);
	}
	   flag = false;

	}
	

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && flag == true)  //sirve para cancelar la seleccion de una pieza
	{
		flag = false;
	}
	
}

void Coordinador::seleccion(int f1, int c1)
{
	tablero.seleccion(f1, c1);
}

//Constructor-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Coordinador::Coordinador()
{
	estado = INICIO;
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
	}

	if (estado == DUELO) {
		stopMusica();
		playMusica("sonidos/Musica1_100.mp3", true);
		tablero.dibuja();
		
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
//Getters (Por si hiciera falta)---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Coordinador::Estado Coordinador::getEstado() const 
{
	return estado;
}

Coordinador::Estado Coordinador::getEstadoAnterior() const 
{
	return estado_anterior;
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