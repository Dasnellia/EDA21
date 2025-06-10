#include <iostream>
#include <cstring>
#include "zona.h"

Zona::Zona(int a = 0, const char *ubi = "", int t = 0)
{
    aforo = a;
    strncpy(ubicacion, ubi, 49);
    ubicacion[49] = '\0';
    lleno = false;
    tamanio = t;
}

void Zona::mostrarInfo() const
{
    std::cout << "Ubicación: " << ubicacion << ", Aforo: " << aforo
              << ", Tamaño: " << tamanio << ", Lleno: " << (lleno ? "Sí" : "No") << std::endl;
}
