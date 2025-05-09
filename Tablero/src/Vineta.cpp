#include "Vineta.h"


void Vineta::dibujar()
{
    
	vineta.draw();
    tablero.draw();
    fondo.draw();    
    mostrarTextoAnimado("Peones y torres mover�s, joven padawan. Pero recordar\n debes : la mente, tu arma m�s poderosa es.", 0.1, -15, -18);
   
    
}

void Vineta::mostrarTextoAnimado(const std::string& texto, float deltaTiempo, float posX, float posY)
{
    // Si es un texto nuevo, inicializa las variables
    if (textoCompleto != texto)
    {
        playMusica("sonidos/Sonido_Yoda.mp3", true);
        textoCompleto = texto;
        textoMostrado = "";
        indiceTexto = 0;
        tiempoAcumulado = 0.0f;
        textoTerminado = false;
    }

    // Si no ha terminado, sigue a�adiendo letras
    if (!textoTerminado)
    {
        tiempoAcumulado += deltaTiempo;

        if (indiceTexto < textoCompleto.size() && tiempoAcumulado >= velocidadTexto)
        {
            textoMostrado += textoCompleto[indiceTexto];
            indiceTexto++;
            tiempoAcumulado = 0.0f;
        }

        if (indiceTexto >= textoCompleto.size())
        {
            playMusica("sonidos/Sonido_Yoda.mp3", false);
            textoTerminado = true;
        }
    }

    // Dibujar: dividimos el texto por saltos de l�nea '\n'
    std::istringstream ss(textoMostrado);
    std::string linea;
    float desplazamientoY = 0.0f;
    const float saltoLinea = 3.0f;  // Ajusta seg�n el tama�o de la fuente

    

    while (std::getline(ss, linea, '\n'))
    {
        ETSIDI::setTextColor(255, 255, 0);  // Blanco
        ETSIDI::setFont("fuentes/STARWARS.ttf", 24);
        ETSIDI::printxy(linea.c_str(), posX, posY - desplazamientoY);
        desplazamientoY += saltoLinea;  // Baja una l�nea para la siguiente
    }
}