#include "datos_usuario.h"
#include "ui_datos_usuario.h"
#include "registro.h"
#include "ui_registro.h"
#include "entrar.h"
#include "ui_entrar.h"
#include "QDebug"
#include "QMessageBox"

DATOS_USUARIO::DATOS_USUARIO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DATOS_USUARIO)
{
    ui->setupUi(this);
    CrearTabla_2();
}

DATOS_USUARIO::~DATOS_USUARIO()
{
    delete ui;
}

void DATOS_USUARIO::CrearTabla_2()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS TBL_DATOS_USUARIOS("
                    "nombre VARCHAR(25),"
                    "apellido VARCHAR(25),"
                    "numero_id VARCHAR(25),"
                    "dia VARCHAR(2),"
                    "mes VARCHAR(2),"
                    "year VARCHAR(4)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec())
    {
        qDebug()<<"Tabla Creada";
    }else
    {
        qDebug()<<"Tabla no creada"<<crear.lastError();
    }
}

void DATOS_USUARIO::on_REGISTRO_2_clicked()
{
    QString nombre=ui->NOMBRE->text();
    QString apellido=ui->APELLIDO->text();
    QString numero_id=ui->NUM_ID->text();
    QString dia=ui->DIA->text();
    QString mes=ui->MES->text();
    QString year=ui->YEAR->text();
    qDebug()<<nombre;
    qDebug()<<apellido;
    qDebug()<<numero_id;
    qDebug()<<dia;
    qDebug()<<mes;
    qDebug()<<year;
    QSqlQuery insert_db;
    if(1<=dia<=31 && 1<=mes<=12 && 1500<=year<=2021)
    {
        insert_db.prepare("INSERT INTO TBL_DATOS_USUARIOS(nombre,apellido,numero_id,dia,mes,year)"
                        "VALUES (:nombre,:apellido,:numero_id,:dia,:mes,:year)");
        insert_db.bindValue(":nombre",nombre);
        insert_db.bindValue(":apellido",apellido);
        insert_db.bindValue(":numero_id",numero_id);
        insert_db.bindValue(":dia",dia);
        insert_db.bindValue(":mes",mes);
        insert_db.bindValue(":year",year);

        if(insert_db.exec())
        {
            qDebug()<<"Datos ingresados con exito";
            QMessageBox::information(this,tr("Exito"),tr("Registro Exitoso"));
            this -> close();
            ENTRAR *entrar = new ENTRAR(0);
            entrar->show();
        }
        else
        {
            qDebug()<<"Error"<<insert_db.lastError();
            QMessageBox::critical (this,tr("ERROR"),tr("Error"));
        }
    }
    else
    {
        qDebug()<<"Error al ingresar los datos"<<insert_db.lastError();
        QMessageBox::critical (this,tr("ERROR"),tr("Verifique, Error en la fecha"));
    }
}

