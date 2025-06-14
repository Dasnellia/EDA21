#include <unordered_map>
#include "evento.h"

class HashTableEvento {
private:
    std::unordered_map<int, Evento*> eventos; // Tabla hash de eventos por ID

public:
    void agregarEvento(int id, Evento* evento) {
        eventos[id] = evento;
    }

    Evento* obtenerEvento(int id) {
        return eventos.count(id) ? eventos[id] : nullptr;
    }

    void eliminarEvento(int id) {
        eventos.erase(id);
    }
};
