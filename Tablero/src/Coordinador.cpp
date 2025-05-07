#include "Coordinador.h"
#include "freeglut.h"
#include "ETSIDI.h"
#include <cstdlib>
void Coordinador::setTablero(Tablero* t)
{
	tablero = t;
}
//Movimiento del raton----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::MovRaton(int x, int y)  //Indica que casilla se ha pulsado según 
{
	float x_base = x / escalaX;
	float y_base = y / escalaY;
	int fil3 = 0, col3 = 0;
	if ((x_base >= 100 || x_base <= 700) && (y_base >= 0 || y_base <= 600))
	{
		for (int i = 0; i < 8; i++)
		{
			if ((x_base >= 100 + (75 * i)) && (x_base <= 100 + (75 * (i + 1))))
			{
				col3 = i;
			}
			if ((y_base >= 0 + (75 * i)) && (y_base <= 0 + (75 * (i + 1))))
			{
				fil3 = (7 - i);
			}
		}
		if (tablero)
			tablero->seleccion(fil3, col3);
	}
	//Reset resaltado de botones
	resaltar_duelo = false;
	resaltar_ia = false;
	resaltar_ajustes = false;
	resaltar_salida = false;
	resaltar_altavoz = false;
	resaltar_sonido = false;
	resaltar_musica = false;
	resaltar_ayuda = false;
	resaltar_creditos = false;
	resaltar_normas = false;
	resaltar_movimientos = false;
	resaltar_atras = false;
	resaltar_interrogacion = false;
	resaltar_cancion1 = false;
	resaltar_cancion2 = false;
	resaltar_cancion3 = false;

	if (x_base >= 21 && x_base <= 127 && y_base >= 18 && y_base <= 38) resaltar_salida = true;
	if (x_base >= 1816 && x_base <= 1895 && y_base >= 23 && y_base <= 76) resaltar_altavoz = true;
	if (x_base >= 1702 && x_base <= 1783 && y_base >= 26 && y_base <= 74) resaltar_atras = true;
	switch (estado)
	{
	case INICIO:
		if (x_base >= 122 && x_base <= 452 && y_base >= 915 && y_base <= 1024) resaltar_duelo = true;
		if (x_base >= 795 && x_base <= 1125 && y_base >= 916 && y_base <= 1025) resaltar_ia = true;
		if (x_base >= 1466 && x_base <= 1796 && y_base >= 917 && y_base <= 1025) resaltar_ajustes = true;
		break;
	case AJUSTES:
		if (x_base >= 122 && x_base <= 452 && y_base >= 915 && y_base <= 1024) resaltar_sonido = true;
		if (x_base >= 795 && x_base <= 1125 && y_base >= 916 && y_base <= 1025) resaltar_musica = true;
		if (x_base >= 1466 && x_base <= 1796 && y_base >= 917 && y_base <= 1025) resaltar_ayuda = true;
		if (x_base >= 795 && x_base <= 1125 && y_base >= 664 && y_base <= 773) resaltar_creditos = true;
		break;
	case AYUDA:
		if (x_base >= 122 && x_base <= 452 && y_base >= 915 && y_base <= 1024) resaltar_normas = true;
		if (x_base >= 1466 && x_base <= 1796 && y_base >= 917 && y_base <= 1025) resaltar_movimientos = true;
		break;

	case MUSICA:
		if (x_base >= 105 && x_base <= 450 && y_base >= 874 && y_base <= 1025) resaltar_cancion1 = true;
		if (x_base >= 794 && x_base <= 1120 && y_base >= 874 && y_base <= 1025) resaltar_cancion2 = true;
		if (x_base >= 1464 && x_base <= 1790 && y_base >= 874 && y_base <= 1025) resaltar_cancion3 = true;
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
		if (x_base >= 21 && x_base <= 127 && y_base >= 18 && y_base <= 38) exit(0);
		if (x_base >= 1816 && x_base <= 1895 && y_base >= 23 && y_base <= 76)
		{
			if (pulsado_sonido == 0)
			{
				pulsado_sonido = true;
				musica();
			}
			else {
				pulsado_sonido = false;
				musica();
			}
		}
		if (x_base >= 1702 && x_base <= 1783 && y_base >= 26 && y_base <= 74)
		{
			estado = memoria_Estado.back();
			memoria_Estado.pop_back();			
		}
		if (estado == INICIO)
		{
			if (x_base >= 122 && x_base <= 452 && y_base >= 915 && y_base <= 1024)
			{
				memoria_Estado.push_back(INICIO);
				estado = DUELO;
				return;
			}
			if (x_base >= 795 && x_base <= 1125 && y_base >= 916 && y_base <= 1025)
			{
				memoria_Estado.push_back(INICIO);
				estado_anterior = estado;
				estado = IA;
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
		if (estado == AJUSTES)
		{			
			
			if (x_base >= 122 && x_base <= 452 && y_base >= 915 && y_base <= 1024)
			{
				memoria_Estado.push_back(AJUSTES);
				estado_anterior = estado;
				estado = SONIDO;
				return;
			}
			if (x_base >= 795 && x_base <= 1125 && y_base >= 916 && y_base <= 1025)
			{
				memoria_Estado.push_back(AJUSTES);
				estado_anterior = estado;
				estado = MUSICA;
				return;
			}
			if (x_base >= 1466 && x_base <= 1796 && y_base >= 917 && y_base <= 1025)
			{
				memoria_Estado.push_back(AJUSTES);
				estado_anterior = estado;
				estado = AYUDA;
				return;
			}
			if (x_base >= 795 && x_base <= 1125 && y_base >= 664 && y_base <= 773)
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
			if (x_base >= 122 && x_base <= 452 && y_base >= 915 && y_base <= 1024)
			{
				estado = AYUDA;
				system("start https://www.ajedrezeureka.com/ajedrez-pierde-gana/"); //Comando para abrir el navegador
				return;
			}
			if (x_base >= 1466 && x_base <= 1796 && y_base >= 917 && y_base <= 1025)
			{
				memoria_Estado.push_back(AYUDA);
				estado_anterior = estado;
				estado = MOVIMIENTOS;
				return;
			}
		}


		
	}
}
//Movimiento fichas----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::movimiento(int fil1, int col1, int fil2, int col2)  //mueve la ficha de la selección 1 a la 2
{
	char color = (turno == 0) ? 'B' : 'N';

	if (fil1 == fil2 && col1 == col2)
		return;

	if (compMov(fil1, col1, fil2, col2) && tablero->getCasillas()[fil1][col1].getcolor() == color)
	{
		if (tablero->getCasillas()[fil1][col1].getficha() != 0)
		{
			tablero->getCasillas()[fil2][col2].setficha(tablero->getCasillas()[fil1][col1].getficha(), tablero->getCasillas()[fil1][col1].getcolor());
			tablero->getCasillas()[fil1][col1].setficha(0, 0);

			// Actualiza selección gráfica
			tablero->seleccion(fil2, col2);
			turno = not(turno);
		}
	}
}

bool Coordinador::compMov(int fil1, int col1, int fil2, int col2) //comprueba si se puede mover
{
	switch (tablero->getCasillas()[fil1][col1].getficha())
	{
	case 6:
		return peon.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	case 5:
		return alfil.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2) || torre.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	case 4:
		return rey.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	case 3:
		return alfil.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	case 2:
		return caballo.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	case 1:
		return torre.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	default:
		return false;
	}
}
//Constructor-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Coordinador::Coordinador()
{
	//Vamos a utilizar esta parte de codigo para especificar en que estado estamos
	estado = INICIO;
	//Reseteamos los botones para que salga bien el "resaltar"
	resaltar_duelo = false;
	resaltar_ia = false;
	resaltar_ajustes = false;
	resaltar_salida = false;
	resaltar_altavoz = false;
	resaltar_sonido = false;
	resaltar_musica = false;
	resaltar_ayuda = false;
	resaltar_creditos = false;
	pulsado_sonido = false;
	resaltar_normas = false;
	resaltar_movimientos = false;
	resaltar_atras = false;
	resaltar_interrogacion = false;
	activacion_titulo2 = false;
	tamx = 0, tamy = 0;
	activacion_titulo1 = false;
	musica_creditos_activada = false;
	activacion_titulo3 = false;
	resaltar_cancion1 = false;
	resaltar_cancion2 = false;
	resaltar_cancion3 = false;
	
}

//Animaciones varias de los menus-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::animaciones()
{
	//bote estrella
	angulo_bote += 0.05f; // velocidad del bote
	if (angulo_bote > 2 * 3.14159f)
		angulo_bote = 0.0f;

	bote = sin(angulo_bote) * 1.0f;

	//Creditos
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
		playMusica("sonidos/Musica1.mp3", true);
		musica_actual = 0;
	}

	
}
 
