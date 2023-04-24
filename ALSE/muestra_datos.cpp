#include "muestra_datos.h"
#include "ui_muestra_datos.h"
#include "sensor.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iostream>
#include "QDebug"
#include "QMessageBox"


int cont = 0;
MUESTRA_DATOS::MUESTRA_DATOS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MUESTRA_DATOS)
{
    ui->setupUi(this);
    CrearTabla_2();
    _tmr = new QTimer();
    _tmr->setInterval( 50 );
    connect( _tmr, SIGNAL(timeout()), this, SLOT(leerSensores()) );
    _tmr->start();

    // Preguntar fecha y hora al SO
    ActualizarFechaFromSO();

    std::cout << _fecha << std::endl;
    _itera = 0;
    _prom_Tem[0] = _prom_Tem[1] = _prom_Tem[2] = 0.;
    _prom_Viento[0] = _prom_Viento[1] = 0.;
    _prom_Preci = 0.;

//    _db_local = new Db_Local("sensores.db");

    actualizarGUI();
}
MUESTRA_DATOS::~MUESTRA_DATOS()
{
    delete ui;
    delete _tmr;
}

void MUESTRA_DATOS::CrearTabla_2()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS TBL_DATOS_SENSOR("
                    "temperatura VARCHAR(10),"
                    "humedad VARCHAR(10),"
                    "velocidad_viento VARCHAR(10),"
                    "direccion_viento VARCHAR(10),"
                    "precipitacion VARCHAR(10),"
                    "intensidad_luz VARCHAR(10)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec())
    {
        qDebug()<<"Tabla datos del sensor Creada";
    }else
    {
        qDebug()<<"Tabla datos del sensor no creada"<<crear.lastError();
    }
}

void MUESTRA_DATOS::agregar_datos(){
    QSqlQuery insertar_db;
    QString temperatura=ui->TEMPE->text();
    QString humedad=ui->HUME->text();
    QString velocidad_viento=ui->VEL->text();
    QString direccion_viento=ui->DIREC->text();
    QString precipitacion=ui->PRECI->text();
    QString intensidad_luz=ui->LUZ->text();
    qDebug()<<temperatura;
    qDebug()<<humedad;
    qDebug()<<velocidad_viento;
    qDebug()<<direccion_viento;
    qDebug()<<precipitacion;
    qDebug()<<intensidad_luz;
    insertar_db.prepare("INSERT INTO TBL_DATOS_SENSOR(temperatura,humedad,velocidad_viento,direccion_viento,precipitacion,intensidad_luz)"
                    "VALUES (:temperatura,:humedad,:velocidad_viento,:direccion_viento,:precipitacion,:intensidad_luz)");
    insertar_db.bindValue(":temperatura",temperatura);
    insertar_db.bindValue(":humedad",humedad);
    insertar_db.bindValue(":velocidad_viento",velocidad_viento);
    insertar_db.bindValue(":direccion_viento",direccion_viento);
    insertar_db.bindValue(":precipitacion",precipitacion);
    insertar_db.bindValue(":intensidad_luz",intensidad_luz);
    if(insertar_db.exec())
    {
            qDebug()<<"Datos ingresados a la tabla";
    }
    else
    {
        qDebug()<<"Error al ingresar los datos"<<insertar_db.lastError();
    }
}

void MUESTRA_DATOS::actualizarGUI(){

    ui->HORA->setText( QString::number( _hr ) );
    ui->SEG->setText( QString::number( _min ));
    ui->TEMPE->setText( QString::number( _prom_Tem[0] ) + " °C");
    ui->HUME->setText( QString::number( _prom_Tem[1] ) +" %");
    ui->VEL->setText( QString::number( _prom_Viento[1] ) +" km/h");
    ui->DIREC->setText( QString::number( _prom_Viento[0] ) + " °");
    ui->PRECI->setText( QString::number( _prom_Preci ) +" mm/día");
    ui->LUZ->setText(QString::number( _prom_Tem[2] ) +" lummen");
}

int estado;
void MUESTRA_DATOS::on_IZQUIERDA_clicked()
{
    if (cont>0){
    cont = cont-1;
    }
    else{}
    estado=cont;
    estados(cont);
}

void MUESTRA_DATOS::on_DERECHA_clicked()
{
    if (cont<=2)
    {
    cont = cont+1;
    }
    else
    {
    cont = cont-2;
    }
    estado=cont;
    estados(cont);
}

void MUESTRA_DATOS::estados(int& cont)
{
}

void MUESTRA_DATOS::leerSensores(){


    agregar_datos();
    // Leer los sensores

    _tem.actualizar();
    _prom_Tem[0] += _tem.temperatura();
    _prom_Tem[1] += _tem.humedad();
    _prom_Tem[2] += _tem.luz();

    _viento.actualizar();
    _prom_Viento[0] += _viento.velocidad();
    _prom_Viento[1] += _viento.direccion();

    _preci.actualizar();
    _prom_Preci += _preci.leerDato();

    // Contador de cada 5 seg. Un minuto son 12.
    _itera++;
    if( _itera == 60 ){
        _itera = 0;
        _min++;
        if( _min == 60 ){
            _min = 0;
            _hr++;
           if( _hr == 24) {
               _hr = 0;
               ActualizarFechaFromSO();
           }
        }
        // Calcular promedios de minuto


        _prom_Tem[0] /= 12.;
        _prom_Tem[1] /= 12.;

        _prom_Viento[0] /= 12.;
        _prom_Viento[1] /= 12.;

        // Actualizar GUI
        actualizarGUI();
/*        if( _db_local->abrir_DB() ){
            std::stringstream hora;
            hora << _hr << ":" << _min;
            _db_local->guardarDatos(_fecha, hora.str(), _prom_gps, _prom_Tem, _prom_Viento, _prom_Preci );
            _db_local->cerrar_DB();
        }
*/
        // Acumuladores a 0
        _prom_Tem[0] = _prom_Tem[1] = _prom_Tem [2] = 0.;
        _prom_Viento[0] = _prom_Viento[1] = 0.;
        _prom_Preci = 0.;
    }

}

void MUESTRA_DATOS::ActualizarFechaFromSO()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    _hr = ltm->tm_hour;
    _min = ltm->tm_min;

    std::stringstream fecha;
    fecha << ltm->tm_mday << "/" << ltm->tm_mon + 1  << "/" << ltm->tm_year + 1900;
    _fecha = fecha.str();
}

