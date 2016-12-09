#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
//#include "botellas.h"

 Prueba *principal = new Prueba();
 int elegido;
 int cuentaAgregadas = 0;
 hiloInterfaz *hiloss = principal->retornarHilo();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Se inicializan las tablas con sus respectivos datos
    setWindowTitle("Refrescos");
    QStringList titulosGeneral, titulosEspecificos, rechazos, camion, priori;
    titulosGeneral << "Nombre" << "C.Actual" << "Prioridad" << "P.Rechazo";
    titulosEspecificos << "Nombre" << "Pasando";
    rechazos << "Nombre" << "Aprobadas" << "Deshecho";
    camion << "Cajas" << "Camiones";
    ui->Tabla->setColumnCount(4);
    ui->tablaCBotellas->setColumnCount(4);
    ui->tablaLBotellas->setColumnCount(2);
    ui->tablaLLBotellas1->setColumnCount(2);
    ui->tablaLLBotellas2->setColumnCount(2);
    ui->tablaTBotellas->setColumnCount(2);
    ui->tablaInspCalidad->setColumnCount(2);
    ui->tablaRechazo->setColumnCount(3);
    ui->tablaCamion->setColumnCount(2);
    ui->Tabla->setHorizontalHeaderLabels(titulosGeneral);
    ui->Tabla->setColumnWidth(1,60);
    ui->Tabla->setColumnWidth(2,60);
    ui->Tabla->setColumnWidth(3,60);
    ui->Tabla->setColumnWidth(4,60);
    ui->tablaLBotellas->setHorizontalHeaderLabels(titulosEspecificos);
    ui->tablaCBotellas->setHorizontalHeaderLabels(titulosEspecificos);
    ui->tablaLLBotellas1->setHorizontalHeaderLabels(titulosEspecificos);
    ui->tablaLLBotellas2->setHorizontalHeaderLabels(titulosEspecificos);
    ui->tablaTBotellas->setHorizontalHeaderLabels(titulosEspecificos);
    ui->tablaInspCalidad->setHorizontalHeaderLabels(titulosEspecificos);
    ui->tablaRechazo->setHorizontalHeaderLabels(rechazos);
    ui->tablaCamion->setHorizontalHeaderLabels(camion);
    connect(hiloss, SIGNAL(actualizarTablas(int, int)), this, SLOT(actualizarTabla(int,int)));
    connect(hiloss, SIGNAL(actualizarColas(int, int)), this, SLOT(actualizarCola(int,int)));
    connect(hiloss, SIGNAL(actualizarAceptados(int,bool)), this, SLOT(actualizarRechazo(int,bool)));
    connect(hiloss, SIGNAL(actualizarCamion(int)), this, SLOT(actualizarElCamion(int)));




}

MainWindow::~MainWindow()
{
    delete ui;
}

//Asigna un tamaño máximo a la cola correspondiente

void MainWindow::on_pushButton_2_clicked()
{

    if(ui->textoMax1->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }

    else if(principal->obtenerElementosCola(0)>ui->textoMax1->text().toInt())
    {
        QMessageBox::warning(NULL, "Advertencia", "El máximo digitado es menor el que número de botellas en proceso");
    }

    else
    {
        principal->asignarTamanoCola(0, ui->textoMax1->text().toInt());
        QMessageBox::information(NULL, "Información", "El máximo se ha asignado correctamente");
    }

}

//validarCien
//Entradas: ninguna
//Salidas: un entero que identifique si se cometió algún error en específico o ningún error
//Restricciones: deben ser números mayores que cero y en el caso de las prioridades deben sumar 100

int MainWindow::validarCien()
{
   int cantidad = 0;
   for(int n = 0; n<ui->Tabla->rowCount(); n++)
   {
       QTableWidgetItem *priori = ui->Tabla->item(n,2);
       QTableWidgetItem *recha  = ui->Tabla->item(n,3);
       if(priori->text().toInt()<=0 || recha->text().toInt()<0 || recha->text().toInt()>100)
       {
           return 1;
       }
       else
       cantidad+=priori->text().toInt();
   }
   if(cantidad == 100)
   {
       return 3;
   }
   else
   {
       return 2;
   }
}

