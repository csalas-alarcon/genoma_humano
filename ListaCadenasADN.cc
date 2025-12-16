#include "ListaCadenasADN.h"
#include <sstream>

// =============================================
// IMPLEMENTACIÓN DE NODOLISTA
// =============================================

// Constructor por defecto - nodo vacío
NodoLista::NodoLista() {
    anterior = nullptr;
    siguiente = nullptr;
    cadenaADN = CadenaADN();  // Cadena ADN por defecto
}

// Constructor con parámetros
NodoLista::NodoLista(NodoLista* ant, NodoLista* sig, const CadenaADN& cad) {
    anterior = ant;
    siguiente = sig;
    cadenaADN = cad;
}

// Constructor de copia
NodoLista::NodoLista(const NodoLista& otro) {
    anterior = otro.anterior;
    siguiente = otro.siguiente;
    cadenaADN = otro.cadenaADN;
}

// Operador de asignación
NodoLista& NodoLista::operator=(const NodoLista& otro) {
    if (this != &otro) {  // Evitar auto-asignación
        anterior = otro.anterior;
        siguiente = otro.siguiente;
        cadenaADN = otro.cadenaADN;
    }
    return *this;
}

// Destructor
NodoLista::~NodoLista() {
    // No libera memoria - la lista se encarga de eso
}

// GETTERS
NodoLista* NodoLista::getAnterior() const {
    return anterior;
}

NodoLista* NodoLista::getSiguiente() const {
    return siguiente;
}

CadenaADN NodoLista::getCadenaADN() const {
    return cadenaADN;
}

// SETTERS
void NodoLista::setAnterior(NodoLista* ant) {
    anterior = ant;
}

void NodoLista::setSiguiente(NodoLista* sig) {
    siguiente = sig;
}

void NodoLista::setCadenaADN(const CadenaADN& cad) {
    cadenaADN = cad;
}

// =============================================
// IMPLEMENTACIÓN DE ITERADORLISTA
// =============================================

// Constructor por defecto
IteradorLista::IteradorLista() {
    pt = nullptr;  // Apunta a nada inicialmente
}

// Constructor de copia
IteradorLista::IteradorLista(const IteradorLista& other) {
    pt = other.pt;  // Copia el puntero
}

// Destructor
IteradorLista::~IteradorLista() {
    pt = nullptr;  // Solo anula el puntero
}

// Operador de asignación
IteradorLista& IteradorLista::operator=(const IteradorLista& other) {
    if (this != &other) {  // Evitar auto-asignación
        pt = other.pt;
    }
    return *this;
}

// Avanza al siguiente nodo
void IteradorLista::step() {
    if (pt != nullptr) {
        pt = pt->getSiguiente();
    }
}

// Retrocede al nodo anterior
void IteradorLista::rstep() {
    if (pt != nullptr) {
        pt = pt->getAnterior();
    }
}

// Operador de igualdad
bool IteradorLista::operator==(const IteradorLista& other) const {
    return (pt == other.pt);  // Compara punteros
}

// Operador de desigualdad
bool IteradorLista::operator!=(const IteradorLista& other) const {
    return (pt != other.pt);  // Compara punteros
}

// =============================================
// IMPLEMENTACIÓN DE LISTACADENASADN
// =============================================

// Constructor por defecto - lista vacía
ListaCadenasADN::ListaCadenasADN() {
    head = nullptr;
    tail = nullptr;
    numElementos = 0;
}

// Constructor de copia
ListaCadenasADN::ListaCadenasADN(const ListaCadenasADN& other) {
    head = nullptr;
    tail = nullptr;
    numElementos = 0;
    
    // Copiar todos los elementos de la otra lista
    NodoLista* actual = other.head;
    while (actual != nullptr) {
        insertarFinal(actual->getCadenaADN());
        actual = actual->getSiguiente();
    }
}

// Operador de asignación
ListaCadenasADN& ListaCadenasADN::operator=(const ListaCadenasADN& other) {
    if (this != &other) {  // Evitar auto-asignación
        // Limpiar lista actual
        while (head != nullptr) {
            borrarPrimera();
        }
        
        // Copiar todos los elementos de la otra lista
        NodoLista* actual = other.head;
        while (actual != nullptr) {
            insertarFinal(actual->getCadenaADN());
            actual = actual->getSiguiente();
        }
    }
    return *this;
}

