/**
 * Project Clases
 */


#ifndef _HUMEDAD_H
#define _HUMEDAD_H

#include "Resultados.h"


class Humedad: public Resultados {
public: 
    
/**
 * @param h
 */
void Humedad(float h);
private: 
    float _humedad;
    
void Humedad();
};

#endif //_HUMEDAD_H