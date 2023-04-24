#include "inicio.h"
#include "./ui_inicio.h"
#include "registro.h"
#include "entrar.h"
#include "QDebug"


INICIO::INICIO(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::INICIO)
{
    ui->setupUi(this);
    QString nombre;
    nombre="base_datos.sql";
    dbmain=QSqlDatabase::addDatabase("QSQLITE");
    dbmain.setDatabaseName(nombre);
    if(dbmain.open())
    {
        qDebug()<<"Exito en conexión con base de datos";
    }
    else
    {
        qDebug()<<"Error";
    }
}

INICIO::~INICIO()
{
    delete ui;
}

//* aqui llamamos a la interfaz de registro cuando se da click*//
void INICIO::on_REGISTRO_clicked()
{
    REGISTRO *registro = new REGISTRO(0);
    registro->show();
    this->close();
}

//* aqui llamamos a la interfaz de entrar cuando se da click*//
void INICIO::on_ENTRAR_clicked()
{
    ENTRAR *entrar = new ENTRAR(0);
    entrar->show();
    this->close();
}