//Para dibujar-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::dibuja()
{
	//Estella de la muerte
	if (estado != CREDITOS)
	{
		Estrella.setPos(-16, 0 + bote);
		Estrella.draw();
		Estrella.setSize(20, 25);
	}

	//Boton de sonido
	if (pulsado_sonido == 0)
	{
		if (resaltar_altavoz == 0)
		{
			BotonSonido.setPos(40, 29);
			BotonSonido.draw();
		}
		else
		{
			BotonSonido1_5.setPos(40, 29);
			BotonSonido1_5.draw();
		}
		BotonSonido.setPos(40, 29);
		BotonSonido.draw();
		BotonSonido.setSize(5, 5);
	}
	else
	{
		if (resaltar_altavoz == 0)
		{
			BotonSonido2.setPos(40, 29);
			BotonSonido2.draw();
		}
		else
		{
			BotonSonido2_5.setPos(40, 29);
			BotonSonido2_5.draw();
		}
		BotonSonido2.setPos(40, 29);
		BotonSonido2.draw();
	}

	//Boton de exit
	if (resaltar_salida == 0)
	{
		BotonSalida.setPos(-32, 38);
		BotonSalida.draw();
		BotonSalida.setSize(5, 5);
	}
	else
	{
		BotonSalida2.setPos(-32, 38);
		BotonSalida2.draw();
		BotonSalida2.setSize(5, 5);
	}

	//Boton de atras
	if(estado!=INICIO)
	{
		if (resaltar_atras == 0)
		{
			BotonAtras.setPos(35, 29);
			BotonAtras.draw();
		}
		else
		{
			BotonAtras2.setPos(35, 29);
			BotonAtras2.draw();
		}
	}

	//Botones Inicio
	if (estado == INICIO) {

		if (resaltar_duelo == 0)
		{
			BotonDuelo.setPos(-30, -25);
			BotonDuelo.draw();
		}
		else
		{
			BotonDuelo2.setPos(-30, -25);
			BotonDuelo2.draw();
		}

		if (resaltar_ia == 0)
		{
			BotonIA.setPos(0, -25);
			BotonIA.draw();
		}
		else
		{
			BotonIA2.setPos(0, -25);
			BotonIA2.draw();
		}

		if (resaltar_ajustes == 0)
		{
			BotonAJUSTES.setPos(30, -25);
			BotonAJUSTES.draw();
		}
		else
		{
			BotonAJUSTES2.setPos(30, -25);
			BotonAJUSTES2.draw();
		}
	}

	//Botones AJUSTES
	if (estado == AJUSTES) {

		if (resaltar_sonido == 0)
		{
			BotonSonidoGeneral.setPos(-30, -25);
			BotonSonidoGeneral.draw();
		}
		else
		{
			BotonSonidoGeneral2.setPos(-30, -25);
			BotonSonidoGeneral2.draw();
		}

		if (resaltar_musica == 0)
		{
			BotonMusica.setPos(0, -25);
			BotonMusica.draw();
		}
		else
		{
			BotonMusica2.setPos(0, -25);
			BotonMusica2.draw();
		}

		if (resaltar_ayuda == 0)
		{
			BotonAyuda.setPos(30, -25);
			BotonAyuda.draw();
		}
		else
		{
			BotonAyuda2.setPos(30, -25);
			BotonAyuda2.draw();
		}
		if (resaltar_creditos == 0)
		{
			BotonCreditos.setPos(0, -10);
			BotonCreditos.draw();
		}
		else
		{
			BotonCreditos2.setPos(0, -10);
			BotonCreditos2.draw();
		}
	}

	//Botones AYUDA
	if (estado == AYUDA) {

		if (resaltar_normas == 0)
		{
			BotonNormas.setPos(-30, -25);
			BotonNormas.draw();
		}
		else
		{
			BotonNormas2.setPos(-30, -25);
			BotonNormas2.draw();
		}

		if (resaltar_movimientos == 0)
		{
			BotonMovimientos.setPos(30, -25);
			BotonMovimientos.draw();
		}
		else
		{
			BotonMovimientos2.setPos(30, -25);
			BotonMovimientos2.draw();
		}

	}

	//Botones MUSICA
	if (estado == MUSICA) {

		if (resaltar_cancion1 == 0)
		{
			BotonCancion1.setPos(-30, -25);
			BotonCancion1.draw();
		}
		else
		{
			BotonCancion12.setPos(-30, -25);
			BotonCancion12.draw();
		}

		if (resaltar_cancion2 == 0)
		{
			BotonCancion2.setPos(0, -25);
			BotonCancion2.draw();
		}
		else
		{
			BotonCancion22.setPos(0, -25);
			BotonCancion22.draw();
		}

		if (resaltar_cancion3 == 0)
		{
			BotonCancion3.setPos(30, -25);
			BotonCancion3.draw();
		}
		else
		{
			BotonCancion32.setPos(30, -25);
			BotonCancion32.draw();
		}
	}

	//Fondo
	if (estado != CREDITOS)
	{
		MenuInicial.draw();	
	}
	

	//Creditos
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