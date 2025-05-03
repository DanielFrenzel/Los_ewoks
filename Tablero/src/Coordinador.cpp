#include "Coordinador.h"
#include "freeglut.h"
void Coordinador::setTablero(Tablero* t)
{
	tablero = t;
}
//Movimiento del raton----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::MovRaton(int x, int y)  //Indica que casilla se ha pulsado según 
{
	int fil3 = 0, col3 = 0;
	if ((x >= 100 || x <= 700) && (y >= 0 || y <= 600))
	{
		for (int i = 0; i < 8; i++)
		{
			if ((x >= 100 + (75 * i)) && (x <= 100 + (75 * (i + 1))))
			{
				col3 = i;
			}
			if ((y >= 0 + (75 * i)) && (y <= 0 + (75 * (i + 1))))
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

	if (x >= 21 && x <= 127 && y >= 18 && y <= 38) resaltar_salida = true;
	if (x >= 1816 && x <= 1895 && y >= 23 && y <= 76) resaltar_altavoz = true;
	if (x >= 1702 && x <= 1783 && y >= 26 && y <= 74) resaltar_atras = true;
	switch (estado)
	{
	case INICIO:
		if (x >= 122 && x <= 452 && y >= 915 && y <= 1024) resaltar_duelo = true;
		if (x >= 795 && x <= 1125 && y >= 916 && y <= 1025) resaltar_ia = true;
		if (x >= 1466 && x <= 1796 && y >= 917 && y <= 1025) resaltar_ajustes = true;
		break;
	case AJUSTES:
		if (x >= 122 && x <= 452 && y >= 915 && y <= 1024) resaltar_sonido = true;
		if (x >= 795 && x <= 1125 && y >= 916 && y <= 1025) resaltar_musica = true;
		if (x >= 1466 && x <= 1796 && y >= 917 && y <= 1025) resaltar_ayuda = true;
		if (x >= 795 && x <= 1125 && y >= 664 && y <= 773) resaltar_creditos = true;
		break;
	case AYUDA:
		if (x >= 122 && x <= 452 && y >= 915 && y <= 1024) resaltar_normas = true;
		if (x >= 1466 && x <= 1796 && y >= 917 && y <= 1025) resaltar_movimientos = true;
		break;
	}


}
//para controlar el click--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (x >= 21 && x <= 127 && y >= 18 && y <= 38) exit(0);
		if (x >= 1816 && x <= 1895 && y >= 23 && y <= 76)
		{
			if (pulsado_sonido == 0)
			{
				pulsado_sonido = true;
			}
			else {
				pulsado_sonido = false;
			}
		}
		if (x >= 1702 && x <= 1783 && y >= 26 && y <= 74) estado=estado_anterior;
		if (estado == INICIO)
		{
			if (x >= 122 && x <= 452 && y >= 915 && y <= 1024)
			{
				estado_anterior = estado;
				estado = DUELO;
				return;
			}
			if (x >= 795 && x <= 1125 && y >= 916 && y <= 1025)
			{
				estado_anterior = estado;
				estado = IA;
				return;
			}
			if (x >= 1466 && x <= 1796 && y >= 917 && y <= 1025)
			{
				estado_anterior = estado;
				estado = AJUSTES;
				return;
			}
		}
		if (estado == AJUSTES)
		{
			if (x >= 122 && x <= 452 && y >= 915 && y <= 1024)
			{
				estado_anterior = estado;
				estado = SONIDO;
				return;
			}
			if (x >= 795 && x <= 1125 && y >= 916 && y <= 1025)
			{
				estado_anterior = estado;
				estado = MUSICA;
				return;
			}
			if (x >= 1466 && x <= 1796 && y >= 917 && y <= 1025)
			{
				estado_anterior = estado;
				estado = AYUDA;
				return;
			}
			if (x >= 795 && x <= 1125 && y >= 664 && y <= 773)
			{
				estado_anterior = estado;
				estado = CREDITOS;
				return;
			}
		}
		if (estado == AYUDA)
		{
			if (x >= 122 && x <= 452 && y >= 915 && y <= 1024)
			{
				estado_anterior = estado;
				estado = NORMAS;
				return;
			}
			if (x >= 1466 && x <= 1796 && y >= 917 && y <= 1025)
			{
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
}

//bote de la estrella y aumento del tamaño-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::boteEstrella()
{

	angulo_bote += 0.05f; // velocidad del bote
	if (angulo_bote > 2 * 3.14159f)
		angulo_bote = 0.0f;

	bote = sin(angulo_bote) * 1.0f;

}

//Para dibujar-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Coordinador::dibuja()
{
	//Estella de la muerte
	Estrella.draw();
	Estrella.setPos(-16, 0 + bote);
	Estrella.setSize(20, 25);

	//Boton de sonido
	if (pulsado_sonido == 0)
	{
		if (resaltar_altavoz == 0)
		{
			BotonSonido.draw();
			BotonSonido.setPos(40, 29);
		}
		else
		{
			BotonSonido1_5.draw();
			BotonSonido1_5.setPos(40, 29);
		}
		BotonSonido.draw();
		BotonSonido.setPos(40, 29);
		BotonSonido.setSize(5, 5);
	}
	else
	{
		if (resaltar_altavoz == 0)
		{
			BotonSonido2.draw();
			BotonSonido2.setPos(40, 29);
		}
		else
		{
			BotonSonido2_5.draw();
			BotonSonido2_5.setPos(40, 29);
		}
		BotonSonido2.draw();
		BotonSonido2.setPos(40, 29);
	}

	//Boton de exit
	if (resaltar_salida == 0)
	{
		BotonSalida.draw();
		BotonSalida.setPos(-32, 38);
		BotonSalida.setSize(5, 5);
	}
	else
	{
		BotonSalida2.draw();
		BotonSalida2.setPos(-32, 38);
		BotonSalida2.setSize(5, 5);
	}
	//Boton de atras
	if(estado!=INICIO)
	{
		if (resaltar_atras == 0)
		{
			BotonAtras.draw();
			BotonAtras.setPos(35, 29);
		}
		else
		{
			BotonAtras2.draw();
			BotonAtras2.setPos(35, 29);
		}
	}

	//Botones Inicio
	if (estado == INICIO) {

		if (resaltar_duelo == 0)
		{
			BotonDuelo.draw();
			BotonDuelo.setPos(-30, -25);
		}
		else
		{
			BotonDuelo2.draw();
			BotonDuelo2.setPos(-30, -25);
		}

		if (resaltar_ia == 0)
		{
			BotonIA.draw();
			BotonIA.setPos(0, -25);
		}
		else
		{
			BotonIA2.draw();
			BotonIA2.setPos(0, -25);
		}

		if (resaltar_ajustes == 0)
		{
			BotonAJUSTES.draw();
			BotonAJUSTES.setPos(30, -25);
		}
		else
		{
			BotonAJUSTES2.draw();
			BotonAJUSTES2.setPos(30, -25);
		}
	}
	//Botones AJUSTES
	if (estado == AJUSTES) {

		if (resaltar_sonido == 0)
		{
			BotonSonidoGeneral.draw();
			BotonSonidoGeneral.setPos(-30, -25);
		}
		else
		{
			BotonSonidoGeneral2.draw();
			BotonSonidoGeneral2.setPos(-30, -25);
		}

		if (resaltar_musica == 0)
		{
			BotonMusica.draw();
			BotonMusica.setPos(0, -25);
		}
		else
		{
			BotonMusica2.draw();
			BotonMusica2.setPos(0, -25);
		}

		if (resaltar_ayuda == 0)
		{
			BotonAyuda.draw();
			BotonAyuda.setPos(30, -25);
		}
		else
		{
			BotonAyuda2.draw();
			BotonAyuda2.setPos(30, -25);
		}
		if (resaltar_creditos == 0)
		{
			BotonCreditos.draw();
			BotonCreditos.setPos(0, -10);
		}
		else
		{
			BotonCreditos2.draw();
			BotonCreditos2.setPos(0, -10);
		}
	}
	//Botones AYUDA
	if (estado == AYUDA) {

		if (resaltar_normas == 0)
		{
			BotonNormas.draw();
			BotonNormas.setPos(-30, -25);
		}
		else
		{
			BotonNormas2.draw();
			BotonNormas2.setPos(-30, -25);
		}

		if (resaltar_movimientos == 0)
		{
			BotonMovimientos.draw();
			BotonMovimientos.setPos(30, -25);
		}
		else
		{
			BotonMovimientos2.draw();
			BotonMovimientos2.setPos(30, -25);
		}
	}
	//Fondo
	MenuInicial.draw();
}