// Destructor
ListaCadenasADN::~ListaCadenasADN() {
    // Liberar todos los nodos
    while (head != nullptr) {
        borrarPrimera();
    }
}

// =============================================
// ITERADORES
// =============================================

// Iterador al primer elemento
IteradorLista ListaCadenasADN::begin() const {
    IteradorLista it;
    it.pt = head;  // Puede ser nullptr si la lista está vacía
    return it;
}

// Iterador después del último elemento
IteradorLista ListaCadenasADN::end() const {
    IteradorLista it;
    it.pt = nullptr;  // Siempre nullptr
    return it;
}

// Iterador al último elemento
IteradorLista ListaCadenasADN::rbegin() const {
    IteradorLista it;
    it.pt = tail;  // Puede ser nullptr si la lista está vacía
    return it;
}

// Iterador antes del primer elemento
IteradorLista ListaCadenasADN::rend() const {
    IteradorLista it;
    it.pt = nullptr;  // Siempre nullptr
    return it;
}

// =============================================
// OPERACIONES BÁSICAS
// =============================================

// Obtiene la cadena ADN apuntada por un iterador
CadenaADN ListaCadenasADN::getCadenaADN(IteradorLista it) const {
    if (it.pt != nullptr) {
        return it.pt->getCadenaADN();
    } else {
        return CadenaADN();  // Cadena por defecto si el iterador no es válido
    }
}

// Verifica si la lista está vacía
bool ListaCadenasADN::esVacia() const {
    return (head == nullptr);
}

// Inserta una cadena al principio de la lista
void ListaCadenasADN::insertarInicio(const CadenaADN& cadena) {
    // Crear nuevo nodo
    NodoLista* nuevo = new NodoLista(nullptr, head, cadena);
    
    // Actualizar enlaces
    if (head != nullptr) {
        head->setAnterior(nuevo);
    } else {
        tail = nuevo;  // Lista estaba vacía
    }
    
    head = nuevo;
    numElementos++;
}

// Inserta una cadena al final de la lista
void ListaCadenasADN::insertarFinal(const CadenaADN& cadena) {
    // Crear nuevo nodo
    NodoLista* nuevo = new NodoLista(tail, nullptr, cadena);
    
    // Actualizar enlaces
    if (tail != nullptr) {
        tail->setSiguiente(nuevo);
    } else {
        head = nuevo;  // Lista estaba vacía
    }
    
    tail = nuevo;
    numElementos++;
}

// Inserta una cadena antes de la posición del iterador
bool ListaCadenasADN::insertar(IteradorLista it, const CadenaADN& cadena) {
    if (it.pt == nullptr) {
        return false;  // Iterador no válido
    }
    
    if (it.pt == head) {
        insertarInicio(cadena);  // Insertar al principio
    } else {
        // Insertar en medio
        NodoLista* nuevo = new NodoLista(it.pt->getAnterior(), it.pt, cadena);
        it.pt->getAnterior()->setSiguiente(nuevo);
        it.pt->setAnterior(nuevo);
        numElementos++;
    }
    
    return true;
}

// Asigna una nueva cadena a la posición del iterador
bool ListaCadenasADN::asignar(IteradorLista it, const CadenaADN& cadena) {
    if (it.pt == nullptr) {
        return false;  // Iterador no válido
    }
    
    it.pt->setCadenaADN(cadena);
    return true;
}

// =============================================
// OPERACIONES DE BORRADO
// =============================================

// Borra la primera cadena de la lista
bool ListaCadenasADN::borrarPrimera() {
    if (head == nullptr) {
        return false;  // Lista vacía
    }
    
    NodoLista* aBorrar = head;
    head = head->getSiguiente();
    
    if (head != nullptr) {
        head->setAnterior(nullptr);
    } else {
        tail = nullptr;  // Lista quedó vacía
    }
    
    delete aBorrar;
    numElementos--;
    return true;
}

// Borra la última cadena de la lista
bool ListaCadenasADN::borrarUltima() {
    if (tail == nullptr) {
        return false;  // Lista vacía
    }
    
    NodoLista* aBorrar = tail;
    tail = tail->getAnterior();
    
    if (tail != nullptr) {
        tail->setSiguiente(nullptr);
    } else {
        head = nullptr;  // Lista quedó vacía
    }
    
    delete aBorrar;
    numElementos--;
    return true;
}

