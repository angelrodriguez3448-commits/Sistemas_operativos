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

int main()
{
    cout << "--Simulador de procesamiento por Lotes con Multiprogramacion--\n\n";
    Lista<Proceso> ListaProcs;
    Lista<Proceso> ListaLoteAct;
    Lista<Proceso> ListaTerminados;
    NodoLista<Proceso>* AuxiliarLote;
    NodoLista<Proceso>* AuxiliarEjec;
    NodoLista<Proceso>* AuxiliarResul;
    NodoLista<Proceso>* ObjSig;
    int Oper, Num1, Num2, Tiemp;
    int NumProcs, i, j, interrupcion, ProcTer, LotesR, TiempG;
    float NumLot, ResulProc;
    srand(time(NULL));
    bool BanderaError = false;
    bool LoteTerminado = true;
    bool BanderaRegreso = false;
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
        Proceso ObjProc(Oper, Num1, Num2, Tiemp, i, 0);
        //cout << ObjProc;
        ListaProcs.InsertaOrdenCrec(ObjProc);
    }
    //system("pause");

    AuxiliarLote = ListaProcs.RegresaPrimero();

    ProcTer = 0;
    NumLot = ((4 - NumProcs % 4) + NumProcs) / 4;
    TiempG = 0;

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
                BanderaRegreso = true;
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
        Proceso ObjProc;
        Proceso* PObjProc;

        //Hace una lista auxiliar para cada lote
        if (LoteTerminado == true){
            ListaLoteAct = Lista<Proceso>();
            AuxiliarLote = ListaProcs.RegresaPrimero();
            if (NumProcs > 1){
                for (i = 0; i < ProcTer && AuxiliarLote->RegresaLiga() != NULL; i++){
                    AuxiliarLote = AuxiliarLote->RegresaLiga(); // Recorre el apuntador al inicio de cada lote
                }
            }
            for (i = 0; i < 4; i++){
                ObjProc = AuxiliarLote->RegresaInfo();
                ListaLoteAct.InsertaOrdenCrec(ObjProc);
                if (AuxiliarLote->RegresaLiga() == NULL){
                    i = 4;
                } else {
                    AuxiliarLote = AuxiliarLote->RegresaLiga();
                }
            }
            AuxiliarLote = ListaLoteAct.RegresaPrimero();
            AuxiliarEjec = ListaLoteAct.RegresaPrimero();
        }

        AuxiliarLote = ListaLoteAct.RegresaPrimero();
        //Recorrer apuntador
        if (AuxiliarLote->RegresaLiga() != NULL){
            AuxiliarLote = AuxiliarLote->RegresaLiga(); // ahora apunta al 2o del lote
        } else{
            AuxiliarLote = ListaLoteAct.RegresaPrimero();
        }
        AuxiliarEjec = ListaLoteAct.RegresaPrimero();

        //Verificar si ya se acabaron los lotes
        if (ProcTer == NumProcs) {
                Terminado = true;
        }

        LotesR = (NumLot - 1)- (ProcTer/4);
        cout << "\nLotes restantes: " << LotesR;
        //Lotes en ejecucion
        cout << "\nLote en ejecucion\n";
        while(AuxiliarLote != NULL && AuxiliarEjec->RegresaLiga() != NULL){
            ObjProc = AuxiliarLote->RegresaInfo();
            cout << "\nID: " << ObjProc.RegresaID();
            cout << "\tTME: " << ObjProc.RegresaTiempo();
            cout << "\tT Transcurrido: " << ObjProc.RegresaTiempoTrans();
            AuxiliarLote = AuxiliarLote->RegresaLiga();
        };

        //Impresion del proceso en ejecucion
        cout << "\n\nPorceso en ejecucion\n";
        ObjProc = AuxiliarEjec->RegresaInfo();
        PObjProc = AuxiliarEjec->RegresaApun();

       //Imprime el proceso en ejecucion
        if (Terminado != true){
            //Caso por si se ordena un error
            if (BanderaError == true){
                PObjProc->CambiarError(BanderaError);
                BanderaError = false;
                PObjProc->CambiarTiempo(PObjProc->RegresaTiempo());
            }

            if (PObjProc->RegresaTiempoTrans() < PObjProc->RegresaTiempo()){
                if (PObjProc->RegresaTiempoTrans() != 0){
                    TiempG = TiempG + 1;
                }

                //Caso por si se ordena un cambio de proceso
                if (BanderaRegreso != true){
                    cout << *PObjProc;
                    cout << "\tTiempo transcurrido: " << PObjProc->RegresaTiempoTrans() << "\n";
                    cout << "Tiempo restante: " << (PObjProc->RegresaTiempo() - PObjProc->RegresaTiempoTrans()) << "\n";
                    PObjProc->CambiarTiempo(PObjProc->RegresaTiempoTrans() + 1);
                    cout << "\n";
                } else{ //Cambio de contexto
                    ObjSig = AuxiliarEjec->RegresaLiga();
                    ObjProc = AuxiliarEjec->RegresaInfo();
                    ListaLoteAct.EliminaUnNodo(ObjProc);
                    ListaLoteAct.InsertaFinal(ObjProc);
                    if(ObjSig != NULL){
                        AuxiliarEjec = ObjSig;
                    } else{
                        AuxiliarEjec = ListaLoteAct.RegresaPrimero();
                    }
                    BanderaRegreso = false;
                }
            } else if (PObjProc->RegresaTiempoTrans() == PObjProc->RegresaTiempo()){ //Caso para cuando el proceso a terminado
                ProcTer++;
                TiempG = TiempG + 1;
                ObjSig = AuxiliarEjec->RegresaLiga();
                ObjProc = AuxiliarEjec->RegresaInfo();
                ListaLoteAct.EliminaUnNodo(ObjProc);
                ListaTerminados.InsertaFinal(ObjProc);
                if (ObjSig != NULL){
                    AuxiliarEjec = AuxiliarEjec->RegresaLiga();
                } else {
                    AuxiliarEjec = ListaLoteAct.RegresaPrimero();
                }
            }
        }

        if (ObjSig == NULL && ObjProc.RegresaTiempoTrans() == ObjProc.RegresaTiempo()){
                LoteTerminado = true;
        } else{
                LoteTerminado = false;
        }

        int cLote = 0;
        //Procesos terminados
        cout << "\nProcesos terminados: " << ProcTer;
        AuxiliarResul = ListaTerminados.RegresaPrimero();
        for(j = 0; j < ProcTer; j++){

            if (j %4 == 0){
                cLote++;
            }
            ObjProc = AuxiliarResul->RegresaInfo();
            cout << "\nLote: " << cLote;
            cout << "\tID programa: " << ObjProc.RegresaID();
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

            if (AuxiliarResul->RegresaLiga() != NULL){
                AuxiliarResul = AuxiliarResul->RegresaLiga();
            }
        }

        cout << "\nContador global: " << TiempG;
        cout << "\n";
        sleep(1);

    } while(Terminado == false);
    system("pause");

    return 0;
}
