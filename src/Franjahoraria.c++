#include <iostream>
#include <chrono>
#include "Franjahoraria.h"
#include <iomanip>
#include <sstream>

FranjaHoraria::FranjaHoraria() {
    // Constructor por defecto que inicializa a 0
    anio = 0;
    hora = 0;
    dia = 0;
    mes = 0;
    fechaHora = {};
    fechaHora.tm_year = anio - 1900;
    fechaHora.tm_mon = mes - 1;
    fechaHora.tm_mday = dia;
    fechaHora.tm_hour = hora;
}

FranjaHoraria::FranjaHoraria(int h, int a, int d, int me) {
    if (a < 0 || h < 0 || d < 0 || me < 0) {
        std::cerr << "Advertencia: Se ingresaron valores negativos. Inicializando en 0.\n";
        anio = 0;
        hora = 0;
        dia = 0;
        mes = 0;
    } else {
        anio = a;
        hora = h;
        dia = d;
        mes = me;
    }
    fechaHora = {};
fechaHora.tm_year = anio - 1900;
fechaHora.tm_mon = mes - 1;
fechaHora.tm_mday = dia;
fechaHora.tm_hour = hora;

}

FranjaHoraria::FranjaHoraria(int fechacompleta) {
    anio = fechacompleta / 1000000;
    mes  = (fechacompleta / 10000) % 100;
    dia  = (fechacompleta / 100) % 100;
    hora = fechacompleta % 100;
    fechaHora = {};
fechaHora.tm_year = anio - 1900;
fechaHora.tm_mon = mes - 1;
fechaHora.tm_mday = dia;
fechaHora.tm_hour = hora;

}





int FranjaHoraria::getHora() const { return hora; }
int FranjaHoraria::getAnio() const { return anio; }
int FranjaHoraria::getDia() const { return dia; }
int FranjaHoraria::getMes() const { return mes; }

void FranjaHoraria::setHora(int h) { 
    hora = h; 
    fechaHora.tm_hour = hora;
}
void FranjaHoraria::setAnio(int a) { 
    anio = a; 
    fechaHora.tm_year = anio - 1900;
}
void FranjaHoraria::setDia(int d) { 
    dia = d; 
    fechaHora.tm_mday = dia;
}
void FranjaHoraria::setMes(int me) { 
    mes = me; 
    fechaHora.tm_mon = mes - 1;
}



bool FranjaHoraria::igualA(const FranjaHoraria &otra) const
{
    return (anio == otra.anio &&
            mes == otra.mes &&
            dia == otra.dia &&
            hora == otra.hora);
}





bool FranjaHoraria::antesDe(const FranjaHoraria &otra) const {
    std::tm t1 = fechaHora;
    std::tm t2 = otra.fechaHora;

    auto time1 = std::mktime(&t1);
    auto time2 = std::mktime(&t2);

    return time1 < time2;
}

int FranjaHoraria::getFechanumerica() const {
    char buffer[12]; // YYYYMMDDHH formato
    std::strftime(buffer, sizeof(buffer), "%Y%m%d%H", &fechaHora);
    return std::stoi(buffer);
}
std::tm FranjaHoraria::getTm() const {
    return fechaHora;
}

