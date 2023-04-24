/**
 * Project Clases
 */


#ifndef _TEMPERATURA_H
#define _TEMPERATURA_H

#include "Resultados.h"


class Temperatura: public Resultados {
public: 
    
/**
 * @param t
 */
void Temperatura(float t);
private: 
    float _temperatura;
    
void Temperatura();
};

#endif //_TEMPERATURA_H