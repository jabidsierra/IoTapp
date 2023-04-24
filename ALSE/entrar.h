#ifndef ENTRAR_H
#define ENTRAR_H
#include "QtSql/QSqlDatabase"
#include "QtSql/qsqlquery.h"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQuery"

#include <QWidget>

namespace Ui {
class ENTRAR;
}

class ENTRAR : public QWidget
{
    Q_OBJECT

public:
    explicit ENTRAR(QWidget *parent = nullptr);
    ~ENTRAR();

private slots:
    void on_ENTRAR_2_clicked();

    void on_REGISTRO_3_clicked();

private:
    Ui::ENTRAR *ui;
};

#endif // ENTRAR_H
