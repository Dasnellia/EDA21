#include <iostream>
#include <cstring>
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

bool Zona::esDisponible(int fechaID, int duracionHoras) const
{
    for (Evento *evento : eventosProgramados)
    {
        int eventoInicio = evento->getFranjaHoraria().getFechanumerica();
        int eventoFin = eventoInicio + evento->getHorasDuracion();

        int nuevoEventoFin = fechaID + duracionHoras;

        // Si el nuevo evento se solapa con alguno existente, no está disponible
        if ((fechaID >= eventoInicio && fechaID < eventoFin) ||
            (nuevoEventoFin > eventoInicio && nuevoEventoFin <= eventoFin))
        {
            return false;
        }
    }
    return true;
}

void Zona::mostrarInfo() const
{
    std::cout << "Ubicación: " << (ubicacion[0] != '\0' ? ubicacion : "Ubicación no especificada")
              << ", Aforo: " << aforo
              << ", Tamaño: " << tamanio
              << ", Lleno: " << (lleno ? "Sí" : "No") << std::endl;
}
