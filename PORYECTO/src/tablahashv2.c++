#include <iostream>
#include <string>
#include <stdlib.h>     // Para new y delete
#include <limits>       // Para numeric_limits
   

using namespace std;

int tam, *tablaHash, valor, cant = 0;

void inicializarTabla();
void insertarClave();
int calcularHash(string clave);
void insertarEnHash(int hash);
void mostrarTablaHash();
bool deseaContinuar();

int main()
{
    cout << "Ingrese el tamaño de la tabla hash: ";
    cin >> tam;

    tablaHash = new int[tam];
    inicializarTabla();

    do
    {
        insertarClave();
    } while (deseaContinuar() && cant < tam);

    delete[] tablaHash;
    return 0;
}


void inicializarTabla()
{
    for (int i = 0; i < tam; i++)
        tablaHash[i] = -1;
}


void insertarClave()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string clave;
    cout << "Ingrese la clave: ";
    getline(cin, clave);

    cout << "Ingrese el valor: ";
    cin >> valor;

    cout << "La clave es: " << clave << " cuyo valor es: " << valor << endl;

    int suma = calcularHash(clave);
    insertarEnHash(suma);

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


void insertarEnHash(int suma)
{
    int i = 1, indice = suma % tam;
    do
    {
        if (tablaHash[indice] == -1)
        {
            tablaHash[indice] = valor;
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


void mostrarTablaHash()
{
    cout << "\nMostrar la tabla Hash con exploración lineal **\n";
    for (int i = 0; i < tam; i++)
        cout << tablaHash[i] << endl;
}


bool deseaContinuar()
{
    char respuesta;
    cout << "¿Desea ingresar otra clave (y/n)? ";
    cin >> respuesta;
    return respuesta == 'y' || respuesta == 'Y';
}
