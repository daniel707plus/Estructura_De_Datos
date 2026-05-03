/***********************************************************************
 * Module:  ICompetencia.h
 * Author:  USUARIO
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class ICompetencia
 ***********************************************************************/
#ifndef ICOMPETENCIA_H
#define ICOMPETENCIA_H

class ICompetencia {
public:
    
    virtual void ejecutarTorneo() = 0; 
    
    virtual ~ICompetencia() {} 
};

#endif