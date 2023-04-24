#ifndef DB_LOCAL_H
#define DB_LOCAL_H
#include <string>
#include <sqlite3.h>

class DB_Local{

public:
    DB_Local(std::string path);
    bool abrir_DB();
    bool validuser_DB(char min[]);
    bool cerrar_DB();
    bool guardarT(double min, double prom, double max, double fecha,double hora);
    bool guardarH(double min, double prom, double max, double fecha,double hora);
    bool guardarV(double min, double prom, double max, double fecha,double hora);
    bool guardarP(double min, double prom, double max, double fecha,double hora);
    bool guardarI(double min, double prom, double max, double fecha,double hora);
    bool recuperarTyH(double &min, double &prom, double &max );


private:
    DB_Local();
    sqlite3         *_db;
    std::string     _url;
    static int rellenar(void* data, int argc, char* argv[], char* campos[] );
};

#endif // DB_LOCAL_H
