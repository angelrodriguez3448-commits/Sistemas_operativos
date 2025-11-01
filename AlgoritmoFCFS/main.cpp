#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include "Lista.h"
#include "Proceso.h"
using namespace std;

int main(){
    cout << "--Simulador de algoritmo de planificacion FCFS--\n\n";
    Lista<Proceso> ListaNuevos; //Equivlae a ListaProcs
    Lista<Proceso> ListaListos; //Equivale a ListaLote
    Lista<Proceso> ListaTerminados;
    Lista<Proceso> ListaBloqueados;
    NodoLista<Proceso>* AuxiliarListos; //Equivale a AuxiliarLote
    NodoLista<Proceso>* AuxiliarEjec;
    NodoLista<Proceso>* AuxiliarResul;
    NodoLista<Proceso>* AuxiliarBloq;
    NodoLista<Proceso>* ObjSig;
    Proceso ObjProc;
    Proceso* PObjProc;
    int Oper, Num1, Num2, Tiemp;
    int NumProcs, i, j, interrupcion, EspaciosLL, ProcTer, ProcR /*Equivale a LotesR*/, TiempG;
    float ResulProc;
    srand(time(NULL));
    bool BanderaError = false;
    bool BanderaBloqueado = false;
    bool Terminado = false;

    //Solicitud de procesos
    do{
        cout << "\nIngrese el numero de procesos que se realizaran: ";
        cin >> NumProcs;
    } while (NumProcs <= 0);

    //Ciclo para rellenar la lista de procesos
    for (i = 1; i <= NumProcs; i++){
        do{
            Oper = rand() % 7; //Genera valores del 0 al 6
        }while(Oper == 0); //Valida que el operador no sea 0
        Num1 = rand() % 1001; //Genera valores del 0 al 1000
        do{
            Num2 = rand() % 1001;
        }while(Num2 == 0 && (Oper == 4 || Oper == 5)); //Valida que el segundo operando no sea 0 cuando se va a realizar una division o residuo
        do{
            Tiemp = rand() % 21; //Genera valores del 0 al 20
        } while(Tiemp < 4); //Valida que el TME no sea menor a 5
        Proceso ObjProc(Oper, Num1, Num2, Tiemp, i);
        ListaNuevos.InsertaOrdenCrec(ObjProc);
    }

    AuxiliarListos = ListaNuevos.RegresaPrimero();
    ProcR = NumProcs;
    ProcTer = 0;
    TiempG = 0;
    EspaciosLL = 0;

    //Ciclo principal
    do{
        //Detectar si se a pulsado una tecla
        if(kbhit() != 0){
            char tecla = getch();
            interrupcion = 0;

            if (tecla == 'e' || tecla == 'E'){
                interrupcion = 1;
            }else if(tecla == 'w' || tecla == 'W'){
                interrupcion = 2;
            }else if(tecla == 'p' || tecla == 'P'){
                interrupcion = 3;
            }else if(tecla == 'c' || tecla == 'C'){
                interrupcion = 4;
            }

            //Switch para evaluar interrupciones
            switch(interrupcion){
            case 1:
                //cout << "Rregresar el proceso a su lote\n";
                BanderaBloqueado = true;
                break;
            case 2:
                //Error
                BanderaError = true;
                break;
            case 3:
                //Pausa
                cout << "Pausa, pulsa C para continuar\n";
                do{
                    if(kbhit() != 0){
                        char tecla = getch();
                        interrupcion = 0;

                        if(tecla == 'c' || tecla == 'C'){
                            interrupcion = 4;
                        }
                    }
                }while(interrupcion != 4);
                break;
            case 4:
                //Continuar no hace nada afuera de Puasa
                break;
            }
            interrupcion = 0;
        }

        system("cls");

        //Hace una lista auxiliar para porcesos listos
        if (ListaNuevos.RegresaPrimero() != NULL){
            AuxiliarListos = ListaNuevos.RegresaPrimero();
            while (EspaciosLL < 4){
                PObjProc = AuxiliarListos->RegresaApun();
                PObjProc->CambiarTiempoLl(TiempG);
                ObjProc = AuxiliarListos->RegresaInfo();
                /*ObjProc = AuxiliarListos->RegresaInfo()*/;
                ListaListos.InsertaOrdenCrec(ObjProc);
                if (AuxiliarListos->RegresaLiga() == NULL){
                    EspaciosLL = 4;
                } else {
                    EspaciosLL++;
                    AuxiliarListos = AuxiliarListos->RegresaLiga();
                }
                ListaNuevos.EliminaUnNodo(ObjProc);
                ProcR--;
            }
            AuxiliarListos = ListaListos.RegresaPrimero();
            AuxiliarEjec = ListaListos.RegresaPrimero();
        }

        AuxiliarListos = ListaListos.RegresaPrimero();
        //Recorrer apuntador
        if(AuxiliarListos != NULL){
            if (AuxiliarListos->RegresaLiga() != NULL){
            AuxiliarListos = AuxiliarListos->RegresaLiga(); // ahora apunta al 2o del lote
            } else{
                AuxiliarListos = ListaListos.RegresaPrimero();
            }
            AuxiliarEjec = ListaListos.RegresaPrimero();
        } else{
            AuxiliarEjec = NULL;
        }


        //Verificar si ya se acabaron los lotes
        if (ProcTer == NumProcs) {
                Terminado = true;
        }

        cout << "\nProcesos en cola de Nuevos: " << ProcR;
        //Procesos Listos
        cout << "\nCola de listos\n";
        while(AuxiliarListos != NULL && AuxiliarEjec->RegresaLiga() != NULL){
            ObjProc = AuxiliarListos->RegresaInfo();
            cout << "\nID: " << ObjProc.RegresaID();
            cout << "\tTME: " << ObjProc.RegresaTiempo();
            cout << "\tT Transcurrido: " << ObjProc.RegresaTiempoTrans();
            AuxiliarListos = AuxiliarListos->RegresaLiga();
        };

        //Impresion del proceso en ejecucion
        cout << "\n\nPorceso en ejecucion\n";

       //Imprime el proceso en ejecucion
        if (Terminado != true && AuxiliarEjec != NULL){
            ObjProc = AuxiliarEjec->RegresaInfo();
            PObjProc = AuxiliarEjec->RegresaApun();
            if (PObjProc->RegresaTiempoR() == -1){
                PObjProc->CambiarTiempoR(TiempG - PObjProc->RegresaTiempoLl());
            }
            //Caso por si se ordena un error
            if (BanderaError == true){
                PObjProc->CambiarError(BanderaError);
                BanderaError = false;
                //PObjProc->CambiarTiempo(PObjProc->RegresaTiempo());
            }

            if (PObjProc->RegresaTiempoTrans() < PObjProc->RegresaTiempo() && PObjProc->RegresaError() != true){
                if (PObjProc->RegresaTiempoTrans() != 0){
                    TiempG = TiempG + 1;
                }

                //Caso por si se ordena un cambio de proceso
                if (BanderaBloqueado != true){
                    cout << *PObjProc;
                    cout << "\tTiempo transcurrido: " << PObjProc->RegresaTiempoTrans() << "\n";
                    cout << "Tiempo restante: " << (PObjProc->RegresaTiempo() - PObjProc->RegresaTiempoTrans()) << "\n";
                    PObjProc->CambiarTiempo(PObjProc->RegresaTiempoTrans() + 1);
                    cout << "\n";
                } else{ //Cambio de contexto
                    ObjSig = AuxiliarEjec->RegresaLiga();
                    ObjProc = AuxiliarEjec->RegresaInfo();
                    ListaListos.EliminaUnNodo(ObjProc);
                    ListaBloqueados.InsertaFinal(ObjProc);
                    if(ObjSig != NULL){
                        AuxiliarEjec = ObjSig;
                    } else{
                        AuxiliarEjec = ListaListos.RegresaPrimero();
                    }
                    BanderaBloqueado = false;
                }
            } else if (PObjProc->RegresaTiempoTrans() == PObjProc->RegresaTiempo() || PObjProc->RegresaError() == true){ //Caso para cuando el proceso a terminado
                ProcTer++;
                TiempG = TiempG + 1;
                EspaciosLL--;
                PObjProc->CambiarTiempoF(TiempG);
                ObjSig = AuxiliarEjec->RegresaLiga();
                ObjProc = AuxiliarEjec->RegresaInfo();
                ListaListos.EliminaUnNodo(ObjProc);
                ListaTerminados.InsertaFinal(ObjProc);
                if (ObjSig != NULL){
                    AuxiliarEjec = AuxiliarEjec->RegresaLiga();
                } else {
                    AuxiliarEjec = ListaListos.RegresaPrimero();
                }
            }
        }

        //Procesos bloqueados
        cout << "\nProcesos bloqueados\n";
        if(ListaBloqueados.RegresaPrimero() != NULL){
            AuxiliarBloq = ListaBloqueados.RegresaPrimero();

            while(AuxiliarBloq != NULL){
                PObjProc = AuxiliarBloq->RegresaApun();
                cout << "ID: " << PObjProc->RegresaID() << "\t";
                cout << "Tiempo Bloqueado: " << PObjProc->RegresaTiempoB() << "\n";
                PObjProc->CambiarTiempoB(PObjProc->RegresaTiempoB() + 1);

                ObjSig = AuxiliarBloq->RegresaLiga();
                if(PObjProc->RegresaTiempoB() > 8){
                    PObjProc->CambiarTiempoB(0);
                    ObjProc = AuxiliarBloq->RegresaInfo();
                    ListaBloqueados.EliminaUnNodo(ObjProc);
                    ListaListos.InsertaFinal(ObjProc);
                }
                AuxiliarBloq = ObjSig;
            }
        }

        //Procesos terminados
        cout << "\nProcesos terminados: " << ProcTer;
        AuxiliarResul = ListaTerminados.RegresaPrimero();
        for(j = 0; j < ProcTer; j++){
            ObjProc = AuxiliarResul->RegresaInfo();
            cout << "\nID proceso: " << ObjProc.RegresaID();
            cout << "\tOperacion: " << ObjProc.RegresaNumero(1);
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
            if (ObjProc.RegresaError() != true){
                cout << "\tResultado: " << ResulProc << "\n";
            } else {
                cout << "\tResultado: Error\n";
            }

            //Tiempos
            /*cout << "T llegada: " << ObjProc.RegresaTiempoLl();
            cout << "\tT Finalizacion: " << ObjProc.RegresaTiempoF();
            cout << "\tT Retorno: " << ObjProc.RegresaTiempoF() - ObjProc.RegresaTiempoLl();
            cout << "\nT Respuesta: " << ObjProc.RegresaTiempoR();
            cout << "\tT Espera: " << (ObjProc.RegresaTiempoF() - ObjProc.RegresaTiempoLl()) - ObjProc.RegresaTiempoTrans();
            cout << "\tT Servicio: " << ObjProc.RegresaTiempoTrans();
            */

            if (AuxiliarResul->RegresaLiga() != NULL){
                AuxiliarResul = AuxiliarResul->RegresaLiga();
            }
        }

        cout << "\nContador global: " << TiempG;
        cout << "\n";
        sleep(1);

    }while(Terminado == false);
    cout << "Continuar con tabla de tiempos\n";
    system("pause");
    system("cls");
    cout << left << setw(4)  << "ID"
        << setw(11) << "Operacion"
        << setw(10) << "Resultado"
        << setw(16) << "T Llegada"
        << setw(16) << "T Finalizacion"
        << setw(16) << "T Retorno"
        << setw(16) << "T Respuesta"
        << setw(16) << "T Espera"
        << setw(16) << "T Servicio"
        << "\n";

     AuxiliarResul = ListaTerminados.RegresaPrimero();
        for(j = 0; j < ProcTer; j++){
            ObjProc = AuxiliarResul->RegresaInfo();
            cout << left << setw(4)  << ObjProc.RegresaID();
            cout << left << setw(4) << ObjProc.RegresaNumero(1);
            switch(ObjProc.RegresaOperador()){
            case 1:
                cout << "+ ";
                ResulProc = ObjProc.RegresaNumero(1) + ObjProc.RegresaNumero(2);
                break;
            case 2:
                cout << "- ";
                ResulProc = ObjProc.RegresaNumero(1) - ObjProc.RegresaNumero(2);
                break;
            case 3:
                cout << "* ";
                ResulProc = ObjProc.RegresaNumero(1) * ObjProc.RegresaNumero(2);
                break;
            case 4:
                cout << "/ ";
                ResulProc = ObjProc.RegresaNumero(1) / ObjProc.RegresaNumero(2);
                break;
            case 5:
                cout << "% ";
                ResulProc = ObjProc.RegresaNumero(1) % ObjProc.RegresaNumero(2);
                break;
            case 6:
                cout << "^ ";
                ResulProc = pow(ObjProc.RegresaNumero(1), ObjProc.RegresaNumero(2));
                break;
            }
            cout << left << setw(5) << ObjProc.RegresaNumero(2);
            if (ObjProc.RegresaError() != true){
                cout << left << setw(10) << ResulProc;
            } else {
                cout << left << setw(10) << "Error";
            }
            cout << left << setw(16) << ObjProc.RegresaTiempoLl()
                << setw(16) << ObjProc.RegresaTiempoF()
                << setw(16) << (ObjProc.RegresaTiempoF() - ObjProc.RegresaTiempoLl())
                << setw(16) << ObjProc.RegresaTiempoR()
                << setw(16) << (ObjProc.RegresaTiempoF() - ObjProc.RegresaTiempoLl()) - ObjProc.RegresaTiempoTrans()
                << setw(16) << ObjProc.RegresaTiempoTrans()
                << "\n";

            if (AuxiliarResul->RegresaLiga() != NULL){
                AuxiliarResul = AuxiliarResul->RegresaLiga();
            }
        }

}
