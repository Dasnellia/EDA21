#include <iostream>
using namespace std;
#include "asistente.h"
#include "./include/Franjahoraria.h"
#include <unordered_map>
//AVL DE LA PROFA PERO LO MODIFIQUE PA SIRVA CON FECHAS.
// EN SI NO DEBERIA PERO SE ME HACIA MAS FACIL ENTENDERLO. IGUAL LO

struct NodoFecha {
    int fechaID;
    FranjaHoraria franjaHoraria;
    std::unordered_map<int, Evento*> eventos; // Eventos organizados por ID
    int factor_balance;
    NodoFecha* izq;
    NodoFecha* der;
    NodoFecha* padre;

    NodoFecha(const FranjaHoraria& fh) 
        : fechaID(fh.getFechanumerica()), franjaHoraria(fh), factor_balance(0), izq(nullptr), der(nullptr), padre(nullptr) {}

    bool agregarEvento(Evento* evento);
    bool esDisponible(const FranjaHoraria& nuevaFH) const;
};



// Clase �rbol AVL
class ArbolAVL {
private:
    Nodo* raiz;

    // M�todos privados
    Nodo* insertarRecursivo(Nodo* nodo, int val);
    int calcularAltura(Nodo* nodo);
    void actualizarFactor(Nodo* nodo);
    Nodo* rebalance(Nodo* nodo);
    Nodo* rotarIzquierda(Nodo* nodo);
    Nodo* rotarDerecha(Nodo* nodo);
    void mostrarEchado(Nodo* nodo, int nivel);

public:
    ArbolAVL() : raiz(nullptr) {}
    void insertar(int val);
    void mostrar();
};


// M�todo insertar (p�blico)
void ArbolAVL::insertar(const FranjaHoraria& fh) {
    int fechaID = fh.getFechanumerica();
    raiz = insertarRecursivo(raiz, fechaID);
}


// Inserci�n recursiva
Nodo* ArbolAVL::insertarRecursivo(Nodo* nodo, int val) {
    if (!nodo) return new Nodo(val);

    if (val < nodo->dato) {
        nodo->izq = insertarRecursivo(nodo->izq, val);
        nodo->izq->padre = nodo;
    } else {
        nodo->der = insertarRecursivo(nodo->der, val);
        nodo->der->padre = nodo;
    }

    // Actualizar balance y rebalancear si es necesario
    actualizarFactor(nodo);
    return rebalance(nodo);
}

// M�todo para calcular la altura de un nodo
int ArbolAVL::calcularAltura(Nodo* nodo) {
    if (!nodo) return 0;
    return 1 + max(calcularAltura(nodo->izq), calcularAltura(nodo->der));
}

// Actualizar el factor de balance
void ArbolAVL::actualizarFactor(Nodo* nodo) {
    nodo->factor_balance = calcularAltura(nodo->izq) - calcularAltura(nodo->der);
}

// M�todo de rebalance
Nodo* ArbolAVL::rebalance(Nodo* nodo) {
    actualizarFactor(nodo);

    // Caso: Desbalance por izquierda
    if (nodo->factor_balance > 1) {
        if (nodo->izq && nodo->izq->factor_balance < 0) {
            nodo->izq = rotarIzquierda(nodo->izq);
        }
        return rotarDerecha(nodo);
    }

    // Caso: Desbalance por derecha
    if (nodo->factor_balance < -1) {
        if (nodo->der && nodo->der->factor_balance > 0) {
            nodo->der = rotarDerecha(nodo->der);
        }
        return rotarIzquierda(nodo);
    }

    return nodo;
}

// Rotaci�n a la izquierda
Nodo* ArbolAVL::rotarIzquierda(Nodo* nodo) {
    Nodo* nuevaRaiz = nodo->der;
    nodo->der = nuevaRaiz->izq;
    if (nuevaRaiz->izq) nuevaRaiz->izq->padre = nodo;

    nuevaRaiz->izq = nodo;
    nuevaRaiz->padre = nodo->padre;
    nodo->padre = nuevaRaiz;

    // Actualizar balance
    actualizarFactor(nodo);
    actualizarFactor(nuevaRaiz);

    return nuevaRaiz;
}

// Rotaci�n a la derecha
Nodo* ArbolAVL::rotarDerecha(Nodo* nodo) {
    Nodo* nuevaRaiz = nodo->izq;
    nodo->izq = nuevaRaiz->der;
    if (nuevaRaiz->der) nuevaRaiz->der->padre = nodo;

    nuevaRaiz->der = nodo;
    nuevaRaiz->padre = nodo->padre;
    nodo->padre = nuevaRaiz;

    // Actualizar balance
    actualizarFactor(nodo);
    actualizarFactor(nuevaRaiz);

    return nuevaRaiz;
}

// Mostrar el �rbol de forma visual (Echado)
void ArbolAVL::mostrar() {
    if (!raiz) {
        cout << "El �rbol est� vac�o." << endl;
        return;
    }
    mostrarEchado(raiz, 0);
}

void ArbolAVL::mostrarEchado(Nodo* nodo, int nivel) {
    if (nodo) {
        mostrarEchado(nodo->der, nivel + 1);
        for (int i = 0; i < nivel; i++) cout << "    ";
        cout << nodo->dato << " (" << nodo->factor_balance << ")\n";
        mostrarEchado(nodo->izq, nivel + 1);
    }
}

bool NodoFecha::esDisponible(const FranjaHoraria& nuevaFH) const {
    for (const auto& pair : eventos) {
        Evento* eventoExistente = pair.second;
        if (eventoExistente->getFranjaHoraria().igualA(nuevaFH) ||
            eventoExistente->getFranjaHoraria().antesDe(nuevaFH)) {
            return false;
        }
    }
    return true;
}


bool NodoFecha::agregarEvento(Evento* evento) {
    int eventoInicio = evento->getFranjaHoraria().getFechanumerica();
    int eventoFin = eventoInicio + evento->getHorasDuracion();

    for (const auto& pair : eventos) {
        Evento* eventoExistente = pair.second;
        int existenteInicio = eventoExistente->getFranjaHoraria().getFechanumerica();
        int existenteFin = existenteInicio + eventoExistente->getHorasDuracion();

        // Revisar solapamiento de horarios
        if ((eventoInicio >= existenteInicio && eventoInicio < existenteFin) ||
            (eventoFin > existenteInicio && eventoFin <= existenteFin)) {
            return false; // Conflicto de horario
        }
    }

    // Si es disponible, agregar el evento
    eventos[evento->getId()] = evento;
    return true;
}


// Funci�n principal
int main() {
    ArbolAVL arbol;
    


    cout << "Arbol AVL (Visualizado):" << endl;
    arbol.mostrar();

    return 0;
}
