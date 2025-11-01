#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include "Lista.h"
#include "Proceso.h"
using namespace std;

int main()
{
    cout << "--Simulador de procesamiento por Lotes--\n\n";
    Lista<Proceso> ListaProcs;
    NodoLista<Proceso>* AuxiliarLote;
    NodoLista<Proceso>* AuxiliarEjec;
    NodoLista<Proceso>* AuxiliarResul;
    NodoLista<Proceso>* Existe;
    Proceso ObjProc;
    Proceso ObjExis;
    int NumProcs, i, x, j, id, ProcTer, TiempG;
    float NumLot, ResulProc;

    bool Terminado = false;

    do{
        cout << "\nIngrese el numero de procesos que se realizaran: ";
        cin >> NumProcs;
    } while (NumProcs <= 0);


    //Ciclo para solicitar procesos
    for (i = 0; i < NumProcs; i++){
        cout << "\nIngrese datos del proceso a capturar:\n";
        cin >> ObjProc;
         Existe = ListaProcs.BuscaOrdenada(ObjProc);
        //Ciclo para confirmar el ID
        while (Existe != nullptr){
            cout << "\nYa existe un proceso con ese ID.\n";
            cout << "Ingrese el ID del proceso: ";
            cin >> id;
            ObjProc.CambiarID(id);

            Existe = ListaProcs.BuscaOrdenada(ObjProc);
        }
        ListaProcs.InsertaOrdenCrec(ObjProc);
        cout << "\nProceso registrado exitosamente.\n";
    }

    AuxiliarLote = ListaProcs.RegresaPrimero();
    if (NumProcs > 1){
        AuxiliarLote = AuxiliarLote->RegresaLiga();
    }
    AuxiliarEjec = ListaProcs.RegresaPrimero();
    ProcTer = 0;
    NumLot = NumProcs / 4;
    TiempG = 0;
    x = 0;

    //Ciclo para imprimir los lotes y porcesos
    do{
        system("cls");

        cout << "\nLotes restantes: " << ceil(NumLot) - (ProcTer/4);
        //Lotes en ejecucion
        cout << "\nLote en ejecucion\n";

        if (NumProcs > 1 && ProcTer != (NumProcs - 1) && ProcTer < NumProcs) {
                if ( ((ProcTer > 0) && ProcTer % 3 != 0) || ProcTer == 0){
                    for (i = 0; i < (3 - ProcTer % 3); i++){
                        ObjProc = AuxiliarLote->RegresaInfo();
                        cout << "\n" << ObjProc.RegresaNombre();
                        cout << "\n" << ObjProc.RegresaTiempo();

                        if (AuxiliarLote->RegresaLiga() == NULL){
                            i = 3;
                        } else {
                            AuxiliarLote = AuxiliarLote->RegresaLiga();
                        }
                    }
                }
        }

        //Proceso en ejecucion
        cout << "\n\nPorceso en ejecucion\n";
        ObjProc = AuxiliarEjec->RegresaInfo();
        if (x < ObjProc.RegresaTiempo()){
            cout << ObjProc;
            cout << "Tiempo transcurrido: " << x << "\n";
            cout << "Tiempo restante: " << (ObjProc.RegresaTiempo() - x) << "\n";
            if (x != 0){
                TiempG = TiempG + 1;
            }
            x++;
            cout << "\n";
        } else if (x == ObjProc.RegresaTiempo()){
            ProcTer++;
            x++;
            TiempG = TiempG + 1;
            if (AuxiliarEjec->RegresaLiga() != NULL){
                AuxiliarEjec = AuxiliarEjec->RegresaLiga();
                x = 0;
            } else {
            Terminado = true;
            }
        } else {
            Terminado = true;
        }

        //Procesos terminados
        cout << "\nProcesos terminados: " << ProcTer;
        AuxiliarResul = ListaProcs.RegresaPrimero();
        for(j = 0; j < ProcTer; j++){
            ObjProc = AuxiliarResul->RegresaInfo();
            cout << "\nID programa: " << ObjProc.RegresaID();
            cout << "\nOperacion: " << ObjProc.RegresaNumero(1);
            switch(ObjProc.RegresaOperador()){
            case 1:
                cout << " + ";
                ResulProc = ObjProc.RegresaNumero(1) + ObjProc.RegresaNumero(2);
                break;
            case 2:
                cout << " - ";
                ResulProc = ObjProc.RegresaNumero(1) - ObjProc.RegresaNumero(2);
                break;
            case 3:
                cout << " * ";
                ResulProc = ObjProc.RegresaNumero(1) * ObjProc.RegresaNumero(2);
                break;
            case 4:
                cout << " / ";
                ResulProc = ObjProc.RegresaNumero(1) / ObjProc.RegresaNumero(2);
                break;
            case 5:
                cout << " % ";
                ResulProc = ObjProc.RegresaNumero(1) % ObjProc.RegresaNumero(2);
                break;
            case 6:
                cout << " ^ ";
                ResulProc = pow(ObjProc.RegresaNumero(1), ObjProc.RegresaNumero(2));
                break;
            }
            cout << ObjProc.RegresaNumero(2);
            cout << "\nResultado: " << setprecision(2) << ResulProc << "\n";
            if (AuxiliarResul->RegresaLiga() != NULL){
                AuxiliarResul = AuxiliarResul->RegresaLiga();
            }
        }

        AuxiliarLote = ListaProcs.RegresaPrimero();
        for(j = 0; j < ProcTer + 1; j++){
            if (AuxiliarLote->RegresaLiga() == NULL){
                j = ProcTer + 1;
            } else {
                AuxiliarLote = AuxiliarLote->RegresaLiga();
            }
        }

        cout << "\nContador global: " << TiempG;
        cout << "\n";
        sleep(1);

    } while (Terminado == false);
    system("pause");

    return 0;
}
