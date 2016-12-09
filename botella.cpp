#include "botellas.h"
#include "ui_botellas.h"
#include <Qdebug>

Botellas::Botellas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Botellas)
{
    ui->setupUi(this);
}

Botellas::~Botellas()
{
    delete ui;
}

//Toma el nombre solicitado
QString Botellas::nombre() const
{
   return ui->Nombre->text();

}

//Toma la prioridad solicitada
int Botellas::prioridad() const
{
    return ui->Prioridad->text().toInt();
}

//Toma el rechazo solicitado
int Botellas::rechazo() const
{
    return ui->Rechazo->text().toInt();
}
void Botellas::on_pushButton_clicked()
{
    accept();
}
