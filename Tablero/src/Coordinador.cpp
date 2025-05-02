#include "Coordinador.h"

void Coordinador::setTablero(Tablero* t)
{
	tablero = t;
}

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
	//Raton y botones
	resaltar_duelo = false;
	resaltar_ia = false;
	resaltar_ajustes = false;
	resaltar_salida = false;
	resaltar_altavoz = false;
	//si no ponemos lo de arriba se queda con el color resaltado
	if (x >= 21 && x <= 127 && y >= 18 && y <= 38)
	{

		resaltar_salida = true;
	}
	if (x >= 1816 && x <= 1895 && y >= 23 && y <= 76)
	{

		resaltar_altavoz = true;
	}
	if (x >= 122 && x <= 452 && y >= 915 && y <= 1024)
	{
		//estado = DUELO;
		resaltar_duelo = true;
	}
	if (x >= 795 && x <= 1125 && y >= 916 && y <= 1025)
	{
		//estado = IA;
		resaltar_ia = true;
	}
	if (x >= 1466 && x <= 1796 && y >= 917 && y <= 1025)
	{
		//estado = AJUSTES;
		resaltar_ajustes = true;
	}
}

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

Coordinador::Coordinador()
{
	//Vamos a utilizar esta parte de codigo para especificar en que estado estamos
	estado = INICIO;
	//Reseteamos los botones para que salga bien el "resaltar"
	resaltar_duelo = false;
	resaltar_ia = false;
	resaltar_ajustes = false;
}

//bote de la estrella y aumento del tamaño
void Coordinador::boteEstrella()
{

	angulo_bote += 0.05f; // velocidad del bote
	if (angulo_bote > 2 * 3.14159f)
		angulo_bote = 0.0f;

	bote = sin(angulo_bote) * 1.0f;
	
}

void Coordinador::dibuja() 
{
	//Estella de la muerte
	Estrella.draw();
	Estrella.setPos(-16, 0 + bote );
	Estrella.setSize(20, 25);

	
	//Boton de sonido
	if (resaltar_altavoz == 0)
	{
		BotonSonido.draw();
		BotonSonido.setPos(40, 29);
	}
	else
	{
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

		MenuInicial.draw();
		

	}
}