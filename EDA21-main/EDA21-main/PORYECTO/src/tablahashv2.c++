#include <iostream>
#include <string>
#include <stdlib.h>     // Para new y delete
#include <limits>       // Para numeric_limits
#include "Evento.h"

using namespace std;

int tam,  valor, cant = 0;
Evento* tablaHash;

//seria muy bueno si lo hacemos tipo clase Tabla Hash, pero no tngo tiempo
void inicializarTabla();
void insertarClave(Evento nuevoEvento);
int calcularHash(string clave);
void insertarEnHash(int hash);
void mostrarTablaHash();



int main()
{
    tam = 1000;
    tablaHash = new Evento[tam]();
    inicializarTabla();

    return 0;
}


void inicializarTabla()
{
    
    for (int i = 0; i < tam; i++)
        tablaHash[i] = Evento();

}


void insertarClave(Evento nuevoEvento)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string clave;

    clave = nuevoEvento.getNombre();
    valor = nuevoEvento.getId();

    cout << "La clave es: " << clave << " cuyo valor es: " << valor << endl;

    int suma = calcularHash(clave);
    insertarEnHash(suma, nuevoEvento);

    mostrarTablaHash();
}


int calcularHash(string clave)
{
    int suma = 0;
    for (char c : clave)
    {
        cout << c << ", valor: " << (int)c << "\n";
        suma += (int)c;
    }
    cout << "La suma es: " << suma << endl;
    return suma;
}


void insertarEnHash(int suma, Evento nuevoEvento)
{
    int i = 1, indice = suma % tam;
    do
    {
        if (tablaHash[indice].getId() == -1)
        {
            tablaHash[indice] = nuevoEvento;
            cant++;
            break;
        }
        else
        {
            indice = (suma + i) % tam;
            i++;
            cout << "\nHay colisión, nueva posición: " << indice << endl;
        }
    } while (i <= tam);
}

int devolverId(string clave)
{
    int suma = calcularHash(clave);
    int i = 0, indice = suma % tam;

    do
    {
        if (strcmp(tablaHash[indice].getNombre(), clave.c_str()) == 0)

        {
            return tablaHash[indice].getId();
        }
        else
        {
            indice = (suma + i) % tam;
            i++;
        }
    } while (i < tam);

    return -1; 
}

void mostrarTablaHash()
{
    cout << "\nMostrar la tabla Hash con exploración lineal **\n";
    for (int i = 0; i < tam; i++) {
        if (tablaHash[i].getId() != -1) {
            cout << "[" << i << "] ";
            cout << "[" << tablaHash[i].getNombre << "] ";
            cout << "[" << tablaHash[i].getZona << "] ";
            tablaHash[i].mostrarEvento();
        }
    }
    
}


