#include "registro.h"
#include "ui_registro.h"
#include "ui_entrar.h"
#include "entrar.h"
#include "datos_usuario.h"
#include "ui_datos_usuario.h"
#include "QDebug"
#include "QMessageBox"


REGISTRO::REGISTRO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::REGISTRO)
{
    ui->setupUi(this);
    CrearTabla_1();
}

REGISTRO::~REGISTRO()
{
    delete ui;
}
void REGISTRO::CrearTabla_1()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS TBL_USUARIOS("
                    "nombre_usuario VARCHAR(25) PRIMARY KEY,"
                    "contra VARCHAR(25),"
                    "confirmar_contra VARCHAR(25)"
                    ");" );

    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec())
    {
        qDebug()<<"Tabla creada con exito";
    }else
    {
        qDebug()<<"Tabla sin exito"<<crear.lastError();
    }
}

void REGISTRO::on_REGISTRAR_clicked()
{
    QString nombre_usuario=ui->NOMBRE_USUARIO->text();
    QString contra=ui->CONTRA->text();
    QString confirmar_contra=ui->CONFI_CONTRA->text();
    qDebug()<<nombre_usuario;
    qDebug()<<contra;
    qDebug()<<confirmar_contra;
    QSqlQuery insert_db;
    if(contra==confirmar_contra)
    {
        insert_db.prepare("INSERT INTO TBL_USUARIOS (nombre_usuario,contra,confirmar_contra)"
                        "VALUES (:nombre_usuario,:contra,:confirmar_contra)");
        insert_db.bindValue(":nombre_usuario",nombre_usuario);
        insert_db.bindValue(":contra",contra);
        insert_db.bindValue(":confirmar_contra",confirmar_contra);

        if(insert_db.exec())
        {
            qDebug()<<"Datos ingresados con exito";
            DATOS_USUARIO * datos_usuario= new DATOS_USUARIO(0);
            datos_usuario->show();
            QMessageBox::information(this,tr("Exito"),tr("Registro Exitoso"));
            this -> close();
        }
        else
        {
            qDebug()<<"Error"<<insert_db.lastError();
            QMessageBox::critical (this,tr("ERROR"),tr("El usuario ya está creado, utiliza otro"));
        }
    }
    else
    {
        qDebug()<<"Error"<<insert_db.lastError();
        QMessageBox::critical (this,tr("ERROR"),tr("COnfirmacion de contraseña incorrecta"));
    }

}
