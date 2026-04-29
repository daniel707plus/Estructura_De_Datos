/***********************************************************************
 * Module:  VerificarCedula.h
 * Author:  USUARIO
 * Modified: mircoles, 8 de abril de 2026 22:31:12
 * Purpose: Declaration of the class VerificarCedula
 ***********************************************************************/


# ifndef VERIFICARCEDULA_H
# define VERIFICARCEDULA_H

# include <string>

using namespace std;

class VerificarCedula
{   
    public:
        bool validarCedula(const string& cedula);
};

# endif 