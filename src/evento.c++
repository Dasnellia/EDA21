#include "evento.h"
#include <iostream>
#include <cstring>





Evento::Evento(const char* n, FranjaHoraria fh, Zona* z, int id_evento, int duracion)
    : FH(fh), zona(z), publicado(false), id(-1), horasduracion(duracion) {
    strncpy(Nombre, n, 59);
    Nombre[59] = '\0';
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

int Evento::getHorasDuracion() const {
    return horasduracion;
}

void Evento::setHorasDuracion(int n) {
    horasduracion = n;
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


void Evento::registrarAsistente(const Asistente& nuevo) {
    asistentesEvento.insertar(nuevo.getId());
}

void Evento::registrarAsistenciaPorID(int id) {
    if (asistentesEvento.registrarAsistenciaPorID(id))
        std::cout << "Asistencia registrada para el asistente ID: " << id << std::endl;
    else
        std::cout << "Asistente con ID " << id << " no encontrado en este evento." << std::endl;
}

void Evento::mostrarAsistentes() const {
    asistentesEvento.mostrar();
}

void Evento::mostrarVIPs() const {
    asistentesEvento.mostrarSoloVIPs();
}