//Pausa a la estructura correspondiente

void MainWindow::on_botonPausar_clicked()
{
    principal->pausar(0);
    principal->pausar(1);
    principal->pausar(2);
    principal->pausar(3);
    principal->pausar(4);
    principal->pausar(5);
}

//Reinicia a la estructura correspondiente

void MainWindow::on_botonReiniciar_clicked()
{
    principal->reiniciar(0);
    principal->reiniciar(1);
    principal->reiniciar(2);
    principal->reiniciar(3);
    principal->reiniciar(4);
    principal->reiniciar(5);
}

//Asigna un tamaño a una cola

void MainWindow::on_pushButton_10_clicked()
{
    if(ui->textoMax2->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }

    else if(principal->obtenerElementosCola(1)>ui->textoMax2->text().toInt())
    {
        QMessageBox::warning(NULL, "Advertencia", "El máximo digitado es menor el que número de botellas en proceso");
    }

    else
    {
    principal->asignarTamanoCola(1, ui->textoMax2->text().toInt());
    QMessageBox::information(NULL, "Información", "El máximo se ha asignado correctamente");
    }
}

//Asigna los datos a las tablas de acuerdo al formulario de datos

void MainWindow::on_botonAgregar_clicked()
{


    int res, prioridad, rechazo, fila;
    QString nombre;
    Botellas pd(this);
    pd.setWindowTitle("Formulario de botellas");
    res = pd.exec();   //Se encarga de abrir el formulario para las botellas
  if(res ==QDialog::Accepted)
  {
  fila = ui->Tabla->rowCount();
  nombre = pd.nombre();
  prioridad = pd.prioridad();
  rechazo = pd.rechazo();
  ui->Tabla->insertRow(ui->Tabla->rowCount());
  ui->tablaLBotellas->insertRow(ui->tablaLBotellas->rowCount());
  ui->tablaCBotellas->insertRow(ui->tablaCBotellas->rowCount());
  ui->tablaLLBotellas1->insertRow(ui->tablaLLBotellas1->rowCount());
  ui->tablaLLBotellas2->insertRow(ui->tablaLLBotellas2->rowCount());
  ui->tablaTBotellas->insertRow(ui->tablaTBotellas->rowCount());
  ui->tablaInspCalidad->insertRow(ui->tablaInspCalidad->rowCount());
  ui->tablaRechazo->insertRow(ui->tablaRechazo->rowCount());

  ui->Tabla->setItem(fila, NOMBRE, new QTableWidgetItem(nombre));
  ui->Tabla->setItem(fila, CANTIDAD, new QTableWidgetItem("0"));
  ui->Tabla->setItem(fila, PRIORIDAD, new QTableWidgetItem(QString::number(prioridad)));
  ui->Tabla->setItem(fila, RECHAZO, new QTableWidgetItem(QString::number(rechazo)));
  ui->tablaLBotellas->setItem(fila, NOMBRE, new QTableWidgetItem(nombre));
  ui->tablaLBotellas->setItem(fila, 1, new QTableWidgetItem("0"));
  ui->tablaLLBotellas1->setItem(fila, NOMBRE, new QTableWidgetItem(nombre)); //No se actualizan los datos de estas tablas
  ui->tablaLLBotellas1->setItem(fila, 1, new QTableWidgetItem("0"));
  ui->tablaLLBotellas2->setItem(fila, NOMBRE, new QTableWidgetItem(nombre));
  ui->tablaLLBotellas2->setItem(fila, 1, new QTableWidgetItem("0"));
  ui->tablaTBotellas->setItem(fila, NOMBRE, new QTableWidgetItem(nombre));
  ui->tablaTBotellas->setItem(fila, 1, new QTableWidgetItem("0"));
  ui->tablaInspCalidad->setItem(fila, NOMBRE, new QTableWidgetItem(nombre));
  ui->tablaInspCalidad->setItem(fila, 1, new QTableWidgetItem("0"));
  ui->tablaCBotellas->setItem(fila,NOMBRE, new QTableWidgetItem(nombre));
  ui->tablaCBotellas->setItem(fila,1, new QTableWidgetItem("0"));
  ui->tablaRechazo->setItem(fila, NOMBRE, new QTableWidgetItem(nombre));
  ui->tablaRechazo->setItem(fila, 1, new QTableWidgetItem("0"));
  ui->tablaRechazo->setItem(fila, 2, new QTableWidgetItem("0"));
  ui->iniciaBotella->setEnabled(true);
  }

}


