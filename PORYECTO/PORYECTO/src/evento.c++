#include "Evento.h"
#include <iostream>
#include <cstring>

// Definición del método setNombre
void Evento::setNombre(const char* n) {
    strncpy(Nombre, n, 59);
    Nombre[59] = '\0';
}

// Definición del método setFranjaHoraria
void Evento::setFranjaHoraria(const FranjaHoraria& fh) {
    FH = fh;
}

// Definición del método setZona
void Evento::setZona(Zona* zon) {
    zona = zon;
}

// Definición del método setPublicado
void Evento::setPublicado(bool publicar) {
    publicado = publicar;
}

// Definición del método setId
void Evento::setId(int id_evento) {
    id = id_evento;
}

// Definición del método getNombre
const char* Evento::getNombre() const {
    return Nombre;
}

// Definición del método getFranjaHoraria
FranjaHoraria Evento::getFranjaHoraria() const {
    return FH;
}

// Definición del método getZona
Zona* Evento::getZona() const {
    return zona;
}

// Definición del método isPublicado
bool Evento::isPublicado() const {
    return publicado;
}

// Definición del método getId
int Evento::getId() const {
    return id;
}

// Método para mostrar información del evento
void Evento::mostrarEvento() const {
    std::cout << "Evento: " << Nombre << ", Publicado: " << (publicado ? "Sí" : "No") 
              << ", ID: " << id << std::endl;
    
    // Mostrar información de la zona si está asignada
    if (zona) {
        zona->mostrarInfo();
    } else {
        std::cout << "No hay zona asignada." << std::endl;
    }
}
