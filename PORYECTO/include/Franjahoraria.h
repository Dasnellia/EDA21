#include <iostream>
#ifndef FRANJAHORARIA_H
#define FRANJAHORARIA_H
#include <ctime>

class FranjaHoraria
{
private:
    int idEvento;
    int hora;
    int anio;
    int dia;
    int mes;

public:
    FranjaHoraria(int h, int a, int d, int me);

    int getHora() const;
    int getAnio() const;
    int getDia() const;
    int getMes() const;

    void setHora(int h);
    void setAnio(int a);
    void setDia(int d);
    void setMes(int me);

    bool antesDe(const FranjaHoraria &otra);

    bool igualA(const FranjaHoraria &otra);

    int regresarFechanumerica();
};

#endif