//Asigna el tiempo a la estructura correspondiente

void MainWindow::on_botonTi1_clicked()
{
   if(ui->TexTi->text().toInt()==0 || ui->TexTi->text().toInt()<0)
   {
      QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
   }
   else
   {
      principal->asignarTiempo(0,ui->TexTi->text().toInt());
      QMessageBox::information(NULL, "Información", "El tiempo se ha asignado correctamente");
   }
}


void MainWindow::on_botonTi2_clicked()
{
if(ui->TexTi2->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }
    else
    {
        principal->asignarTiempo(1,ui->TexTi2->text().toInt());
        QMessageBox::information(NULL, "Información", "El tiempo se ha asignado correctamente");
    }
}

void MainWindow::on_botonTi3_clicked()
{
    if(ui->TexTi3->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }
    else
    {
        principal->asignarTiempo(2,ui->TexTi3->text().toInt());
        QMessageBox::information(NULL, "Información", "El tiempo se ha asignado correctamente");
    }
}

void MainWindow::on_botonTi4_clicked()
{
    if(ui->TexTi4->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }
    else
    {
        principal->asignarTiempo(3,ui->TexTi4->text().toInt());
        QMessageBox::information(NULL, "Información", "El tiempo se ha asignado correctamente");
    }
}

void MainWindow::on_botonTi5_clicked()
{
    if(ui->TexTi5->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }
    else
    {
        principal->asignarTiempo(4,ui->TexTi5->text().toInt());
        QMessageBox::information(NULL, "Información", "El tiempo se ha asignado correctamente");
    }
}

void MainWindow::on_botonTi6_clicked()
{
    if(ui->TexTi6->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }
    else
    {
        principal->asignarTiempo(5,ui->TexTi6->text().toInt());
        QMessageBox::information(NULL, "Información", "El tiempo se ha asignado correctamente");
    }
}

//Inicializa los datos básicos del programa, habilidando los botones necesarios para su ejecución
//de la misma forma, asignará valores a tiempo y tamaño de cola, que será posible editarse por el usuario

void MainWindow::on_iniciaBotella_clicked()
{

    if(validarCien()==3)
    {
    ui->pushButton_11->setEnabled(false);
    principal->iniciarColas();
    principal->iniciarEstructuras();
    for(int n = 0; n<ui->Tabla->rowCount(); n++)
    {
      QTableWidgetItem *nombre = ui->Tabla->item(n,0);
      QTableWidgetItem *prioridad = ui->Tabla->item(n,2);
      QTableWidgetItem *rechazo = ui->Tabla->item(n,3);
      principal->iniciarDatos(nombre->text(), prioridad->text().toInt(), rechazo->text().toInt(), n);
    }

    ui->botonAgregar->setEnabled(false);
    ui->botonEmpezar->setEnabled(true);
    ui->botonPausar->setEnabled(true);
    ui->botonReiniciar->setEnabled(true);
    ui->botonParar->setEnabled(true);
    ui->pausaCBotella->setEnabled(true);
    ui->playCBotella->setEnabled(true);
    ui->toolButton->setEnabled(true);
    ui->toolButton_2->setEnabled(true);
    ui->toolButton_3->setEnabled(true);
    ui->toolButton_4->setEnabled(true);
    ui->toolButton_5->setEnabled(true);
    ui->toolButton_6->setEnabled(true);
    ui->toolButton_7->setEnabled(true);
    ui->toolButton_8->setEnabled(true);
    ui->toolButton_9->setEnabled(true);
    ui->toolButton_10->setEnabled(true);
    ui->TexTi->setText("1");
    ui->TexTi2->setText("1");
    ui->TexTi3->setText("1");
    ui->TexTi4->setText("1");
    ui->TexTi5->setText("1");
    ui->TexTi6->setText("1");
    ui->textoMax1->setText("15");
    ui->textoMax2->setText("15");
    ui->textoMax3->setText("15");
    ui->textoMax4->setText("15");
    ui->textoMax5->setText("15");
    ui->textoMax6->setText("15");
    ui->texNumeroCajas->setText("1");
    ui->tablaCamion->insertRow(ui->tablaCamion->rowCount());
    ui->tablaCamion->setItem(0, 0, new QTableWidgetItem("0"));
    ui->tablaCamion->setItem(0, 1, new QTableWidgetItem("0"));
    QMessageBox::information(NULL, "Información", "Botellas cargadas");
    }
    else if(validarCien() == 2)
    QMessageBox::warning(NULL, "Advertencia", "Las prioridades no suman 100");
    else if(validarCien() == 1)
    QMessageBox::warning(NULL, "Advertencia", "No puede asignar números negativos, rechazos mayores que 100 o una prioridad de 0");




}

