#include <iostream>
using namespace std;

#include "Franjahoraria.h"
#include "evento.h"
#include <unordered_map>
#include <algorithm>

// AVL DE LA PROFA PERO LO MODIFIQUE PA SIRVA CON FECHAS.
//  EN SI NO DEBERIA PERO SE ME HACIA MAS FACIL ENTENDERLO. IGUAL LO

struct NodoFecha
{
    int fechaID;
    FranjaHoraria franjaHoraria;
    std::unordered_map<int, Evento *> eventos; // Eventos organizados por ID
    int factor_balance;
    NodoFecha *izq;
    NodoFecha *der;
    NodoFecha *padre;

    NodoFecha(const FranjaHoraria &fh)
        : fechaID(fh.getFechanumerica()), franjaHoraria(fh), factor_balance(0), izq(nullptr), der(nullptr), padre(nullptr) {}

    NodoFecha(int fecha1)
        : fechaID(fecha1),
          franjaHoraria(FranjaHoraria(fecha1)),
          factor_balance(0),
          izq(nullptr),
          der(nullptr),
          padre(nullptr) {}

    bool agregarEvento(Evento *evento);
    bool esDisponible(const FranjaHoraria &nuevaFH) const;
};

// Clase �rbol AVL
class ArbolAVL
{
private:
    NodoFecha *raiz;

    // M�todos privados
    NodoFecha *insertarRecursivo(NodoFecha *nodo, int val);
    int calcularAltura(NodoFecha *nodo);
    void actualizarFactor(NodoFecha *nodo);
    NodoFecha *rebalance(NodoFecha *nodo);
    NodoFecha *rotarIzquierda(NodoFecha *nodo);
    NodoFecha *rotarDerecha(NodoFecha *nodo);
    void mostrarEchado(NodoFecha *nodo, int nivel);

public:
    ArbolAVL() : raiz(nullptr) {}
    void insertar(const FranjaHoraria &fh);
    void mostrar();
};

// M�todo insertar (p�blico)
void ArbolAVL::insertar(const FranjaHoraria &fh)
{
    int fechaID = fh.getFechanumerica();
    raiz = insertarRecursivo(raiz, fechaID);
}

// Inserci�n recursiva
NodoFecha *ArbolAVL::insertarRecursivo(NodoFecha *nodo, int val)
{
    if (!nodo)
        return new NodoFecha(val);

    if (val < nodo->fechaID)
    {
        nodo->izq = insertarRecursivo(nodo->izq, val);
        nodo->izq->padre = nodo;
    }
    else
    {
        nodo->der = insertarRecursivo(nodo->der, val);
        nodo->der->padre = nodo;
    }

    // Actualizar balance y rebalancear si es necesario
    actualizarFactor(nodo);
    return rebalance(nodo);
}

// M�todo para calcular la altura de un nodo
int ArbolAVL::calcularAltura(NodoFecha *nodo)
{
    if (!nodo)
        return 0;
    return 1 + max(calcularAltura(nodo->izq), calcularAltura(nodo->der));
}

// Actualizar el factor de balance
void ArbolAVL::actualizarFactor(NodoFecha *nodo)
{
    nodo->factor_balance = calcularAltura(nodo->izq) - calcularAltura(nodo->der);
}

// M�todo de rebalance
NodoFecha *ArbolAVL::rebalance(NodoFecha *nodo)
{
    actualizarFactor(nodo);

    // Caso: Desbalance por izquierda
    if (nodo->factor_balance > 1)
    {
        if (nodo->izq && nodo->izq->factor_balance < 0)
        {
            nodo->izq = rotarIzquierda(nodo->izq);
        }
        return rotarDerecha(nodo);
    }

    // Caso: Desbalance por derecha
    if (nodo->factor_balance < -1)
    {
        if (nodo->der && nodo->der->factor_balance > 0)
        {
            nodo->der = rotarDerecha(nodo->der);
        }
        return rotarIzquierda(nodo);
    }

    return nodo;
}

// Rotaci�n a la izquierda
NodoFecha *ArbolAVL::rotarIzquierda(NodoFecha *nodo)
{
    NodoFecha *nuevaRaiz = nodo->der;
    nodo->der = nuevaRaiz->izq;
    if (nuevaRaiz->izq)
        nuevaRaiz->izq->padre = nodo;

    nuevaRaiz->izq = nodo;
    nuevaRaiz->padre = nodo->padre;
    nodo->padre = nuevaRaiz;

    // Actualizar balance
    actualizarFactor(nodo);
    actualizarFactor(nuevaRaiz);

    return nuevaRaiz;
}

