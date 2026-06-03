#include "Usuario.h"

Usuario::Usuario( const std::string& nom, const std::string& ape, const std::string& ced) {
    nombre = nom;
    apellido = ape;
    cedula = ced;
}

const std::string& Usuario::getNombre() const {
     return nombre;
     }
const std::string& Usuario::getApellido() const {
     return apellido;
     }
const std::string& Usuario::getCedula() const {
     return cedula; 
    }

void Usuario::setNombre(const std::string& nom) { 
    nombre = nom;
 }
void Usuario::setApellido(const std::string& ape) { 
    apellido = ape; 
 }
void Usuario::setCedula(const std::string& ced) { 
    cedula = ced; 
 }