//actualizarTabla
//Entradas: identificador y número de tabla
//Salidas: ninguna
//Restricciones: ninguna

void MainWindow::actualizarTabla(int identificador, int tabla)
{


    if(tabla == 1)
    {
     int suma = 1;
     QTableWidgetItem *nombre = ui->tablaLBotellas->item(identificador, 1);

     int n = nombre->text().toInt();
     suma = suma+n;
     nombre->text() = QString::number(suma);
     ui->tablaLBotellas->setItem(identificador, 1, new QTableWidgetItem(QString::number(suma)));




     }



    else if(tabla == 2)
    {
        int suma = 1;
        QTableWidgetItem *valorLLBotellas = ui->tablaLLBotellas1->item(identificador, 1);

        int n = valorLLBotellas->text().toInt();
        suma = suma+n;
        ui->tablaLLBotellas1->setItem(identificador, 1, new QTableWidgetItem(QString::number(suma)));




    }
    else if(tabla ==3)
    {
        int suma = 1;
        QTableWidgetItem *nombre = ui->tablaLLBotellas2->item(identificador, 1);

        int n = nombre->text().toInt();
        suma = suma+n;
        nombre->text() = QString::number(suma);
        ui->tablaLLBotellas2->setItem(identificador, 1, new QTableWidgetItem(QString::number(suma)));

    }
    else if(tabla ==4)
    {
        int suma = 1;
        QTableWidgetItem *nombre = ui->tablaTBotellas->item(identificador, 1);

        int n = nombre->text().toInt();
        suma = suma+n;
        nombre->text() = QString::number(suma);
        ui->tablaTBotellas->setItem(identificador, 1, new QTableWidgetItem(QString::number(suma)));

    }
    else if(tabla ==5)
    {
        int suma = 1;
        QTableWidgetItem *nombre = ui->tablaInspCalidad->item(identificador, 1);

        int n = nombre->text().toInt();
        suma = suma+n;
        nombre->text() = QString::number(suma);
        ui->tablaInspCalidad->setItem(identificador, 1, new QTableWidgetItem(QString::number(suma)));

    }
    else if(tabla == 6)
    {
        int suma = 1;
        QTableWidgetItem *nombre = ui->Tabla->item(identificador, 1);

        int n = nombre->text().toInt();
        suma = suma+n;
        nombre->text() = QString::number(suma);
        ui->Tabla->setItem(identificador, 1, new QTableWidgetItem(QString::number(suma)));

        suma = 1;
        nombre = ui->tablaCBotellas->item(identificador,1);
        n = nombre->text().toInt();
        suma = suma+n;
        ui->tablaCBotellas->setItem(identificador, 1, new QTableWidgetItem(QString::number(suma)));
    }

}

//actualizarCola
//Entradas: número de lementos en la cola y el número de la cola
//Salidas: ninguna
//Restricciones: ninguna

