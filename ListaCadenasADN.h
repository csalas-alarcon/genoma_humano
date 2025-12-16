#include "CadenaADN.h"
#include <string>

using namespace std;

class NodoLista{
   private:
    NodoLista* anterior;
    NodoLista* siguiente;
    CadenaADN cadenaADN;

   public:
    //Constructor por defecto
    NodoLista();
    //Constructor sobrecargado
    NodoLista(NodoLista*, NodoLista*, const CadenaADN& );
    //Constructor de copia
    NodoLista(const NodoLista&);
    //Operador de asignación
    NodoLista& operator=(const NodoLista &);
    //Destructor
    ~NodoLista();
    //Devuelve el puntero al nodo anterior de la lista
    NodoLista* getAnterior() const;
    //Devuelve el puntero al siguiente nodo de la lista
    NodoLista* getSiguiente() const;
    //Devuelve la cadena de ADN almacenada en el nodo
    CadenaADN getCadenaADN() const;
    //Modifica el puntero al nodo anterior de la lista
    void setAnterior(NodoLista* );
    //Modifica el puntero al siguiente nodo de la lista
    void setSiguiente(NodoLista* );
    //Modifica la cadena de ADN
    void setCadenaADN(const CadenaADN& );
};

class IteradorLista {
    friend class ListaCadenasADN;

   private:
    NodoLista* pt;

   public:
    //Constructor por defecto: puntero a nullptr
    IteradorLista();
    //Constructor de copia
    IteradorLista(const IteradorLista&);
    //Destructor: puntero a nullptr
    ~IteradorLista();
    //Operador de asignación
    IteradorLista& operator=(const IteradorLista&);
    //Avanza una posición en la lista
    void step();
    //Retrocede una posición en la lista
    void rstep();
    //Operador de comparación
    bool operator==(const IteradorLista&) const;
    //Operador de comparación
    bool operator!=(const IteradorLista&) const;
};

class ListaCadenasADN{
private:
    NodoLista* head;
    NodoLista* tail;
    int numElementos;

public:
    //Constructor por defecto: lista vacía
    ListaCadenasADN();
    //Constructor de copia
    ListaCadenasADN(const ListaCadenasADN&);
    //Operador de asignación
    ListaCadenasADN& operator=(const ListaCadenasADN &);
    //Destructor
    ~ListaCadenasADN();
    //Devuelve un iterador que apunta al primer elemento de la lista
    IteradorLista begin() const;
    //Devuelve un iterador que apunta después del último elemento de la lista: puntero a nullptr
    IteradorLista end() const;
    //Devuelve un iterador que apunta al último elemento de la lista
    IteradorLista rbegin() const;
    //Devuelve un iterador que apunta antes del primer elemento de la lista: puntero a nullptr
    IteradorLista rend() const;
    //Devuelve la cadena de ADN apuntada por el iterador
    CadenaADN getCadenaADN(IteradorLista) const;
    //Comprueba si la lista está vacía
    bool esVacia() const;
    //Inserta una cadena de ADN al principio de la lista
    void insertarInicio(const CadenaADN&);
    //Inserta una cadena de ADN al final de la lista
    void insertarFinal(const CadenaADN&);
    //Inserta una cadena de ADN justo antes de la posición apuntada por el iterador
    bool insertar( IteradorLista, const CadenaADN&);
    //Asigna la cadena de ADN la posición apuntada por el iterador
    bool asignar(IteradorLista, const CadenaADN&);
    //Borra la primera cadena de ADN de la lista
    bool borrarPrimera();
    //Borra la última cadena de ADN de la lista
    bool borrarUltima();
    //Borra la cadena de ADN a la que apunta el iterador
    bool borrar(IteradorLista &);
    //Devuelve cuántos elementos hay en la lista
    int longitud() const;
    //Cuenta el número de apariciones de la cadena de ADN que se pasa como parámetro (según su operador ==)
    int contar(const CadenaADN &) const;
    //Devuelve una nueva lista con todos los elementos de la lista actual y, a continuación, todos los de la lista que se pasa como parámetro
    ListaCadenasADN concatenar(const ListaCadenasADN &) const;
    //Devuelve una nueva lista con todos los elementos de la lista actual que no están en la que se pasa como parámetro
    ListaCadenasADN diferencia(const ListaCadenasADN &) const;
    //Devuelve una cadena de ADN con la concatenación de todas las secuencias de la lista y la cadena vacía como descripción
    CadenaADN concatenar() const;
    //Devuelve una cadena de texto con el contenido completo de la lista
    string aCadena() const;
};