#include <iostream>
#include "db_local.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "Bienvenido al sistema de alertas tempranas!" << endl;

    DB_Local a("baseproyect.db");
    a.abrir_DB();
    std::cout << a.guardarT( 56.89, 58.88, 63.77,12,17 ) << std::endl;
    std::cout << a.guardarH( 56.89, 58.88, 63.77,12,17 ) << std::endl;
    std::cout << a.guardarV( 56.89, 58.88, 63.77,12,17 ) << std::endl;
    std::cout << a.guardarP( 56.89, 58.88, 63.77,12,17 ) << std::endl;
    std::cout << a.guardarI( 56.89, 58.88, 63.77,12,17 ) << std::endl;
    //double min;
    a.validuser_DB("jabid");
    //std:: cout << "Min: " << min << std::endl;
    //double mi, ma, pro;
    //a.recuperarTyH( mi, pro, ma );

    //std:: cout << "Min: " << mi << ", Pro: " << pro << ", Máx: " << ma << std::endl;
    a.cerrar_DB();

    return 0;
}
