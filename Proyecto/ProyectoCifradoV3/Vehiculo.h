#pragma once
#include <string>

class Vehiculo {
private:
    std::string placa;
public:
    Vehiculo(const std::string& pla);
    const std::string& getPlaca() const;
    void setPlaca(const std::string& pla);
};