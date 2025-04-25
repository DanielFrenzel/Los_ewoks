#include "Boton.h"
#include"iostream"

void Boton::dibuja()
{
	if (dibujado != nullptr)
		dibujado->draw();
}

void Boton::detectar(GLdouble rx, GLdouble ry)
{
	if ((rx) > (x - ancho / 2) && rx < (x + ancho / 2) &&
		(ry) >(y - alto / 2) && ry < (y + alto / 2))
		dibujado = &sprite2;
	else {
		dibujado = &sprite;
	}
}

void Boton::click(GLdouble rx, GLdouble ry)
{
	if ((rx) > (x - ancho / 2) && rx < (x + ancho / 2) &&
		(ry) >(y - alto / 2) && ry < (y + alto / 2))
	{
		if (function != nullptr)
		{
			function();
			PlaySonido(Caso_Sonido);
		}

	}
}

void Boton::PlaySonido(int caso) {

	if (mute == false)
	{
		if (caso == 1) ETSIDI::play("sonidos/impacto.wav");
	}
}



Boton::Boton(const GLdouble& Ancho, const GLdouble& Alto,
	const GLdouble& x, const GLdouble& y,
	std::string Path1, std::string Path2, int caso_sonido,
	std::function<void()> func)
	: ancho(Ancho), alto(Alto), x(x), y(y), sprite(ETSIDI::Sprite(Path1.c_str(), x, y, Ancho, Alto)),
	sprite2(ETSIDI::Sprite(Path2.c_str(), x, y, Ancho, Alto)), dibujado(nullptr), function(func), Caso_Sonido(caso_sonido)
{

}