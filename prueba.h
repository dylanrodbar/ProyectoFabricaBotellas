#ifndef PRUEBA_H
#define PRUEBA_H
#include <pthread.h>
#include <sys/types.h>
#include "estructuras.h"
#include <QString>
#include <QObject>
#include "hilo.h"
#include "hilointerfaz.h"

class Prueba : public QObject

{
    Q_OBJECT
    //class Prueba : public QObject
    //{
        //Q_OBJECT

public:
    Prueba();
    void reiniciarPrograma();
    void stop(int);
    void asignarCaja(int);
    void asignarTiempo(int tipo, int tiempo);
    void asignarTamanoCola(int tipo, int tamano);
    void actualizarPrioridad(int, int);
    void eliminarElementoLista(int);
    int obtenerElementosCola(int);
    static int devolverRechazo(int);
    void actualizarRechazo(int, int);
    void asignarTamanoCircular(int);
    void iniciarDatos(QString nombre, int prioridad, int rechazo, int identificador);
    void iniciarFabrica();
    static void *funcionPrincipal(void * hilo);
    void tomarDatos(QString nombre, int numero);
    void iniciarColas();
    void iniciarEstructuras();
    void pausar(int tipo);
    void reiniciar(int tipo);
    hiloInterfaz *retornarHilo();

signals:


    void actualizarPrimero(QString nombre, int dato);
    void actualizarSegundo(QString nombre, int dato);
    //void actualizarDato(QString dato);

//public slots:

};

#endif // PRUEBA_H
