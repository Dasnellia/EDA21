#include "Evento.h"
#include <iostream>
#include <cstring>


Evento:Evento(const char* n = "", FranjaHoraria fh = FranjaHoraria(), Zona* z = nullptr, int id_evento = 0,int horasduracion )
        : FH(fh), zona(z), publicado(false), id(id_evento) {
        strncpy(Nombre, n, 59);
        Nombre[59] = '\0';
        horasduracion = horasduracion
    }

void Evento::setNombre(const char* n) {
    strncpy(Nombre, n, 59);
    Nombre[59] = '\0';
}

void Evento::setFranjaHoraria(const FranjaHoraria& fh) {
    FH = fh;
}

void Evento::setZona(Zona* zon) {
    zona = zon;
}

void Evento::setPublicado(bool publicar) {
    publicado = publicar;
}

void Evento::setId(int id_evento) {
    id = id_evento;
}

const char* Evento::getNombre() const {
    return Nombre;
}

FranjaHoraria Evento::getFranjaHoraria() const {
    return FH;
}

Zona* Evento::getZona() const {
    return zona;
}

bool Evento::isPublicado() const {
    return publicado;
}

int Evento::getId() const {
    return id;
}

int getHorasDuracion() const {
    return Evento.horasduracion;
}

void Evento::setHorasDuracion(int n){
    Evento.horasduracion = n
}


void Evento::mostrarEvento() const {
    std::cout << "Evento: " << Nombre 
              << ", Publicado: " << (publicado ? "Sí" : "No") 
              << ", ID: " << id 
              << ", Duración: " << horasduracion << " horas" << std::endl;

    if (zona != nullptr) {
        zona->mostrarInfo();
    } else {
        std::cout << "No hay zona asignada." << std::endl;
    }
}