// Borra la cadena apuntada por el iterador
bool ListaCadenasADN::borrar(IteradorLista& it) {
    if (it.pt == nullptr) {
        return false;  // Iterador no válido
    }
    
    // Casos especiales: primer o último elemento
    if (it.pt == head) {
        borrarPrimera();
    } else if (it.pt == tail) {
        borrarUltima();
    } else {
        // Elemento en medio
        NodoLista* anterior = it.pt->getAnterior();
        NodoLista* siguiente = it.pt->getSiguiente();
        
        anterior->setSiguiente(siguiente);
        siguiente->setAnterior(anterior);
        
        delete it.pt;
        numElementos--;
    }
    
    it.pt = nullptr;  // Como especificado, poner iterador a nullptr
    return true;
}

// =============================================
// OPERACIONES DE CONSULTA
// =============================================

// Devuelve el número de elementos en la lista
int ListaCadenasADN::longitud() const {
    return numElementos;
}

// Cuenta cuántas veces aparece una cadena en la lista
int ListaCadenasADN::contar(const CadenaADN& cadena) const {
    int contador = 0;
    NodoLista* actual = head;
    
    while (actual != nullptr) {
        // Compara solo las secuencias (no las descripciones)
        if (actual->getCadenaADN().getSecuencia() == cadena.getSecuencia()) {
            contador++;
        }
        actual = actual->getSiguiente();
    }
    
    return contador;
}

// =============================================
// OPERACIONES AVANZADAS
// =============================================

// Concatena esta lista con otra
ListaCadenasADN ListaCadenasADN::concatenar(const ListaCadenasADN& otra) const {
    ListaCadenasADN resultado;
    
    // Copiar elementos de esta lista
    NodoLista* actual = head;
    while (actual != nullptr) {
        resultado.insertarFinal(actual->getCadenaADN());
        actual = actual->getSiguiente();
    }
    
    // Copiar elementos de la otra lista
    actual = otra.head;
    while (actual != nullptr) {
        resultado.insertarFinal(actual->getCadenaADN());
        actual = actual->getSiguiente();
    }
    
    return resultado;
}

// Devuelve los elementos de esta lista que no están en la otra
ListaCadenasADN ListaCadenasADN::diferencia(const ListaCadenasADN& otra) const {
    ListaCadenasADN resultado;
    NodoLista* actual = head;
    
    while (actual != nullptr) {
        CadenaADN cadenaActual = actual->getCadenaADN();
        bool encontrado = false;
        
        // Buscar si esta cadena está en la otra lista
        NodoLista* actualOtra = otra.head;
        while (actualOtra != nullptr && !encontrado) {
            if (cadenaActual.getSecuencia() == actualOtra->getCadenaADN().getSecuencia()) {
                encontrado = true;
            }
            actualOtra = actualOtra->getSiguiente();
        }
        
        // Si no se encontró, añadir a resultado
        if (!encontrado) {
            resultado.insertarFinal(cadenaActual);
        }
        
        actual = actual->getSiguiente();
    }
    
    return resultado;
}

// Concatena todas las secuencias en una sola cadena ADN
CadenaADN ListaCadenasADN::concatenar() const {
    if (esVacia()) {
        return CadenaADN();  // Cadena por defecto si lista vacía
    }
    
    string secuenciaCompleta;
    NodoLista* actual = head;
    
    while (actual != nullptr) {
        secuenciaCompleta += actual->getCadenaADN().getSecuencia();
        actual = actual->getSiguiente();
    }
    
    return CadenaADN(secuenciaCompleta, "");  // Descripción vacía como especificado
}

// Convierte la lista a una cadena de texto
string ListaCadenasADN::aCadena() const {
    stringstream ss;
    NodoLista* actual = head;
    
    while (actual != nullptr) {
        CadenaADN cadena = actual->getCadenaADN();
        ss << cadena.getDescripcion() << ":" << cadena.getSecuencia();
        
        // Añadir salto de línea solo entre elementos
        if (actual->getSiguiente() != nullptr) {
            ss << "\n";
        }
        
        actual = actual->getSiguiente();
    }
    
    return ss.str();
}