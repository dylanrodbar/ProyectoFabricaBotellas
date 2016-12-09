#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidgetItem>
#include "prueba.h"
#include "hilo.h"
#include "botellas.h"
#include <QMainWindow>
#include "hilointerfaz.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int validarCien();

    ~MainWindow();

private slots:
    void actualizarTabla(int, int);
    void actualizarCola(int, int);
    void actualizarRechazo(int, bool);
    void actualizarElCamion(int);
    //void on_pushButton_clicked();
    //void actualizarPrimerosDatos(QString nombre, int dato);
    //void actualizarSegundosDatos(QString nombre, int dato);
    //void actualizar(int);
    //void actualizarDato(QString nombre, int dato);



    //void on_pushButton_4_clicked();

    void on_botonAgregar_clicked();

    void on_botonTi1_clicked();

    void on_botonTi2_clicked();

    void on_botonTi3_clicked();

    void on_botonTi4_clicked();

    void on_botonTi5_clicked();

    void on_botonTi6_clicked();

    void on_iniciaBotella_clicked();

    void on_botonEmpezar_clicked();



    void on_bActDatos_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pausaCBotella_clicked();

    void on_playCBotella_clicked();

    void on_pushButton_9_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_8_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_10_clicked();

    void on_toolButton_9_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_Tabla_itemClicked(QTableWidgetItem *item);

    void on_pushButton_11_clicked();

    int on_botonParar_clicked();

    void on_botonPausar_clicked();

    void on_botonReiniciar_clicked();



    void on_pushButton_2_clicked();

    void on_pushButton_10_clicked();


private:
    Ui::MainWindow *ui;

    enum
    {
        NOMBRE, CANTIDAD, PRIORIDAD, RECHAZO, PASO
    };

};

#endif // MAINWINDOW_H
