#ifndef REGISTRO_H
#define REGISTRO_H
#include "QtSql/QSqlDatabase"
#include "QtSql/qsqlquery.h"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQuery"
#include "datos_usuario.h"
#include "ui_datos_usuario.h"

#include <QWidget>

namespace Ui {
class REGISTRO;
}

class REGISTRO : public QWidget
{
    Q_OBJECT

public:
    explicit REGISTRO(QWidget *parent = nullptr);
    ~REGISTRO();
    void CrearTabla_1();

private slots:

    void on_REGISTRAR_clicked();

private:
    Ui::REGISTRO *ui;
};

#endif // REGISTRO_H
