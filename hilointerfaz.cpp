#include "hilointerfaz.h"

hiloInterfaz::hiloInterfaz()
{

}

//Actualiza las máquinas por medio de una señal a la interfaz
void hiloInterfaz::maquinas(int identificador, int tabla)
{
    emit actualizarTablas(identificador, tabla);
}

//Actualiza las colas por medio de una señal a la interfaz

void hiloInterfaz::colas(int numElementos, int numCola)
{
    emit actualizarColas(numElementos, numCola);
}

//Actualiza las botellas aprobadas y rechazadas por medio de una señal a la interfaz

void hiloInterfaz::aprobados(int identificador, bool aceptado)
{
    emit actualizarAceptados(identificador, aceptado);
}

//Actualiza al camión por medio de una señal a la interfaz

void hiloInterfaz::camion(int columna)
{
    emit actualizarCamion(columna);
}


