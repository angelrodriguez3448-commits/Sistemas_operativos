// Definición de la clase Proceso. Se sobrecargan algunos operadores
// para que objetos de esta clase puedan ser usados de manera directa.
// Esta clase se guarda en la biblioteca "Proceso.h"

#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

class Proceso {
private:
    int ID;
    int Operador;
    int Numero1;
    int Numero2;
    int Tiempo;
    int TiempoTrans;
    bool Error;

public:
    Proceso();
    Proceso(int, int, int, int, int, int);
    int RegresaOperador();
    int RegresaNumero(int);
    int RegresaTiempo();
    int RegresaTiempoTrans();
    void CambiarTiempo(int);
    int RegresaID();
    void CambiarID(int);
    bool RegresaError();
    void CambiarError(bool);
    int operator == (Proceso);
    int operator != (Proceso);
    int operator > (Proceso);
    int operator < (Proceso);
    friend ostream& operator << (ostream&, Proceso&);
};

// Declaración del método constructor por omisión
Proceso::Proceso() {
    // Constructor vacío
}

// Declaración del método constructor con parámetros
Proceso::Proceso(int Oper, int Num1,  int Num2, int Tiemp, int Id, int TiempT) {
    Operador = Oper;
    Numero1 = Num1;
    Numero2 = Num2;
    Tiempo = Tiemp;
    ID = Id;
    TiempoTrans = TiempT;
}

//Metodo que regresa el valor del atributo Operador
int Proceso::RegresaOperador() {
    return Operador;
}

// Método que regresa el valor de alguno de los atributos Numero
int Proceso::RegresaNumero(int indice) {
    if (indice == 1)
        return Numero1;
    else
        return Numero2;
}

//Metodo que regresa el valor del atributo Tiempo
int Proceso::RegresaTiempo() {
    return Tiempo;
}

//Metodo que regresa el valor del atributo Tiempo transcurrido
int Proceso::RegresaTiempoTrans() {
    return TiempoTrans;
}

//Metodo que cambia el valor del atributo Tiempo transcurrido
void Proceso::CambiarTiempo(int tiempo){
    TiempoTrans = tiempo;
}

//Metodo que regresa el valor del atributo ID
int Proceso::RegresaID() {
    return ID;
}

//Metodo que cambia el valor del atributo ID
void Proceso::CambiarID(int id){
    ID = id;
}

//Metodo que regresa el valor del atributo Error
bool Proceso::RegresaError() {
    return Error;
}

//Metodo que cambia el valor del atributo Error
void Proceso::CambiarError(bool error){
    Error = error;
}

// Método para comparar si un producto es mayor que otro (clave)
int Proceso::operator > (Proceso Proc) {
    return ID > Proc.ID;
}

// Método para comparar si un producto es menor que otro (clave)
int Proceso::operator < (Proceso Proc) {
    return ID < Proc.ID;
}

// Método para comparar si dos procesos son iguales (ID)
int Proceso::operator == (Proceso Proc) {
    return ID == Proc.ID;
}

//Método que permite comparar dos procesos para determinar si son distintos.
int Proceso::operator != (Proceso Proc)
{
    int Resp = 0;
    if (ID != Proc.ID) Resp = 1;
    return Resp;
}

// Sobrecarga del operador << para permitir impresión con cout
ostream& operator << (ostream& Escribe, Proceso& ObjProc) {
    Escribe << "\n\nDatos del proceso\n";
    Escribe << "ID del proceso: " << ObjProc.ID;
    Escribe << "\tOperacion: " << ObjProc.Numero1;
    switch(ObjProc.Operador){
    case 1:
        Escribe << " + ";
        break;
    case 2:
        Escribe << " - ";
        break;
    case 3:
        Escribe << " * ";
        break;
    case 4:
        Escribe << " / ";
        break;
    case 5:
        Escribe << " % ";
        break;
    case 6:
        Escribe << " ^ ";
        break;
    }
    Escribe << ObjProc.Numero2;
    return Escribe;
}


