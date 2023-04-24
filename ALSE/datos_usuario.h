#ifndef DATOS_USUARIO_H
#define DATOS_USUARIO_H
#include "QtSql/QSqlDatabase"
#include "QtSql/qsqlquery.h"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQuery"

#include <QWidget>

namespace Ui {
class DATOS_USUARIO;
}

class DATOS_USUARIO : public QWidget
{
    Q_OBJECT

public:
    explicit DATOS_USUARIO(QWidget *parent = nullptr);
    ~DATOS_USUARIO();
    void CrearTabla_2();

private slots:

    void on_REGISTRO_2_clicked();

private:
    Ui::DATOS_USUARIO *ui;
};

#endif // DATOS_USUARIO_H
