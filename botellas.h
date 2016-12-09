#ifndef BOTELLAS_H
#define BOTELLAS_H

#include <QDialog>

namespace Ui {
class Botellas;
}

class Botellas : public QDialog
{
    Q_OBJECT

public:
    explicit Botellas(QWidget *parent = 0);
    ~Botellas();
    QString nombre() const;
    int cantidad() const;
    int prioridad() const;
    int rechazo() const;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Botellas *ui;
};

#endif // BOTELLAS_H
