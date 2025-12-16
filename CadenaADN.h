#ifndef CADENAADN_H
#define CADENAADN_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector> // Necesario para el nuevo método obtenerCodones()
using namespace std;

class CadenaADN {
    private:
    string secuencia = "ATG";
    string descripcion = "";
    
    // Auxiliares
    bool validador(const string &, const string &) const;
    int contador(const string &) const;

    public:
    //Constructor por defecto
    CadenaADN();
    //Constructor sobrecargado
    CadenaADN(const string &, const string &);
    //Constructor de copia
    CadenaADN(const CadenaADN &);
    //Destructor:
    ~CadenaADN();
    //Operador de asignación
    CadenaADN& operator=(const CadenaADN &);
    //Operadores de comparación
    bool operator==(const CadenaADN &) const;
    bool operator!=(const CadenaADN &) const;
    //Getters y setters
    string getSecuencia() const;
    string getDescripcion() const;
    int getLongitud() const;
    void setSecuencia(const string &);
    void setDescripcion(const string &);
    
    //Cuentas de nucleótidos
    int cuentaA() const;
    int cuentaT() const;
    int cuentaC() const;
    int cuentaG() const;
    bool cumpleChargaff() const;
    double proporcionGC() const;
    
    //Búsqueda de codones
    int contarCodon(const string &) const;
    
    // NUEVO: Método para obtener todos los codones de la secuencia
    // Necesario para los métodos O(1) de ListaCadenasADN
    vector<string> obtenerCodones() const; // 

    //Búsqueda de subsecuencias
    int buscarSubsecuencia(const string &) const;
    int posicionUltimaAparicion(const string &) const;
    //Búsqueda de elementos consecutivos
    int longitudMaximaConsecutiva(char) const;
    int longitudMaximaConsecutivaCualquiera() const;
    //Mutaciones
    bool mutar(int, char);
    int contarMutaciones(const CadenaADN &) const;
    //Secuencias complementarias
    bool esSecuenciaComplementaria(const CadenaADN&) const;
    //Modificaciones
    void invertir();
    //Almacenaje y lectura de fichero
    bool guardarEnFichero(const string &) const;
    bool cargarDesdeFichero(const string &);
};

#endif // CADENAADN_H