#pragma once
#include <string>

class Usuario {
private: 
    std::string nombre;
    std::string apellido;
    std::string cedula;
public:
    Usuario( const std::string& nom, const std::string& ape, const std::string& ced);
    const std::string& getNombre() const;
    const std::string& getApellido() const;
    const std::string& getCedula() const;
    void setNombre(const std::string& nom);
    void setApellido(const std::string& ape);
    void setCedula(const std::string& ced);

};