#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <QString>
#include <cstddef>
#define NULL_null


class Estructuras
{
public:
    Estructuras();

//signals:

//public slots:
};

#endif // ESTRUCTURAS_H

//****************************Estructura Nodo*********************************
struct Nodo {
       QString nombre;   //Nombre de la botella, ejem: pitufas, medianas, grandes
       int prioridad;    //Para que mediante un random 1-100 se indique cual dato de debe tomar de la lista circular
       int rechazo;      //Para determinar cuáles botellas se deben aceptar y cuáles rechazar
       Nodo* siguiente;
       Nodo* anterior;
       int identificador;

       Nodo()
       {
           siguiente = anterior = NULL;
       }

       //Utilizado para inicializar los datos en la lista circular
       Nodo(QString nom, int recha, int identi)
       {
                nombre = nom;
                rechazo = recha;
                identificador = identi;
                siguiente = anterior = NULL;
       }

       //Utilizado para inicializar los datos en la lista doble
       Nodo(int proba)
       {
         prioridad = proba;
         siguiente = anterior = NULL;
       }

       bool esCero();

//***************************************************************************************************************************

};

//*************************Estructura Cola************************************

struct Cola {
       Nodo *frente;
       Nodo *final;
       int max;  //Se determina el máximo de la cola
       int numElemento; //Se va sumando cada vez que se encola
       //Cola *sigCola;
       Cola()
       {
            frente = NULL;
            final = NULL;
            //sigCola = NULL;
       }

       Cola(int num, int maxi)
       {
           max = maxi;
           numElemento=num;
           frente = final = NULL;
           //sigCola = NULL;
       }

       void encolar (QString dato, int rechazo, int identificador); //
       Nodo* desencolar (void);
       Nodo* verFrente(void);
       bool vacia(void);
       bool llena(void);
       void imprimir(void);
};

//*******************************************************************************************************************************

//**************************Estructura Lista Doblemente Enlazada Circular***************************


struct ListaDobleCircular {
       Nodo *primerNodo, *ultimoNodo;
       int numeroDeElementos;
       int elementoEnCero;
       ListaDobleCircular()
       {
           numeroDeElementos = 2;
           elementoEnCero = 0;
           primerNodo = ultimoNodo = NULL;
       }
       void insertarAlInicio (QString dato, int rechazo, int identificador);
       void imprimir(void);
       Nodo *borrarAlInicio(void);
       void insertarAlFinal (QString dato, int cantidad, int rechazo); //No se necesita, aparentemente
       bool vacia(void);
       Nodo *borrarEnIdentificador(int identificador);
       Nodo *retornarPrimerNodo(void);
};

//**********************************************************************************************************************

//****************************Estructura Lista Doblemente Enlazada**************************************

struct ListaDobleEnlazada {
       // solo con pN es suficiente
       Nodo *primerNodo, *ultimoNodo;
       Cola *cola;
       Cola *primeraCola;
       Cola *ultimaCola;
       // constructor
       ListaDobleEnlazada()
       {
           primerNodo = ultimoNodo = NULL;
           primeraCola =  NULL;
       }
       void insertarAlInicio (int prioridad);
       //void insertarAlInicioCola(Cola *cola);
       void imprimir(void);
       Nodo *borrarAlInicio(void);
       void insertarAlFinal (int prioridad);
       bool vacia(void);
       Nodo *borrarEnPrioridad(int);
       bool esCantidadDeCien(void);

       //Cola *encontrarCola(int indice);



};

//************************************************************************************************************

//**********************************Estructura Función********************************************************

struct EstructuraFuncion{
    int tiempo;
    //int maxCola;
    Cola *primeraCola;
    Cola *segundaCola;
    Cola *terceraCola;
    int tipo;
    ListaDobleCircular* l;
    int aprobada;   //Para manejar cuántas se aprueban
    int deshecho;   // Para manejar cuántas se desechan
    bool pausa;
    bool activo;

    EstructuraFuncion()
    {

    }
    EstructuraFuncion(int tip, ListaDobleCircular *la, Cola *cola)
    {
        pausa = false;
        activo = true;
        tipo = tip;
        l = la;
        primeraCola = cola;


    }
    EstructuraFuncion(int tip, ListaDobleCircular *la, Cola *colaUno, Cola *colaDos)
    {
        pausa = false;
        activo = true;
        tipo = tip;
        l = la;
        primeraCola = colaUno;
        segundaCola = colaDos;
    }
    EstructuraFuncion(int tip, ListaDobleCircular *la, Cola *colaUno, Cola *colaDos, Cola *colaTres)
    {
        pausa = false;
        activo = true;
        tipo = tip;
        l = la;
        primeraCola = colaUno;
        segundaCola = colaDos;
        terceraCola = colaTres;
    }

    //Agregar constructores para difete
};
