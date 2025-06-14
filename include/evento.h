#ifndef EVENTO_H
#define EVENTO_H

#include <iostream>
#include <cstring>

#include "Franjahoraria.h"
#include "zona.h"
#include "avlasistente.h"
#include "asistente.h"
#include "persona.h"

class Evento
{
private:
    char Nombre[60];
    FranjaHoraria FH;
    Zona* zona;
    bool publicado;
    int id;
    int horasduracion;
    ArbolAVL asistentesEvento;

public:
    Evento(const char* n = "", FranjaHoraria fh = FranjaHoraria(), Zona* z = nullptr, int id_evento = 0, int horas_duracion = 0)
        : FH(fh), zona(z), publicado(false), id(id_evento), horasduracion(horas_duracion)
    {
        strncpy(Nombre, n, 59);
        Nombre[59] = '\0';
    }

    void mostrarEvento() const;

    void setNombre(const char* n);
    void setFranjaHoraria(const FranjaHoraria& fh);
    void setZona(Zona* zon);
    void setPublicado(bool publicar);
    void setId(int id_evento);

    const char* getNombre() const;
    FranjaHoraria getFranjaHoraria() const;
    int getHorasDuracion() const;
    void setHorasDuracion(int horas);
    Zona* getZona() const;
    bool isPublicado() const;
    int getId() const;

    void registrarAsistente(const Asistente& nuevo);

    void registrarAsistenciaPorID(int id);

    void mostrarAsistentes() const;

    void mostrarVIPs() const;
};

#endif // EVENTO_H
