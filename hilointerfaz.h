#ifndef HILOINTERFAZ_H
#define HILOINTERFAZ_H
#include "qthread.h"
#include <QDebug>


class hiloInterfaz : public QThread
{
    Q_OBJECT
public:
    hiloInterfaz();
    void maquinas(int, int);
    void colas(int, int);
    void aprobados(int, bool);
    void camion(int);

signals:
    actualizarColas(int, int);
    actualizarTablas(int, int);
    actualizarAceptados(int, bool);
    actualizarCamion(int);

public slots:
};

#endif // HILOINTERFAZ_H
