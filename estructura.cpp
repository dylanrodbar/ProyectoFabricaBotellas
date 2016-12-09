#include "estructuras.h"
#include <QString>
#include <QDebug>

Estructuras::Estructuras()
{

}



void Cola::encolar (QString dato, int rechazo, int identificador)   //Se cae en esta parte, modifica el estado del nodo
{
if (vacia())
{
        frente =  final = new Nodo(dato, rechazo, identificador);

}

        else
      {
            Nodo *nuevo  = new Nodo(dato, rechazo, identificador);
            final->siguiente = nuevo;
            nuevo->anterior = final;
            final = nuevo;
            numElemento+=1;

        }
}




Nodo* Cola::desencolar(void)
{

      if (vacia())
      {
         return NULL;
      }
      else
      {

          Nodo *borrado = frente;
          frente = frente->siguiente;
          borrado->siguiente = NULL;
          numElemento-=1;
          return borrado;
      }
}

bool Cola::vacia (void)
{
     if (frente == NULL)
        return true;
     else
         return false;
}


void Cola::imprimir(void)
{

     Nodo *tmp = frente;

     while (tmp != NULL)
     {

           tmp = tmp->siguiente;
     }

}


Nodo* Cola::verFrente()
{
      return frente;
}


//-----------------------------------------------------------------------------------------------------------------//


//---------------------Lista Doblemente Enlazada Circular-------------------//

void ListaDobleCircular::insertarAlInicio (QString dato, int rechazo, int identificador)
{
    Nodo *nuevo = new Nodo(dato, rechazo, identificador);
     if (primerNodo == NULL)
     {

         primerNodo = ultimoNodo = nuevo;
         nuevo->siguiente = nuevo;
         nuevo->anterior =  nuevo;
     }
     else
     {
         nuevo->siguiente = primerNodo;
         nuevo->anterior = ultimoNodo;
         primerNodo->anterior = nuevo;
         ultimoNodo->siguiente = nuevo;
         primerNodo = nuevo;

     }
}



Nodo* ListaDobleCircular::borrarAlInicio(void)
{
      if (primerNodo == NULL)
      {
         return NULL;
      }
      else
      {
          Nodo* borrado = primerNodo;
          primerNodo = primerNodo->siguiente;
          primerNodo->anterior = ultimoNodo;
          ultimoNodo->siguiente = primerNodo;
          borrado->siguiente = NULL;
          borrado->anterior = NULL;
          return borrado;
      }
}










bool ListaDobleCircular::vacia()
{
     if (primerNodo == NULL)
        return true;
     else
         return false;
}




Nodo* ListaDobleCircular::borrarEnIdentificador(int identificador)
{
      if (vacia())
         return NULL;
      else if (primerNodo->siguiente == NULL)
      {
            Nodo* actual = primerNodo;
            primerNodo = ultimoNodo = NULL;
            return actual;
      }
      else
      {
            Nodo* actual = primerNodo;

            while (actual->identificador != identificador)   //Busca al atributo identificar
              actual = actual->siguiente;


            actual->anterior->siguiente = actual->siguiente;  //Cuando lo encuentra, se encarga de eliminar al nodo
            actual->siguiente->anterior = actual->anterior;   //Revisar
            actual->siguiente = NULL;
            actual->anterior = NULL;
            elementoEnCero+=1;
            return actual;
        }
}

Nodo *ListaDobleCircular::retornarPrimerNodo()
{
    return primerNodo;
}








//-----------------------------------------------------------------------------------------------------------------//


//---------------------Lista Doblemente Enlazada-------------------//

void ListaDobleEnlazada::insertarAlInicio (int probabilidad)
{
     if (primerNodo == NULL)
     {

         primerNodo = ultimoNodo = new Nodo(probabilidad);

     }
     else
     {
         Nodo *nuevo = new Nodo(probabilidad);
         primerNodo->anterior = nuevo;
         nuevo->siguiente = primerNodo;
         primerNodo = nuevo;
     }
}





Nodo* ListaDobleEnlazada::borrarAlInicio(void)
{
      if (primerNodo == NULL)
      {
         return NULL;
      }
      else
      {
          Nodo* borrado = primerNodo;
          primerNodo = primerNodo->siguiente;
          primerNodo->anterior = NULL;
          borrado->siguiente = NULL;
          borrado->anterior = NULL;  //Creo que se está repitiendo el NULL
          return borrado;
      }
}





void ListaDobleEnlazada::insertarAlFinal (int probabilidad)
{

     if (primerNodo == NULL)
     {

         primerNodo = new Nodo(probabilidad);
         ultimoNodo = primerNodo;
     }
     else
     {
         Nodo *nuevo = new Nodo(probabilidad);
         nuevo->anterior = ultimoNodo;   //No al 100% seguro
         ultimoNodo->siguiente = nuevo;
         ultimoNodo = nuevo;

     }
}




bool ListaDobleEnlazada::vacia()
{
     if (primerNodo == NULL)
        return true;
     else
         return false;
}




Nodo* ListaDobleEnlazada::borrarEnPrioridad(int prioridad)
{
      if (vacia())
         return NULL;
      else if (primerNodo->siguiente == NULL)
      {
            Nodo* actual = primerNodo;
            primerNodo = ultimoNodo = NULL;
            return actual;
      }
      else
      {
            Nodo* actual = primerNodo;
            while (actual->prioridad!=prioridad)
            {
               actual = actual->siguiente;
            }

            actual->siguiente->anterior = actual->anterior;
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente = NULL;
            actual->anterior = NULL;
            return actual;

        }
}

bool ListaDobleEnlazada::esCantidadDeCien()
{
    int prioridadTotal = 0;
    Nodo *temporal = primerNodo;
    while(temporal != NULL)
    {


        prioridadTotal+=temporal->prioridad;
        qDebug()<<temporal->prioridad<<" "<<prioridadTotal;
        temporal=temporal->siguiente;
    }





    if (prioridadTotal==100)
    {
        return true;
    }
    else
    {
        return false;
    }
}
