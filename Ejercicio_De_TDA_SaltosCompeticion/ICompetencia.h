#ifndef ICOMPETENCIA_H
#define ICOMPETENCIA_H

class ICompetencia {
public:
    
    virtual void ejecutarTorneo() = 0; 
    
    virtual ~ICompetencia() {} 
};

#endif