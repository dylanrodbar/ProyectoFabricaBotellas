#include "prueba.h"
#include <sys/types.h>
#include <pthread.h>
#include <QDebug>
//#include <QTest>
#include <QtCore>
#include <windows.h>
#include <stdlib.h> //Para poner pausa
#include <time.h>



hiloInterfaz *hiloTemposs = new hiloInterfaz();





//Definición de los tamaños fijos
#define NUM_THREADS     6
#define NUM_Colas       6

//Definición de las variables enteras
int azar=100;
int numeroCajas =1;
int cuentaCajas = 0;

//Definición de los array
Cola *colas[NUM_Colas];    //Array para guardar las colas de control
EstructuraFuncion *estructuras[NUM_Colas];  //Array para guardar las estructuras asociadas a hilos
pthread_t *hilos[NUM_THREADS];   //Array para guardar los hilos



//Declaración de la lista doblemente enlazada circular y la lista doblemente enlazada

ListaDobleCircular *listaCir = new ListaDobleCircular(); //Almacenamiento de las botellas
ListaDobleEnlazada *listaDob = new ListaDobleEnlazada(); //Almacenamiento de las prioridades
ListaDobleCircular *listaDatos = new ListaDobleCircular(); //Almacenamiento temporal para manejo de los datos

//********************************************************

//Declaración de variables para aprobado y rechazado
int rechazo = 0;
int aprobacion = 0;

//************************************************************************************************************

Prueba::Prueba()

{
}
//iniciarDatos:
//Entradas: nombre, prioridad, rechazo y el identificador(I.D)
//Salidas: ninguna
//Restricciones: ninguna

void Prueba::iniciarDatos(QString nombre, int prioridad, int rechazo, int identificador)
{

    listaCir->insertarAlInicio(nombre, rechazo, identificador);
    listaDatos->insertarAlInicio(nombre, rechazo, identificador);
    listaDob->insertarAlInicio(prioridad);
}
//funcionPrincipal:
//Entradas: hilo
//Salidas: ninguna
//Restricciones: ninguna

//Hilos..........................................................