void MainWindow::actualizarCola(int numElementos, int numCola)
{
    if(numCola == 1)
    {
        ui->textoAc1->setText(QString::number(numElementos));

    }
    else if(numCola == 2)
    {
       ui->textoAc2->setText(QString::number(numElementos));
    }
    else if(numCola == 3)
    {
      ui->textoAc3->setText(QString::number(numElementos));
    }
    else if(numCola == 4)
    {
      ui->textoAc4->setText(QString::number(numElementos));

    }
    else if(numCola == 5)
    {
      ui->textoAc5->setText(QString::number(numElementos));

    }
    else if(numCola == 6)
    {
      ui->textoAc6->setText(QString::number(numElementos));

    }

}

//actualizarRechazo
//Entradas: identificador y un booleano que indique si se rechazó o no
//Salidas: ninguna
//Restricciones: ninguna

void MainWindow::actualizarRechazo(int identificador, bool rechazo)
{
    if(rechazo == true)
    {
        int suma = 1;
        QTableWidgetItem *nombre = ui->tablaRechazo->item(identificador, 2);

        int n = nombre->text().toInt();
        suma = suma+n;
        nombre->text() = QString::number(suma);
        ui->tablaRechazo->setItem(identificador, 2, new QTableWidgetItem(QString::number(suma)));

    }
    else
    {
        int suma = 1;
        QTableWidgetItem *nombre = ui->tablaRechazo->item(identificador, 1);

        int n = nombre->text().toInt();
        suma = suma+n;
        nombre->text() = QString::number(suma);
        ui->tablaRechazo->setItem(identificador, 1, new QTableWidgetItem(QString::number(suma)));

    }

}

//actualizarElCamion
//Entradas: columna de la tabla
//Salidas: ninguna
//Restricciones: ninguna

void MainWindow::actualizarElCamion(int columna)
{
    int suma = 1;
    QTableWidgetItem *nombre = ui->tablaCamion->item(0, columna);

    int n = nombre->text().toInt();
    suma = suma+n;
    nombre->text() = QString::number(suma);
    ui->tablaCamion->setItem(0, columna, new QTableWidgetItem(QString::number(suma)));
}

//Inicia el programa

void MainWindow::on_botonEmpezar_clicked()
{

    ui->botonEmpezar->setEnabled(false);
    ui->bActDatos->setEnabled(true);
    principal->iniciarFabrica();
}







//Actualiza la prioridad y los procentajes de rechazo

void MainWindow::on_bActDatos_clicked()
{

    if(validarCien()==3)
    {
    for(int n = 0; n<ui->Tabla->rowCount(); n++)
    {
     QTableWidgetItem *prioridad = ui->Tabla->item(n, 2);
     QTableWidgetItem *rechazo = ui->Tabla->item(n, 3);


     principal->actualizarPrioridad(n, prioridad->text().toInt());
     principal->actualizarRechazo(n, rechazo->text().toInt());

}
    QMessageBox::information(NULL, "Información", "Los cambios se han efectuado exitosamente");
    }
    else if(validarCien() == 2)
      QMessageBox::warning(NULL, "Advertencia", "Las prioridades no suman 100");
    else if(validarCien()==1)
      QMessageBox::warning(NULL, "Advertencia", "No puede asignar números negativos, un rechazo mayor que 100 o una prioridad de 0");
}

//Asigna un tamaño a la cola correspondiente

