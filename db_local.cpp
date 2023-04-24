#include "db_local.h"
#include <sstream>
#include <iostream>
#include <iostream>


DB_Local::DB_Local(std::string path){
    _url = path;
}

bool DB_Local::abrir_DB(){
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open( _url.c_str(), &_db );

    // Qué pasaría si el archivo se corrompe? Cómo podemos mitigar ese riesgo?
    /* CREATE TABLE IF NOT EXISTS `TBL_DATOS` ( `id_muestra` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
     * `fecha` TEXT NOT NULL, `hora` TEXT NOT NULL, `latitud` REAL NOT NULL, `longitud` REAL NOT NULL,
     * `altura` REAL NOT NULL, `temperatura` REAL NOT NULL, `humedad` REAL NOT NULL, `velocidad_viento`
     * REAL NOT NULL, `direccion_viento` REAL NOT NULL, `precipitacion` REAL NOT NULL )
     * */

    if( rc != SQLITE_OK)
       return(false);

    return true;
}

bool DB_Local::validuser_DB(char min[]){
    char *mesg = 0;
    int rc = 0;

    char tmp []=""; // En este vector se traen los datos de la callback function.

    std::stringstream sqlsentence;
    sqlsentence << "SELECT passwd FROM usuario WHERE user_name = 'jabid' );" ;
    //sqlsentence << min <<  ");" ;

    rc = sqlite3_exec( _db, sqlsentence.str().c_str(), rellenar, (void*)&tmp, &mesg );
    std::cout << tmp<< std::endl;
    std::cout << min << std::endl;
    if (rc != SQLITE_OK )
        return false;




    return true;

}


bool DB_Local::cerrar_DB(){

    int rc = sqlite3_close( _db );

    if( rc != SQLITE_OK )
        return false;

    return true;
}

bool DB_Local::guardarT(double min, double prom, double max, double fecha,double hora){
    char *mesg = 0;
    int rc = 0;
    std::stringstream sqlsentence;

    sqlsentence << "INSERT INTO temperatura ('maximoT', 'minimoT', 'promedioT' , 'fecha' , 'hora') VALUES (";
    sqlsentence << max << ", " << min << ", " << prom << ", " << fecha << ", " << hora << ");" ;

    rc = sqlite3_exec( _db, sqlsentence.str().c_str(), 0, 0, &mesg );

    if (rc != SQLITE_OK )
        return false;

    return true;
}
bool DB_Local::guardarH(double min, double prom, double max, double fecha,double hora){
    char *mesg = 0;
    int rc = 0;
    std::stringstream sqlsentence;

    sqlsentence << "INSERT INTO humedad ('maximoH', 'minimoH', 'promedioH' , 'fecha' , 'hora') VALUES (";
    sqlsentence << max << ", " << min << ", " << prom << ", " << fecha << ", " << hora << ");" ;

    rc = sqlite3_exec( _db, sqlsentence.str().c_str(), 0, 0, &mesg );

    if (rc != SQLITE_OK )
        return false;

    return true;
}
bool DB_Local::guardarV(double min, double prom, double max, double fecha,double hora){
    char *mesg = 0;
    int rc = 0;
    std::stringstream sqlsentence;

    sqlsentence << "INSERT INTO velocidadviento ('maximoV', 'minimoV', 'promedioV' , 'fecha' , 'hora') VALUES (";
    sqlsentence << max << ", " << min << ", " << prom << ", " << fecha << ", " << hora << ");" ;

    rc = sqlite3_exec( _db, sqlsentence.str().c_str(), 0, 0, &mesg );

    if (rc != SQLITE_OK )
        return false;

    return true;
}
bool DB_Local::guardarP(double min, double prom, double max, double fecha,double hora){
    char *mesg = 0;
    int rc = 0;
    std::stringstream sqlsentence;

    sqlsentence << "INSERT INTO precipitacion ('maximoP', 'minimoP', 'promedioP' , 'fecha' , 'hora') VALUES (";
    sqlsentence << max << ", " << min << ", " << prom << ", " << fecha << ", " << hora << ");" ;

    rc = sqlite3_exec( _db, sqlsentence.str().c_str(), 0, 0, &mesg );

    if (rc != SQLITE_OK )
        return false;

    return true;
}
bool DB_Local::guardarI(double min, double prom, double max, double fecha,double hora){
    char *mesg = 0;
    int rc = 0;
    std::stringstream sqlsentence;

    sqlsentence << "INSERT INTO intensidadluz ('maximoI', 'minimoI', 'promedioI' , 'fecha' , 'hora') VALUES (";
    sqlsentence << max << ", " << min << ", " << prom << ", " << fecha << ", " << hora << ");" ;

    rc = sqlite3_exec( _db, sqlsentence.str().c_str(), 0, 0, &mesg );

    if (rc != SQLITE_OK )
        return false;

    return true;
}

bool DB_Local::recuperarTyH( double &min, double &prom, double &max ){
    char *mesg = 0;
    int rc = 0;

    double tmp[3] = {0., 0., 0.}; // En este vector se traen los datos de la callback function.

    std::stringstream sql;
    sql << "SELECT min, prom, max FROM TBL_TyH WHERE id_dato = (SELECT MAX(id_dato) FROM TBL_TyH);";

    rc = sqlite3_exec( _db, sql.str().c_str(), rellenar, (void*)&tmp, &mesg );

    if (rc != SQLITE_OK )
        return false;

    // Había olvidado hacer las asignaciones del vector local a los parámetros de la función
    // que has sido pasados por parámetro para devolver la información a la función que la llamó
    min = tmp[0];
    prom = tmp[1];
    max = tmp[2];

    return true;

}

DB_Local::DB_Local(){

}

int DB_Local::rellenar(void *data, int argc, char *argv[], char *campos[]){
    double *ttemp = (double*) data; // Se reinterpreta al puntero a variable doble

    for(int i = 0; i < 3; i++){
        ttemp[i] = atoi(argv[i]);   // Se convierte de texto a número doble
       // std::cout << argv[i] << std::endl;
    }

    return 0;
}
