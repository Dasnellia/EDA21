#include <iostream>
#include "Franjahoraria.h"

FranjaHoraria::FranjaHoraria(int h, int a, int d, int me)
{
    if (a < 0 || h < 0 || d < 0 || me < 0)
    {
        anio = 0;
        hora = 0;
        dia = 0;
        mes = 0;
    }
    else
    {
        anio = a;
        hora = h;
        dia = d;
        mes = me;
    }
}

int FranjaHoraria::getHora() const { return hora; }
int FranjaHoraria::getAnio() const { return anio; }
int FranjaHoraria::getDia() const { return dia; }
int FranjaHoraria::getMes() const { return mes; }

void FranjaHoraria::setHora(int h) { hora = h; }
void FranjaHoraria::setAnio(int a) { anio = a; }
void FranjaHoraria::setDia(int d) { dia = d; }
void FranjaHoraria::setMes(int me) { mes = me; }

bool FranjaHoraria::antesDe(const FranjaHoraria &otra) const
{
    if (anio != otra.anio)
        return anio < otra.anio;
    if (mes != otra.mes)
        return mes < otra.mes;
    if (dia != otra.dia)
        return dia < otra.dia;
    return hora < otra.hora;
}

bool FranjaHoraria::igualA(const FranjaHoraria &otra) const
{
    return (anio == otra.anio &&
            mes == otra.mes &&
            dia == otra.dia &&
            hora == otra.hora);
}

int FranjaHoraria::getFechanumerica(){
    //formato debe ser yyyymmddhh, si alguien ingresa mal la fecha ya fue
    anoy= this.anio * 1000000
    mesi = mes*10000
    diaz = dia * 10
    return(anoy+mesi+diaz+h)
};
