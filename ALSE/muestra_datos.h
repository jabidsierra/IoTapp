#ifndef MUESTRA_DATOS_H
#define MUESTRA_DATOS_H
#include "QtSql/QSqlDatabase"
#include <QMainWindow>
#include <QTimer>
#include "sensor.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/qsqlquery.h"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQuery"
//#include "db_local.h"
#include <string>

#include <QWidget>

namespace Ui {
class MUESTRA_DATOS;
}

class MUESTRA_DATOS : public QWidget
{
    Q_OBJECT

public:
    explicit MUESTRA_DATOS(QWidget *parent = nullptr);
    ~MUESTRA_DATOS();

    void actualizarGUI();
    void CrearTabla_2();
    void agregar_datos();

public slots:
    void leerSensores();
    void on_IZQUIERDA_clicked();
    void on_DERECHA_clicked();

private slots:
    void estados(int&);


private:
    void ActualizarFechaFromSO();
    Ui::MUESTRA_DATOS *ui;
    QTimer*     _tmr;
    Temp_Hum    _tem;
    Viento      _viento;
    Sensor      _preci;
    int         _hr, _min, _itera;
    double      _prom_Tem[2], _prom_Viento[1], _prom_Preci;
    //Db_Local    *_db_local;
    std::string _fecha;
};


#endif // MUESTRA_DATOS_H
