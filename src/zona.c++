#include <iostream>
#include <cstring>
#include <ctime>
#include "zona.h"

Zona::Zona(int a, const char *ubi, int t)
{
    aforo = a;
    strncpy(ubicacion, ubi, 49);
    ubicacion[49] = '\0';
    lleno = false;
    tamanio = t;
}

int Zona::getAforo() const { return aforo; }
const char *Zona::getUbicacion() const { return ubicacion; }
bool Zona::isLleno() const { return lleno; }
int Zona::getTamanio() const { return tamanio; }

void Zona::setAforo(int a) { aforo = a; }
void Zona::setUbicacion(const char *ubi)
{
    strncpy(ubicacion, ubi, 49);
    ubicacion[49] = '\0';
}
void Zona::setLleno(bool estado) { lleno = estado; }
void Zona::setTamanio(int t) { tamanio = t; }


bool Zona::esDisponible(int fechaID, int duracionHoras) const {
    // Convertir fechaID (formato YYYYMMDDHH) a tm
    int anio  = fechaID / 1000000;
    int mes   = (fechaID / 10000) % 100;
    int dia   = (fechaID / 100) % 100;
    int hora  = fechaID % 100;

    std::tm inicioNuevo = {};
    inicioNuevo.tm_year = anio - 1900;
    inicioNuevo.tm_mon  = mes - 1;
    inicioNuevo.tm_mday = dia;
    inicioNuevo.tm_hour = hora;
    inicioNuevo.tm_min  = 0;
    inicioNuevo.tm_sec  = 0;
    inicioNuevo.tm_isdst = -1;

    time_t tiempoInicioNuevo = std::mktime(&inicioNuevo);
    time_t tiempoFinNuevo = tiempoInicioNuevo + duracionHoras * 3600;  // En segundos

    for (const Evento* evento : eventosProgramados) {
        FranjaHoraria fh = evento->getFranjaHoraria();
        std::tm inicioExistente = fh.getTm(); // Debes exponer esto en FranjaHoraria

        time_t tiempoInicioExistente = std::mktime(&inicioExistente);
        time_t tiempoFinExistente = tiempoInicioExistente + evento->getHorasDuracion() * 3600;

        // Verificar solapamiento
        if (tiempoInicioNuevo < tiempoFinExistente && tiempoFinNuevo > tiempoInicioExistente) {
            return false; // Se solapan
        }
    }

    return true; // No hay conflictos
}

void Zona::mostrarInfo() const
{
    std::cout << "Ubicación: " << (ubicacion[0] != '\0' ? ubicacion : "Ubicación no especificada")
              << ", Aforo: " << aforo
              << ", Tamaño: " << tamanio
              << ", Lleno: " << (lleno ? "Sí" : "No") << std::endl;
}
