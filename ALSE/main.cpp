#include "inicio.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    INICIO w;
    w.show();


    return a.exec();
}
