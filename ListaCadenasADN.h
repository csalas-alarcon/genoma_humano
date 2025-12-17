#ifndef LISTACADENASADN_H
#define LISTACADENASADN_H

#include "CadenaADN.h"
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class ListaCadenasADN;

class IteradorLista {
    friend class ListaCadenasADN;
   private:
    list<CadenaADN>::iterator iter;
    bool vacio; // Para controlar el estado del constructor por defecto

   public:
    IteradorLista();
    IteradorLista(const IteradorLista&);
    ~IteradorLista();
    IteradorLista& operator=(const IteradorLista&);
    void step();
    void rstep();
    bool operator==(const IteradorLista&) const;
    bool operator!=(const IteradorLista&) const;
    bool esVacio() const; // Requerido por el enunciado [cite: 152, 236]
};

class ListaCadenasADN {
private:
    list<CadenaADN> data; // Contenedor principal STL [cite: 6, 205]
    
    // Atributos para eficiencia O(1) o independiente [cite: 8, 172, 191]
    unordered_map<string, int> frecSecuencias;
    unordered_map<string, int> frecCodones;
    map<string, bool> codonesUnicos;
    map<string, map<string, bool>> mapaCodonSecuencias;

    void actualizarEstructuras(const CadenaADN& cadena, int incremento);

public:
    ListaCadenasADN();
    ListaCadenasADN(const ListaCadenasADN&);
    ListaCadenasADN& operator=(const ListaCadenasADN &);
    ~ListaCadenasADN();

    IteradorLista begin();
    IteradorLista end();
    IteradorLista rbegin();
    IteradorLista rend();

    CadenaADN getCadenaADN(IteradorLista);
    bool esVacia();
    void insertarInicio(const CadenaADN&);
    void insertarFinal(const CadenaADN&);
    bool insertar(IteradorLista, const CadenaADN&);
    bool insertarDespues(IteradorLista, const CadenaADN&); // Nuevo [cite: 118, 162]
    bool asignar(IteradorLista, const CadenaADN&);
    bool borrarPrimera();
    bool borrarUltima();
    bool borrar(IteradorLista &);
    int longitud();
    int contar(const CadenaADN &);
    ListaCadenasADN concatenar(ListaCadenasADN &);
    ListaCadenasADN diferencia(ListaCadenasADN &);
    CadenaADN concatenar();
    string aCadena();

    // Métodos nuevos Práctica 3 [cite: 117]
    int frecuenciaCodon(const string &);
    int frecuenciaCadena(const CadenaADN&);
    string listaCodones();
    string listaCadenasADN();
    string listaCadenasConCodon(const string&);
    void eliminaDuplicados();
};

#endif