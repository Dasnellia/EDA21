#include <iostream>
#include <string>
#include <stdlib.h>// para trabajar con funciones new y delete
#include <limits> // Para numeric_limits
#include "persona.h"

using namespace std;


int tam, *tablaHash, valor, cant;
void colision(int);

int main()
{
    char band;

    cout<<"Ingrese el tama�o de la tabla hash:";
    cin>>tam;

    tablaHash = new int[tam]; //crear el arreglo dinamico y reservar memoria para el arreglo dinamico segun la cantidad de elementos

    for(int i = 0; i< tam; i++)
    {
          *(tablaHash+i)=-1; //lo mismo que elemento[i]
    }

    do
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string clave;
        int suma = 0, indice;

        cout << "Ingrese la clave:"; //se ingresa el nombre de la persona
        getline(cin, clave);
        cout<<"Ingrese el valor:";
        cin>>valor;

        //mostrar la clave y valor
        cout<<"La clave es: "<<clave<<" cuyo valor es: "<<valor<<endl;

        //calculamos el ascii del string
        for(int i = 0; i<clave.length(); i++){
            cout<<clave[i]<<", valor: "<<(int)clave[i]<<"\n";
            suma += (int)clave[i];
        }

        cout<<"La suma es: "<<suma;


        //antes de guardarlo tiene que verificar que no haya colisi�n mediante exploraci�n lineal
        colision(suma); //para el examen se coment� esto y se agreg� la sgte instrucci�n
       // colision(valor); // es decir esta

        //mostrar la tabla hash
        cout<<"\n Mostrar la tabla Hash con exploracion lineal **\n";
        for(int i = 0; i< tam; i++)
        {
              cout<<*(tablaHash+i)<<endl; //lo mismo que elemento[i]
        }
        cout<<"Desea ingresar otra clave (y/n)?";
        cin>>band;
    }while(band == 'y' && cant < tam);


    return 0;
}


void colision(int suma)
{
    int i = 1, indice = suma % tam;
    do
    {
        if(*(tablaHash+indice)== -1)
        {
            //se inserta
            *(tablaHash+indice) = valor;
            cant++;
            break;
        }
        else
        {
             indice = (suma + i) % tam;
             i++;
             cout<<"\n Si hay colision, posicion:"<<indice<<endl;
        }
    }while(i <= tam);

}



