#include "evento.h"
#include <iostream>
#include <cstring>
#include "hashtableevento.h"

Evento::Evento(const char* n, FranjaHoraria fh, Zona* z) 
    : FH(fh), zona(z), publicado(false) {
    strncpy(Nombre, n, 59);
    Nombre[59] = '\0';
}

void Evento::mostrarEvento() const {
    std::cout << "Evento: " << Nombre << ", Publicado: " << (publicado ? "Sí" : "No") << std::endl;
}
