/**
 * Project Clases
 */


#ifndef _RESULTADOS_H
#define _RESULTADOS_H

class Resultados {
public: 
    
float minimo();
    
float maximo();
    
float promedio();
protected: 
    float _minimo;
    float _maximo;
    float _promedio;
    text _fecha;
    text _hora;
    int _registro;
private: 
    
void Resultados();
};

#endif //_RESULTADOS_H