void *Prueba::funcionPrincipal(void * hiloarg)
{

    EstructuraFuncion * datos;
    datos = (EstructuraFuncion *) hiloarg;
    while(datos->activo == true)
    {


        if(datos->tipo==1)
        {
            while(datos->pausa==true)
            {
                Sleep(100);
            }
            while(datos->primeraCola->max==datos->primeraCola->numElemento) //Valida que si la cola está llena, entonces que se pause
            {
                Sleep(100);
            }

            Nodo *temporalDoble;
            Nodo *temporal = datos->l->retornarPrimerNodo();
            temporalDoble = listaDob->primerNodo;    //nodo que tomará los datos de la lista doble
            srand(time(NULL));
            int valor = rand()%azar+1;  //Toma un valor aleatorio entre 1 y 100
            int priori = temporalDoble->prioridad;
            while(priori<valor)
            {

                temporalDoble=temporalDoble->siguiente;
                temporal=temporal->siguiente;
                priori+=temporalDoble->prioridad;

            }



                datos->primeraCola->encolar(temporal->nombre, temporal->rechazo, temporal->identificador); //La progra se cae cuando se encola
                hiloTemposs->actualizarColas(datos->primeraCola->numElemento, 1);
                hiloTemposs->maquinas(temporal->identificador, 6);
                Sleep(datos->tiempo*1000);

            }



        else if(datos->tipo==2)
        {
            Nodo *temporal;
            srand(time(NULL));
            int valor = rand()%azar+1;

            while(datos->pausa==true)
            {
                Sleep(100);
            }
            while(datos->primeraCola->numElemento==0)//Comprueba que si la cola está vacía, entonces estará en pausa
            {
                Sleep(100);
            }
            while(datos->segundaCola->max==datos->segundaCola->numElemento && datos->terceraCola->max==datos->terceraCola->numElemento)//Si las colas asociadas están llenas
            {                                                                                   //entonces estará en pausa
             Sleep(100);
            }

            if(valor % 2 == 0)
            {
                if(datos->segundaCola->max!=datos->segundaCola->numElemento)
                {
            temporal = datos->primeraCola->verFrente();
            datos->segundaCola->encolar(temporal->nombre, temporal->rechazo, temporal->identificador); //da un error al intentar encolar el nodo
            hiloTemposs->actualizarColas(datos->segundaCola->numElemento, 2);
            datos->primeraCola->desencolar();
            hiloTemposs->actualizarColas(datos->primeraCola->numElemento, 1);
             }
            }
            else
            {

            if(datos->terceraCola->max!=datos->terceraCola->numElemento)
             {
            temporal = datos->primeraCola->verFrente();
            datos->terceraCola->encolar(temporal->nombre, temporal->rechazo, temporal->identificador);  //da un error al tratar en encolar el nodo
            hiloTemposs->actualizarColas(datos->terceraCola->numElemento, 3);
            datos->primeraCola->desencolar();
            hiloTemposs->actualizarColas(datos->primeraCola->numElemento, 1);
              }
              }
            hiloTemposs->maquinas(temporal->identificador, 1);
            Sleep(datos->tiempo*1000);

        }
        else if(datos->tipo==3)
        {
            while(datos->pausa==true)
            {
                Sleep(100);
            }
            while(datos->primeraCola->numElemento==0)
            {
                Sleep(100);
            }
            while(datos->segundaCola->max==datos->segundaCola->numElemento)
            {
             Sleep(100);
            }
         if(datos->primeraCola->numElemento!=0)
         {
         Nodo * temporal = datos->primeraCola->verFrente();
         datos->segundaCola->encolar(temporal->nombre, temporal->rechazo, temporal->identificador);
         hiloTemposs->actualizarColas(datos->segundaCola->numElemento, 4);
         datos->primeraCola->desencolar();//Quita un elemento de la cola 0
         hiloTemposs->actualizarColas(datos->primeraCola->numElemento, 2);
         hiloTemposs->maquinas(temporal->identificador, 2);
         Sleep(datos->tiempo*1000);
         }
        }
        else if(datos->tipo==4)
        {
            while(datos->pausa==true)
            {
                Sleep(100);
            }
            while(datos->primeraCola->numElemento==0)
            {
                Sleep(100);
            }
            while(datos->segundaCola->max==datos->segundaCola->numElemento)
            {
             Sleep(100);
            }
         if(datos->primeraCola->numElemento!=0)
         {
             Nodo * temporal = datos->primeraCola->verFrente();
         datos->segundaCola->encolar(temporal->nombre, temporal->rechazo, temporal->identificador);
         hiloTemposs->actualizarColas(datos->segundaCola->numElemento, 4);
         datos->primeraCola->desencolar();//Quita un elemento de la cola 0
         hiloTemposs->actualizarColas(datos->primeraCola->numElemento, 3);
         hiloTemposs->maquinas(temporal->identificador, 3);
         Sleep(datos->tiempo*1000);
         }
        }
        else if(datos->tipo==5)
        {
            while(datos->pausa==true)
            {
                Sleep(100);
            }
            while(datos->primeraCola->numElemento==0)
            {
                Sleep(100);
            }
            while(datos->segundaCola->max==datos->segundaCola->numElemento)
            {
             Sleep(100);
            }

         if(datos->primeraCola->numElemento!=0)
         {
         Nodo * probar = datos->primeraCola->verFrente(); //Ponerlo de primero
         datos->segundaCola->encolar(probar->nombre, probar->rechazo, probar->identificador);
         hiloTemposs->colas(datos->primeraCola->numElemento, 5);
         datos->primeraCola->desencolar();//Quita un elemento de la cola 0
         hiloTemposs->colas(datos->primeraCola->numElemento, 4);
         hiloTemposs->maquinas(probar->identificador, 4);

         Sleep(datos->tiempo*1000);
         }
        }
        else if(datos->tipo==6)  //Este se encarga de encolar la cola relacionada al camión que se lleva las botellas
        {
         while(datos->pausa==true)
         {
             Sleep(100);
         }
         while(datos->primeraCola->numElemento==0)
         {
             Sleep(100);
         }
         Nodo * temporal = datos->primeraCola->verFrente();
         int rechazo = Prueba::devolverRechazo(temporal->identificador);
         srand(time(NULL));
         int valor = rand()%100+1;
         if(valor <= rechazo)
         {
           rechazo+=1;
           hiloTemposs->aprobados(temporal->identificador, true);
         }
         else
         {
             datos->segundaCola->encolar(temporal->nombre ,temporal->rechazo,temporal->identificador);
             hiloTemposs->aprobados(temporal->identificador, false);
             aprobacion+=1;
             //Encolar la cola para el camión
         }
         if(datos->segundaCola->numElemento == datos->segundaCola->max)
         {
             hiloTemposs->actualizarCamion(0);
             datos->segundaCola->numElemento = 0;
             datos->segundaCola->frente = NULL;
             datos->segundaCola->final = NULL;
             cuentaCajas += 1;
             if(cuentaCajas == numeroCajas)
             {
                 hiloTemposs->actualizarCamion(1);
                 cuentaCajas = 0;
             }
         }
         datos->primeraCola->desencolar();
         hiloTemposs->maquinas(temporal->identificador, 5);
         hiloTemposs->colas(datos->segundaCola->numElemento, 6);
         Sleep(datos->tiempo*1000);
        }



}
    return NULL;
}

//Hilos...........................................................................

//iniciarFabrica
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna


//Creación de hilos..............................
void Prueba:: iniciarFabrica()
{

    for(int i=0; i<NUM_THREADS; i++)
    {
        pthread_create(hilos[i], NULL,
        Prueba::funcionPrincipal, (void *)estructuras[i]);
    }


}

//iniciarEstructuras
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna

//Estructuras..................................................
void Prueba:: iniciarEstructuras()
{
    for(int i = 0; i<NUM_THREADS; i++)
    {
        if(i == 0)  //Una cola
        {
            EstructuraFuncion * e = new EstructuraFuncion(i+1,listaCir,colas[0]);
            estructuras[i] = e;
            estructuras[i]->tiempo=1;
        }
        else if(i == 1)  //Tres colas
        {
            EstructuraFuncion * e = new EstructuraFuncion(i+1,listaCir,colas[0],colas[1],colas[2]);
            estructuras[i] = e;
            estructuras[i]->tiempo=1;
        }
        else if(i == 2) //Dos colas
        {
            EstructuraFuncion * e = new EstructuraFuncion(i+1,listaCir,colas[1], colas[3]);
            estructuras[i] = e;
            estructuras[i]->tiempo=1;
        }
        else if (i == 3) //Dos colas
        {
            EstructuraFuncion * e = new EstructuraFuncion(i+1,listaCir,colas[2],colas[3]);
            estructuras[i] = e;
            estructuras[i]->tiempo=1;
        }
        else if (i == 4)//Dos colas
        {
            EstructuraFuncion * e = new EstructuraFuncion(i+1,listaCir,colas[3],colas[4]);
            estructuras[i] = e;
            estructuras[i]->tiempo=1;
        }
        else if (i == 5)//Una cola
        {
            EstructuraFuncion * e = new EstructuraFuncion(i+1,listaCir, colas[4], colas[5]);
            estructuras[i] = e;
            estructuras[i]->tiempo=1;
        }

    }
}
//iniciarColas
//Entradas: ninguna
//Salidas: ninguna
//Restricciones: ninguna

void Prueba:: iniciarColas()
{

    for(int n=0; n<NUM_Colas; n++)
    {
     colas[n] = new Cola(0, 15);
    }
}


void Prueba::pausar(int tipo)
{
      estructuras[tipo]->pausa=true;

}

void Prueba::reiniciar(int tipo)

{
      estructuras[tipo]->pausa=false;
}

void Prueba::asignarTiempo(int tipo, int tiempo)
{


  estructuras[tipo]->tiempo = tiempo;

}
//asignarTamanoCola
//Entrasas: tipo, tamanoCola
//Salidas: ninguna
//Restricciones: ninguna

void Prueba::asignarTamanoCola(int tipo, int tamanoCola)
{

 colas[tipo]->max = tamanoCola;
}

void Prueba::actualizarPrioridad(int identificador, int prioridad)
{

    Nodo *temporal = listaDatos->retornarPrimerNodo();
    Nodo *temporalDoble = listaDob->primerNodo;
    while(identificador != temporal->identificador)
    {


        temporalDoble = temporalDoble->siguiente;
        temporal = temporal->siguiente; //No toma el temporal->identificador = 0
    }
    temporalDoble->prioridad = prioridad;

}

//actualizarRechazo
//Entradas: identificador y rechazo
//Salidas: ninguna
//Restricciones: ninguna

void Prueba::actualizarRechazo(int identificador, int rechazo)
{

    Nodo *temporal = listaDatos->primerNodo;
    while(identificador != temporal->identificador)
    {
        temporal = temporal->siguiente;
    }

    temporal->rechazo = rechazo;

}

//retornarHilo
//Entradas: ninguna
//Salidas: un hilo tipo hiloInterfaz
//Restricciones: ninguna

hiloInterfaz *Prueba::retornarHilo()
{
    return hiloTemposs;
}

//asignarCaja
//Entradas: número de cajas
//Salidas: ninguna
//Restricciones: ninguna

void Prueba::asignarCaja(int cajas)
{
    numeroCajas =  cajas;
}

//asignarTamanoCircular
//Entradas: tamaño
//Salidas: ninguna
//Restricciones: ninguna

void Prueba::asignarTamanoCircular(int tamano)
{
    listaCir->numeroDeElementos = tamano;
    listaDatos->numeroDeElementos = tamano;
}

//otenerElementosCola
//Entradas: número de cola
//Salidas: el número de elementos de la cola
//Restricciones: ninguna

int Prueba::obtenerElementosCola(int cola)
{
    return colas[cola]->numElemento;
}

//devolverRechazo
//Entradas: identificador
//Salidas: número del rechazo
//Restriccioes: ninguna

int Prueba:: devolverRechazo(int identificador)
{

    Nodo *temporal = listaDatos->retornarPrimerNodo();
    while(identificador != temporal->identificador)
    {
        temporal = temporal->siguiente;
    }
    return temporal->rechazo;
}


//stop
//Entradas: tipo que indicará a cuál se le pondrá stop
//Salidas: ninguna
//Restricciones: nignuna

void Prueba::stop(int tipo)
{
    estructuras[tipo]->activo = false;
}


//reiniciarPrograma
//Entradas:ninguna
//Salidas: ninguna
//Restricciones: ninguna
//Reinicia los datos que pertenecen al programa

void Prueba::reiniciarPrograma()
{
    for(int n = 0; n<NUM_Colas; n++)
    {
        colas[n]->frente = colas[n]->final = NULL;
    }

    for(int i = 0; i<NUM_THREADS; i++)
    {
        estructuras[i]->activo = false;
    }
    listaCir->primerNodo = listaCir->ultimoNodo = NULL;
    listaDob->primerNodo = NULL;
    listaDatos->primerNodo = listaDatos->ultimoNodo = NULL;
    numeroCajas = 1;
    cuentaCajas = 0;

}







