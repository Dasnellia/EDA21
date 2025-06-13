#ifndef EVENTO_H
#define EVENTO_H

#include <iostream>
#include <cstring>
#include "Franjahoraria.h"
#include "Zona.h"
#include "ArbolAsistentes.h"

class Evento
{
private:
    char Nombre[60];

    FranjaHoraria FH;
    Zona *zona;
    bool publicado;
    int id;
    int horasduracion;
    ArbolAVL asistentesEvento;


public:
    Evento(const char *n = "", FranjaHoraria fh = FranjaHoraria(), Zona *z = nullptr, int id_evento = 0, int horasduracion = 0)
        : FH(fh), zona(z), publicado(false), id(id_evento), horasduracion(horasduracion)
    {
        strncpy(Nombre, n, 59);
        Nombre[59] = '\0';
    }

    void mostrarEvento() const;

    void setNombre(const char *n);
    void setFranjaHoraria(const FranjaHoraria &fh);
    void setZona(Zona *zon);
    void setPublicado(bool publicar);
    void setId(int id_evento);

    const char *getNombre() const;
    FranjaHoraria getFranjaHoraria() const;
    Zona *getZona() const;
    bool isPublicado() const;
    int getId() const;
    void registrarAsistente(const Asistente& nuevo) {
        asistentes.insertar(nuevo.getId());
    }

    void registrarAsistenciaPorID(int id) {
        if (asistentes.registrarAsistenciaPorID(id))
            std::cout << "Asistencia registrada para el asistente ID: " << id << std::endl;
        else
            std::cout << "Asistente con ID " << id << " no encontrado en este evento." << std::endl;
    }

    void mostrarAsistentes() const {
        asistentes.mostrar();
    }

    void mostrarVIPs() const {
        asistentes.mostrarSoloVIPs();
    }
};

#endif