void MainWindow::on_pushButton_5_clicked()
{
    if(ui->textoMax3->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }

    else if(principal->obtenerElementosCola(2)>ui->textoMax3->text().toInt())
    {
        QMessageBox::warning(NULL, "Advertencia", "El máximo digitado es menor el que número de botellas en proceso");
    }
    else
    {
    principal->asignarTamanoCola(2, ui->textoMax3->text().toInt());
    QMessageBox::information(NULL, "Información", "El máximo se ha asignado correctamente");
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    if(ui->textoMax4->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }

    else if(principal->obtenerElementosCola(3)>ui->textoMax4->text().toInt())
    {
        QMessageBox::warning(NULL, "Advertencia", "El máximo digitado es menor el que número de botellas en proceso");
    }
    else
    {
    principal->asignarTamanoCola(3, ui->textoMax4->text().toInt());
    QMessageBox::information(NULL, "Información", "El máximo se ha asignado correctamente");
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if(ui->textoMax5->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }

    else if(principal->obtenerElementosCola(4)>ui->textoMax5->text().toInt())
    {
        QMessageBox::warning(NULL, "Advertencia", "El máximo digitado es menor el que número de botellas en proceso");
    }
    else
    {
    principal->asignarTamanoCola(4, ui->textoMax5->text().toInt());
    QMessageBox::information(NULL, "Información", "El máximo se ha asignado correctamente");
    }
}

//Pausa a la máquina correspondiente

void MainWindow::on_pausaCBotella_clicked()
{
    principal->pausar(0);
}

//Reinicia a la máquina correspondiente

void MainWindow::on_playCBotella_clicked()
{
    principal->reiniciar(0);
}


//Asigna el número de cajas por proceso del camión
void MainWindow::on_pushButton_9_clicked()
{
    if(ui->texNumeroCajas->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }
    else
    {
    principal->asignarCaja(ui->texNumeroCajas->text().toInt());
    QMessageBox::information(NULL, "Información", "El número de cajas se ha actualizado correctamente");
    }
}

//Pausan y reinician a la máquina correspondiente

void MainWindow::on_toolButton_3_clicked()
{
    principal->reiniciar(1);
}

void MainWindow::on_toolButton_4_clicked()
{
    principal->pausar(1);
}

void MainWindow::on_toolButton_7_clicked()
{
    principal->reiniciar(2);
}

void MainWindow::on_toolButton_8_clicked()
{
    principal->pausar(2);
}

void MainWindow::on_toolButton_5_clicked()
{
    principal->reiniciar(3);
}

void MainWindow::on_toolButton_6_clicked()
{
    principal->pausar(3);
}

void MainWindow::on_toolButton_10_clicked()
{
    principal->reiniciar(4);
}

void MainWindow::on_toolButton_9_clicked()
{
    principal->pausar(4);
}

void MainWindow::on_toolButton_clicked()
{
    principal->reiniciar(5);
}

void MainWindow::on_toolButton_2_clicked()
{
    principal->pausar(5);
}

void MainWindow::on_pushButton_8_clicked()
{
    if(ui->textoMax6->text().toInt()==0)
    {
        QMessageBox::warning(NULL, "Advertencia", "No puede dejar espacios en blanco, asignar un cero o una letra");
    }

    else if(principal->obtenerElementosCola(5)>ui->textoMax6->text().toInt())
    {
        QMessageBox::warning(NULL, "Advertencia", "El máximo digitado es menor el que número de botellas en proceso");
    }
    else
    {
        principal->asignarTamanoCola(5, ui->textoMax6->text().toInt());
        QMessageBox::information(NULL, "Información", "El máximo se ha asignado correctamente");
    }
}

void MainWindow::on_Tabla_itemClicked(QTableWidgetItem *item)
{
    elegido = item->row();
}

//Remueve la fila que el usuario desee

void MainWindow::on_pushButton_11_clicked()
{
    if(cuentaAgregadas == 0)
        ui->iniciaBotella->setEnabled(false);
    ui->Tabla->removeRow(elegido);
    ui->tablaCBotellas->removeRow(elegido);
    ui->tablaLBotellas->removeRow(elegido);
    ui->tablaLLBotellas1->removeRow(elegido);
    ui->tablaLLBotellas2->removeRow(elegido);
    ui->tablaTBotellas->removeRow(elegido);
    ui->tablaInspCalidad->removeRow(elegido);
}

//Reinicia las estructuras en su totalidad

int MainWindow::on_botonParar_clicked()
{
    principal->stop(0);
    principal->stop(1);
    principal->stop(2);
    principal->stop(3);
    principal->stop(4);
    principal->stop(5);
    QString resumen = "Resumen general de los procesos: \n";
    for(int n = 0; n<ui->Tabla->rowCount(); n++)
    {
        QTableWidgetItem *nombre = ui->Tabla->item(n,0);
        QTableWidgetItem *cantidad = ui->Tabla->item(n,1);
        resumen+="Nombre: "+nombre->text()+"\n Cantidad: \n"+cantidad->text()+"\n"+"-----------------\n";
    }
    QMessageBox *mensaje = new QMessageBox();
    mensaje->information(NULL, "Información", resumen);

}