// Rotaci�n a la derecha
NodoFecha *ArbolAVL::rotarDerecha(NodoFecha *nodo)
{
    NodoFecha *nuevaRaiz = nodo->izq;
    nodo->izq = nuevaRaiz->der;
    if (nuevaRaiz->der)
        nuevaRaiz->der->padre = nodo;

    nuevaRaiz->der = nodo;
    nuevaRaiz->padre = nodo->padre;
    nodo->padre = nuevaRaiz;

    // Actualizar balance
    actualizarFactor(nodo);
    actualizarFactor(nuevaRaiz);

    return nuevaRaiz;
}

// Mostrar el �rbol de forma visual (Echado)
void ArbolAVL::mostrar()
{
    if (!raiz)
    {
        cout << "El �rbol est� vac�o." << endl;
        return;
    }
    mostrarEchado(raiz, 0);
}

void ArbolAVL::mostrarEchado(NodoFecha *nodo, int nivel)
{
    if (nodo)
    {
        mostrarEchado(nodo->der, nivel + 1);
        for (int i = 0; i < nivel; i++)
            cout << "    ";
        cout << nodo->fechaID << " (" << nodo->factor_balance << ")\n";
        mostrarEchado(nodo->izq, nivel + 1);
    }
}

bool NodoFecha::esDisponible(const FranjaHoraria &nuevaFH) const
{
    for (const auto &pair : eventos)
    {
        Evento *eventoExistente = pair.second;
        if (eventoExistente->getFranjaHoraria().igualA(nuevaFH) ||
            eventoExistente->getFranjaHoraria().antesDe(nuevaFH))
        {
            return false;
        }
    }
    return true;
}

NodoFecha* buscar(int fechaID) {
    NodoFecha* actual = raiz;
    while (actual) {
        if (fechaID == actual->fechaID) return actual;
        actual = (fechaID < actual->fechaID) ? actual->izq : actual->der;
    }
    return nullptr;
}


bool NodoFecha::agregarEvento(Evento *evento)
{
    int eventoInicio = evento->getFranjaHoraria().getFechanumerica();
    int eventoFin = eventoInicio + evento->getHorasDuracion();

    for (const auto &pair : eventos)
    {
        Evento *eventoExistente = pair.second;
        int existenteInicio = eventoExistente->getFranjaHoraria().getFechanumerica();
        int existenteFin = existenteInicio + eventoExistente->getHorasDuracion();

        // Revisar solapamiento de horarios
        if ((eventoInicio >= existenteInicio && eventoInicio < existenteFin) ||
            (eventoFin > existenteInicio && eventoFin <= existenteFin))
        {
            return false; // Conflicto de horario
        }
    }

    // Si es disponible, agregar el evento
    eventos[evento->getId()] = evento;
    return true;
}

// Funci�n principal
int main()
{

    Evento* nuevoEvento = new Evento(1, "Reunión", fh2, 2); // Asume duración de 2h
NodoFecha* nodo = arbol.buscar(fh2.getFechanumerica());

if (nodo && nodo->agregarEvento(nuevoEvento)) {
    cout << "Evento agregado con éxito." << endl;
} else {
    cout << "Conflicto de horario o fecha no encontrada." << endl;
}


    ArbolAVL arbol;

    FranjaHoraria f1(10, 2025, 15, 6);  // 15 junio 2025, 10am
    FranjaHoraria f2(8, 2025, 14, 6);   // 14 junio 2025, 8am
    FranjaHoraria f3(12, 2025, 16, 6);  // 16 junio 2025, 12pm

    arbol.insertar(f1);
    arbol.insertar(f2);
    arbol.insertar(f3);

    cout << "Árbol AVL (Visualizado):" << endl;
    arbol.mostrar();

    NodoFecha* buscado = arbol.buscar(fh2.getFechanumerica());
if (buscado) {
    cout << "Fecha encontrada: " << buscado->fechaID << endl;
} else {
    cout << "No se encontró la fecha." << endl;
}


    return 0;
}
