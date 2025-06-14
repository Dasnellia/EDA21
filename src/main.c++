


#include <iostream>
#include <cstring>
#include "hashtableevento.h"

int main() {
    Evento techConf("TechConf", FranjaHoraria(10, 2025, 20, 6), nullptr, 101, 3);

    // Creamos asistentes
    Asistente a1("0001", "Lucía", "Gómez", 5, "VIP");
    Asistente a2("0002", "Carlos", "Rey", 6, "Normal");
    Asistente a3("0003", "Ana", "Paz", 7, "VIP");

    // Los registramos en el evento
    techConf.registrarAsistente(a1);
    techConf.registrarAsistente(a2);
    techConf.registrarAsistente(a3);

    // Simulamos que Carlos asistió
    techConf.registrarAsistenciaPorID(6);

    // Mostramos asistentes registrados
    std::cout << "\nLista completa de asistentes:\n";
    techConf.mostrarAsistentes();

    // Mostramos solo los VIP
    std::cout << "\nAsistentes VIP:\n";
    techConf.mostrarVIPs();

    return 0;
}
