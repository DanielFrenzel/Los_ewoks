#include "Vineta.h"


void Vineta::dibujar(float eX, float eY)
{
    escalaX = eX;
    escalaY = eY;
    float xf = -10*escalaX, yf = 0, xv = 0, yv = 5*escalaY;
    float tamf_x = 134.4*escalaX, tamf_y = 80.6*escalaY, tamv_x = 91*escalaX, tamv_y = 97.5*escalaY;
    Sprite* vineta = Imagen::crearImagen										//Imprime tablero
    ("imagenes/vineta.png", xv, yv, tamv_x, tamv_y);
    Sprite* fondo = Imagen::crearImagen										//Imprime tablero
    ("imagenes/fondo_esapcio_negro.png", xf, yf, tamf_x, tamf_y);
	//vineta.draw();
   // fondo.draw();    
    mostrarTextoAnimado("PARA MÍ, EL ALIADO ES LA FUERZA, Y ES UN PODEROSO ALIADO.\nLA VIDA LA CREA Y LA HACE CRECER, Y SU ENERGÍA\nNOS RODEA Y NOS UNE.\nNOSOTROS DOS, SERES LUMINOSOS SOMOS, TÚ ERES LA MATERIA\nBRUTA. Y DEBES SENTIR LA FUERZA A TU ALREDEDOR,\nAQUÍ, ENTRE TÚ Y YO.\n¿SÍ?, EL ÁRBOL, LA ROCA, POR TODAS PARTES, ¿SÍ?\nINCLUSO ENTRE LA TIERRA Y LA NAVE.", 0.02, -12*escalaX, -18*escalaY);
    ETSIDI::setTextColor(255, 255, 0);  // Blanco
    ETSIDI::setFont("fuentes/STARWARS.ttf", 10);
    ETSIDI::printxy("(CLICAR EN CUALQUIER LADO PARA CONTINUAR)", -12*escalaX, -37*escalaY);
    
}

void Vineta::mostrarTextoAnimado(const std::string& texto, float deltaTiempo, float posX, float posY)
{
    // Si es un texto nuevo, inicializa las variables
    if (textoCompleto != texto)
    {
        playMusica("sonidos/Sonido_Yoda.mp3", false);
        textoCompleto = texto;
        textoMostrado = "";
        indiceTexto = 0;
        tiempoAcumulado = 0.0f;
        textoTerminado = false;
    }

    // Si no ha terminado, sigue añadiendo letras
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
            textoTerminado = true;
        }
    }

    // Dibujar: dividimos el texto por saltos de línea '\n'
    std::istringstream ss(textoMostrado);
    std::string linea;
    float desplazamientoY = 0.0f;
    const float saltoLinea = 1.5f;  // Ajusta según el tamaño de la fuente

    

    while (std::getline(ss, linea, '\n'))
    {
        ETSIDI::setTextColor(255, 255, 0);  // Blanco
        ETSIDI::setFont("fuentes/STARWARS.ttf", 14);
        ETSIDI::printxy(linea.c_str(), posX, posY - desplazamientoY);
        desplazamientoY += saltoLinea;  // Baja una línea para la siguiente
    }
}

