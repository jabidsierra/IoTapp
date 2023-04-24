#include "entrar.h"
#include "ui_entrar.h"
#include "registro.h"
#include "ui_registro.h"
#include "muestra_datos.h"
#include "ui_muestra_datos.h"
#include "QDebug"
#include "QMessageBox"

ENTRAR::ENTRAR(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ENTRAR)
{
    ui->setupUi(this);
}

ENTRAR::~ENTRAR()
{
    delete ui;
}

void ENTRAR::on_ENTRAR_2_clicked()
{
    QString nombre_usuario=ui->USUARIO_2->text();
    QString contra=ui->CONTRA_2->text();
    QSqlQuery buscar;
    QString contrasena;
    QString consulta;
    QString usuario;
    consulta.append("SELECT * FROM TBL_USUARIOS where nombre_usuario='"+nombre_usuario+"'");
    buscar.prepare(consulta);
    if(buscar.exec())
    {
        qDebug()<<"consulta realizada";
        while(buscar.next())
        {
            contrasena=buscar.value(1).toByteArray().constData();
            usuario=buscar.value(0).toByteArray().constData();
            qDebug()<<contrasena;
            qDebug()<<usuario;
        }
    }
    else
    {
        qDebug()<<"Error de consulta";
        QMessageBox::critical(this,tr("ERROR"),tr("Usuario no existente, cree uno"));

    }
    if(contrasena==contra && usuario==nombre_usuario)
    {
        MUESTRA_DATOS * muestra_datos= new MUESTRA_DATOS(0);
        muestra_datos->show();
        QMessageBox::information(this,tr("Bienvenido"),tr("Bienvenido"));
        this -> close();
    }
    else
    {
        QMessageBox::critical(this,tr("ERROR"),tr("Usuario no econtrado, cree uno"));
        REGISTRO *registro = new REGISTRO(0);
        registro->show();
    }
}

void ENTRAR::on_REGISTRO_3_clicked()
{
    REGISTRO *registro = new REGISTRO(0);
    registro->show();
}
