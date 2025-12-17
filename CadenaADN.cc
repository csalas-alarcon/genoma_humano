#include "CadenaADN.h"
using namespace std;


vector<string> CadenaADN::obtenerCodones() const {
    vector<string> v;
    for (size_t i = 0; i + 2 < secuencia.length(); i += 3) {
        v.push_back(secuencia.substr(i, 3));
    }
    return v;
}


// =============================================
// FUNCIONES AUXILIARES
// =============================================

// Valida si una secuencia y descripción son válidas
bool CadenaADN::validador(const string &isec, const string &idesc) const {
    // La secuencia debe tener al menos 3 caracteres
    if (isec.length() < 3) { 
        return false; 
    }
    
    // La secuencia debe tener longitud múltiplo de 3
    if (isec.length() % 3 != 0) { 
        return false; 
    }
    
    // NOTA: Esta línea estaba comentada - no requiere que empiece con ATG
    // if (isec.substr(0, 3) != "ATG") { return false; }
    
    // Todos los caracteres deben ser A, T, C o G
    for (char c : isec) {
        if (c != 'A' && c != 'T' && c != 'C' && c != 'G') { 
            return false;
        }
    }

    // La descripción no puede contener saltos de línea
    if (idesc.find("\n") != string::npos || idesc.find("\r") != string::npos) {
        return false;
    }
    
    return true;
}

// Cuenta cuántas veces aparece una subcadena en la secuencia
int CadenaADN::contador(const string &serie) const {
    int contador = 0;
    int longitud_serie = serie.length();

    for (int i = 0; i < secuencia.length(); i++) {
        if (secuencia.substr(i, longitud_serie) == serie) { 
            contador++; 
        }
    }
    return contador;
}

// =============================================
// CONSTRUCTORES Y DESTRUCTOR
// =============================================

// Constructor por defecto - crea secuencia "ATG" vacía
CadenaADN::CadenaADN() {
    secuencia = "ATG"; 
    descripcion = "";
}

// Constructor con parámetros - valida antes de asignar
CadenaADN::CadenaADN(const string &isec, const string &idesc) {
    secuencia = "ATG";
    descripcion = "";
    
    if (validador(isec, idesc)) {
        secuencia = isec; 
        descripcion = idesc;
    }
}

// Constructor de copia
CadenaADN::CadenaADN(const CadenaADN &molecula) {
    secuencia = "ATG"; 
    descripcion = ""; 
    
    if (validador(molecula.secuencia, molecula.descripcion)) {
        secuencia = molecula.secuencia; 
        descripcion = molecula.descripcion;
    }
}

// Destructor
CadenaADN::~CadenaADN() { 
    // No necesita hacer nada especial
}

// Operador de asignación
CadenaADN& CadenaADN::operator=(const CadenaADN &molecula) {
    if (validador(molecula.secuencia, molecula.descripcion)) {
        secuencia = molecula.secuencia; 
        descripcion = molecula.descripcion;
    }
    return (*this);
}

// =============================================
// OPERADORES DE COMPARACIÓN
// =============================================

// Operador de igualdad - compara secuencia Y descripción
bool CadenaADN::operator==(const CadenaADN &molecula) const { 
    return (secuencia == molecula.secuencia && descripcion == molecula.descripcion);
}

// Operador de desigualdad
bool CadenaADN::operator!=(const CadenaADN &molecula) const { 
    return !(secuencia == molecula.secuencia && descripcion == molecula.descripcion);
}

// =============================================
// GETTERS Y SETTERS
// =============================================

string CadenaADN::getSecuencia() const { 
    return secuencia; 
}

string CadenaADN::getDescripcion() const { 
    return descripcion; 
}

int CadenaADN::getLongitud() const { 
    return secuencia.length();
}

void CadenaADN::setSecuencia(const string &isec) { 
    if (validador(isec, "")) { 
        secuencia = isec; 
    }
}

void CadenaADN::setDescripcion(const string &idesc) { 
    if (validador("ATG", idesc)) { 
        descripcion = idesc; 
    }
}

// =============================================
// CONTEO DE NUCLEÓTIDOS
// =============================================

int CadenaADN::cuentaA() const { 
    return contador("A"); 
}

int CadenaADN::cuentaT() const { 
    return contador("T"); 
}

int CadenaADN::cuentaC() const { 
    return contador("C"); 
}

int CadenaADN::cuentaG() const { 
    return contador("G"); 
}

// Verifica si cumple las proporciones de Chargaff
bool CadenaADN::cumpleChargaff() const {
    int numA = cuentaA();
    int numT = cuentaT();
    int numC = cuentaC();
    int numG = cuentaG();
    
    bool cond1 = (numA == numT);
    bool cond2 = (numC == numG);
    bool cond3 = ((numA + numG) / (double)(numT + numC)) == 1.0;
    
    return (cond1 && cond2 && cond3);
}

// Calcula la proporción de G y C en la secuencia
double CadenaADN::proporcionGC() const {
    int cuentaGC = cuentaC() + cuentaG();
    int total = cuentaGC + cuentaA() + cuentaT();
    return ((double)cuentaGC / total);
}

// =============================================
// BÚSQUEDA DE CODONES
// =============================================

// Cuenta cuántas veces aparece un codón (3 letras)
int CadenaADN::contarCodon(const string &icodon) const { 
    if (icodon.length() == 3) {
        return contador(icodon); 
    } else { 
        return 0; 
    }
}

// =============================================
// BÚSQUEDA DE SUBSECUENCIAS
// =============================================

// Busca la primera aparición de una subsecuencia
int CadenaADN::buscarSubsecuencia(const string &serie) const { 
    int posicion = -1;
    int i = 0;
    int longitud_serie = serie.length();
    
    if (longitud_serie == 0) { 
        return posicion; 
    }
    
    while (posicion == -1 && (i + longitud_serie) <= secuencia.length()) {
        if (secuencia.substr(i, longitud_serie) == serie) { 
            posicion = i; 
        } else { 
            i++; 
        }
    }
    return posicion;
}

// Busca la última aparición de una subsecuencia
int CadenaADN::posicionUltimaAparicion(const string &serie) const {
    int posicion = -1;
    int longitud_serie = serie.length();
    
    if (longitud_serie == 0) { 
        return posicion; 
    }

    for (int i = 0; (i + longitud_serie) <= secuencia.length(); i++) {
        if (secuencia.substr(i, longitud_serie) == serie) {
            posicion = i;
        }
    }
    return posicion;
}

// =============================================
// ELEMENTOS CONSECUTIVOS
// =============================================

// Encuentra la longitud máxima de nucleótidos consecutivos del mismo tipo
int CadenaADN::longitudMaximaConsecutiva(char nucleo) const {
    int actual = 0;
    int maxima = 0;
    
    for (int i = 0; i < secuencia.length(); i++) {
        if (secuencia[i] == nucleo) {
            actual++;
        } else {
            if (actual > maxima) { 
                maxima = actual;
            }
            actual = 0;
        }
    }
    
    // Verificar la última secuencia
    if (actual > maxima) {
        maxima = actual;
    }
    
    return maxima;
}

// Encuentra la longitud máxima de cualquier nucleótido consecutivo
int CadenaADN::longitudMaximaConsecutivaCualquiera() const {
    int maxA = longitudMaximaConsecutiva('A');
    int maxT = longitudMaximaConsecutiva('T');
    int maxC = longitudMaximaConsecutiva('C');
    int maxG = longitudMaximaConsecutiva('G');
    
    // Encontrar el máximo de todos
    int maximo = maxA;
    if (maxT > maximo) maximo = maxT;
    if (maxC > maximo) maximo = maxC;
    if (maxG > maximo) maximo = maxG;
    
    return maximo;
}

// =============================================
// MUTACIONES
// =============================================

// Cambia un nucleótido en una posición específica
bool CadenaADN::mutar(int pos, char nucleo) {
    // Verificar que la posición sea válida y el nucleótido sea A,T,C o G
    if (pos >= 0 && pos < secuencia.length() && 
        (nucleo == 'A' || nucleo == 'T' || nucleo == 'C' || nucleo == 'G')) {
        secuencia[pos] = nucleo;
        return true;
    } else {
        return false;
    }
}

// Cuenta las diferencias entre esta secuencia y otra
int CadenaADN::contarMutaciones(const CadenaADN &molecula) const {
    // Solo comparar si tienen la misma longitud
    if (secuencia.length() != molecula.secuencia.length()) { 
        return -1; 
    }
    
    int diferencias = 0;
    for (int i = 0; i < secuencia.length(); i++) {
        if (secuencia[i] != molecula.secuencia[i]) { 
            diferencias++; 
        }
    }
    return diferencias; 
}

// =============================================
// SECUENCIAS COMPLEMENTARIAS
// =============================================

// Verifica si esta secuencia es complementaria de otra
bool CadenaADN::esSecuenciaComplementaria(const CadenaADN& molecula) const {
    // Deben tener la misma longitud
    if (secuencia.length() != molecula.secuencia.length()) { 
        return false; 
    }
    
    // Verificar cada par de nucleótidos
    for (int i = 0; i < secuencia.length(); i++) {
        switch (secuencia[i]) {
            case 'A':
                if (molecula.secuencia[i] != 'T') { return false; }
                break;
            case 'T':
                if (molecula.secuencia[i] != 'A') { return false; }
                break;
            case 'C':
                if (molecula.secuencia[i] != 'G') { return false; }
                break;
            case 'G':
                if (molecula.secuencia[i] != 'C') { return false; }
                break;
            default:
                return false;  // Carácter inválido
        }
    }
    return true;
}

// =============================================
// MODIFICACIONES
// =============================================

// Invierte la secuencia (A->T, T->A, C->G, G->C)
void CadenaADN::invertir() {
    for (int i = 0; i < secuencia.length(); i++) {
        switch (secuencia[i]) {
            case 'A': 
                secuencia[i] = 'T';
                break;
            case 'T':
                secuencia[i] = 'A';
                break;
            case 'C':
                secuencia[i] = 'G';
                break;
            case 'G':
                secuencia[i] = 'C';
                break;
        }
    }  
}

// =============================================
// ALMACENAJE Y LECTURA DE FICHEROS
// =============================================

// Guarda la cadena ADN en un fichero
bool CadenaADN::guardarEnFichero(const string &path) const {
    ofstream fichero(path);
    if (fichero.is_open()) {
        fichero << descripcion << "\n";
        fichero << secuencia << "\n";
        fichero.close();
        return true;
    } else { 
        cout << "Error al abrir el archivo.\n"; 
        return false;
    }
}

// Carga la cadena ADN desde un fichero
bool CadenaADN::cargarDesdeFichero(const string &path) {
    ifstream fichero(path);
    if (fichero.is_open()) {
        string linea_descripcion, linea_secuencia;
        getline(fichero, linea_descripcion);
        getline(fichero, linea_secuencia);
        
        descripcion = linea_descripcion;
        secuencia = linea_secuencia;
        
        fichero.close();
        return true;
    } else { 
        cout << "Error al abrir el archivo.\n"; 
        return false;
    }
}

/*
 * =============================================
 * EJEMPLOS DE MÉTODOS PARA POSIBLE EXAMEN
 * =============================================
 * 
 * ESTE ARCHIVO ES SOLO DE REFERENCIA
 * NO DESCOMENTAR NI COMPILAR ESTE CÓDIGO DIRECTAMENTE
 * 
 * Contiene implementaciones de ejemplo que podrían pedir
 * en el examen para añadir a la clase ListaCadenasADN
 */

/*
// ===========================================================================
// EJEMPLO 1: Buscar cadena por descripción
// ===========================================================================
// Busca en la lista una cadena con la descripción especificada
// Parámetros:
//   - descripcionBuscada: string con la descripción a buscar
// Retorna:
//   - Puntero a la CadenaADN encontrada (para poder modificarla)
//   - nullptr si no se encuentra
// Notas:
//   - Usa getCadenaADN(it) para obtener copia para comparar
//   - Pero devuelve &(it.pt->getCadenaADN()) para devolver referencia al original
//   - CUIDADO: Si borras el nodo, el puntero queda inválido

CadenaADN* ListaCadenasADN::buscarPorDescripcion(const string& descripcionBuscada) {
    // Recorrer toda la lista desde el primer elemento hasta el final
    for (IteradorLista it = begin(); it != end(); it.step()) {
        // Obtener una copia de la cadena actual para poder llamar a getDescripcion()
        CadenaADN cadenaActual = getCadenaADN(it);
        
        // Comparar la descripción de la cadena actual con la descripción buscada
        if (cadenaActual.getDescripcion() == descripcionBuscada) {
            // Encontrada! Devolver puntero a la cadena original en el nodo
            // it.pt->getCadenaADN() accede directamente a la cadena en el nodo
            // & obtiene la dirección de memoria (puntero) de esa cadena
            return &(it.pt->getCadenaADN());
        }
    }
    // Si llegamos aquí, recorrimos toda la lista y no encontramos la descripción
    return nullptr;  // nullptr indica "no encontrado"
}

// ===========================================================================
// EJEMPLO 2: Filtrar secuencias por longitud mínima  
// ===========================================================================
// Crea una nueva lista con solo las secuencias que tienen longitud >= mínimo
// Parámetros:
//   - longitudMinima: longitud mínima que deben tener las secuencias
// Retorna:
//   - Nueva ListaCadenasADN con las secuencias que cumplen la condición
// Notas:
//   - No modifica la lista original
//   - Crea una nueva lista con COPIA de las cadenas que cumplen
//   - Usa insertarFinal() para mantener el orden original

ListaCadenasADN ListaCadenasADN::filtrarSecuenciasLargas(int longitudMinima) {
    // Crear una lista vacía donde guardaremos los resultados
    ListaCadenasADN resultado;
    
    // Recorrer toda la lista original elemento por elemento
    for (IteradorLista it = begin(); it != end(); it.step()) {
        // Obtener la cadena actual del nodo apuntado por el iterador
        CadenaADN cadenaActual = getCadenaADN(it);
        
        // Verificar si esta cadena cumple la condición de longitud mínima
        if (cadenaActual.getLongitud() >= longitudMinima) {
            // Si cumple, insertar una COPIA de la cadena al final de la lista resultado
            resultado.insertarFinal(cadenaActual);
        }
    }
    
    // Devolver la lista con los elementos filtrados
    return resultado;
}

// ===========================================================================
// EJEMPLO 3: Eliminar secuencias duplicadas
// ===========================================================================
// Elimina todas las secuencias duplicadas (misma secuencia de nucleótidos)
// Mantiene solo la primera aparición de cada secuencia única
// Parámetros: Ninguno
// Retorna: Nada (void)
// Notas:
//   - Compara solo secuencias, ignora descripciones
//   - MODIFICA la lista original
//   - Algoritmo: para cada elemento, busca y elimina sus duplicados después de él
//   - CUIDADO: Manejo especial de iteradores al borrar

void ListaCadenasADN::eliminarDuplicados() {
    // Primer bucle: para cada elemento de la lista (it1)
    for (IteradorLista it1 = begin(); it1 != end(); it1.step()) {
        // Guardar la secuencia del elemento actual (it1)
        CadenaADN cadena1 = getCadenaADN(it1);
        
        // Crear segundo iterador que empiece justo después de it1
        IteradorLista it2 = it1;
        it2.step();  // Avanzar una posición para empezar desde el siguiente elemento
        
        // Segundo bucle: buscar duplicados desde it2 hasta el final de la lista
        while (it2 != end()) {
            // Obtener la cadena del elemento actual en el segundo bucle
            CadenaADN cadena2 = getCadenaADN(it2);
            
            // Comparar las secuencias (solo los nucleótidos, no las descripciones)
            if (cadena1.getSecuencia() == cadena2.getSecuencia()) {
                // ¡Encontrado duplicado! Borrar el elemento duplicado (it2)
                borrar(it2);  // Esto pone it2.pt = nullptr
                
                // Después de borrar, it2 queda inválido
                // Reiniciar it2 desde la posición de it1 + 1
                it2 = it1;
                it2.step();
            } else {
                // No es duplicado, avanzar normalmente al siguiente elemento
                it2.step();
            }
        }
    }
}

// ===========================================================================
// EJEMPLO 4: Contar secuencias con alta proporción GC
// ===========================================================================
// Cuenta cuántas secuencias tienen proporción de G+C mayor o igual al mínimo
// Parámetros:
//   - proporcionMinima: valor entre 0.0 y 1.0 (ej: 0.6 = 60% GC)
// Retorna:
//   - Número de secuencias que cumplen la condición
// Notas:
//   - proporción GC = (G + C) / longitud_total
//   - No modifica la lista
//   - Las secuencias ricas en GC son más estables térmicamente

int ListaCadenasADN::contarPorProporcionGC(double proporcionMinima) {
    int contador = 0;  // Inicializar contador a cero
    
    // Recorrer toda la lista
    for (IteradorLista it = begin(); it != end(); it.step()) {
        // Obtener la cadena actual
        CadenaADN cadenaActual = getCadenaADN(it);
        
        // Calcular la proporción GC de esta cadena y comparar con el mínimo
        if (cadenaActual.proporcionGC() >= proporcionMinima) {
            contador++;  // Incrementar contador si cumple la condición
        }
    }
    
    return contador;  // Devolver el total de secuencias que cumplen
}

// ===========================================================================
// EJEMPLO 5: Encontrar posición de una secuencia
// ===========================================================================
// Busca la primera aparición de una secuencia en la lista
// Parámetros:
//   - buscada: CadenaADN con la secuencia a buscar
// Retorna:
//   - Posición (0-based) donde se encuentra, o -1 si no se encuentra
// Notas:
//   - Solo compara las secuencias de nucleótidos
//   - No compara las descripciones
//   - Posición 0 = primer elemento, 1 = segundo, etc.

int ListaCadenasADN::posicionDe(const CadenaADN& buscada) {
    int posicion = 0;  // Empezar contador de posición en 0 (primer elemento)
    
    // Recorrer toda la lista
    for (IteradorLista it = begin(); it != end(); it.step()) {
        // Comparar la secuencia del elemento actual con la secuencia buscada
        if (getCadenaADN(it).getSecuencia() == buscada.getSecuencia()) {
            return posicion;  // ¡Encontrado! Devolver la posición actual
        }
        posicion++;  // No encontrado aquí, incrementar posición para siguiente elemento
    }
    
    return -1;  // Llegamos al final sin encontrar, devolver -1 (no encontrado)
}

// ===========================================================================
// EJEMPLO 6: Invertir la lista (ALGORITMO EFICIENTE)
// ===========================================================================
// Invierte el orden de los elementos modificando solo los punteros
// Parámetros: Ninguno
// Retorna: Nada (void)
// Notas:
//   - NO crea nuevos nodos, NO copia cadenas ADN
//   - Solo modifica los punteros anterior/siguiente de cada nodo
//   - Muy eficiente: O(n) tiempo, O(1) espacio adicional
//   - Algoritmo: intercambiar head/tail, luego para cada nodo intercambiar anterior/siguiente

void ListaCadenasADN::invertir() {
    // Casos especiales donde no hay nada que hacer:
    // - Lista vacía (head == nullptr)
    // - Lista con un solo elemento (head == tail)
    if (esVacia() || head == tail) {
        return;  // No hay nada que invertir
    }
    
    NodoLista* actual = head;  // Empezar desde el primer nodo
    NodoLista* temp = nullptr; // Variable temporal para intercambios
    
    // PASO 1: Intercambiar head y tail
    // El último nodo ahora será el primero, y el primero el último
    head = tail;
    tail = actual;
    
    // PASO 2: Recorrer todos los nodos e intercambiar sus punteros
    while (actual != nullptr) {
        // Guardar el puntero anterior actual antes de modificarlo
        temp = actual->getAnterior();
        
        // Intercambiar los punteros anterior y siguiente
        // El viejo siguiente ahora será el nuevo anterior
        // El viejo anterior ahora será el nuevo siguiente
        actual->setAnterior(actual->getSiguiente());
        actual->setSiguiente(temp);
        
        // Avanzar al siguiente nodo usando el VIEJO siguiente
        // (que ahora está almacenado en anterior después del intercambio)
        actual = actual->getAnterior();
    }
}

// ===========================================================================
// EJEMPLO EXTRA 1: Obtener elemento en posición específica
// ===========================================================================
// Devuelve la cadena ADN en la posición indicada (como si fuera un array)
// Parámetros:
//   - posicion: índice del elemento (0 = primero, 1 = segundo, etc.)
// Retorna:
//   - Cadena ADN en esa posición, o CadenaADN() por defecto si posición inválida
// Notas:
//   - Similar a operator[] pero con verificación de límites
//   - Recorre la lista hasta llegar a la posición deseada

CadenaADN ListaCadenasADN::obtenerEnPosicion(int posicion) {
    // Verificar que la posición está dentro de los límites válidos
    if (posicion < 0 || posicion >= longitud()) {
        return CadenaADN();  // Posición inválida, devolver cadena por defecto
    }
    
    int posActual = 0;  // Contador de posición actual
    
    // Recorrer la lista hasta encontrar la posición deseada
    for (IteradorLista it = begin(); it != end(); it.step()) {
        if (posActual == posicion) {
            // ¡Encontrada la posición! Devolver la cadena en esta posición
            return getCadenaADN(it);
        }
        posActual++;  // No es esta posición, incrementar contador
    }
    
    // En teoría no deberíamos llegar aquí si la posición era válida
    return CadenaADN();  // Por seguridad, devolver cadena por defecto
}

// ===========================================================================
// EJEMPLO EXTRA 2: Insertar en posición específica
// ===========================================================================
// Inserta una cadena en la posición indicada (como insertar en un array)
// Parámetros:
//   - posicion: índice donde insertar (0 = inicio, longitud() = final)
//   - cadena: Cadena ADN a insertar
// Retorna:
//   - true si se insertó correctamente, false si posición inválida
// Notas:
//   - Posiciones válidas: desde 0 hasta longitud() (inclusive)
//   - Si posición = longitud(), equivale a insertarFinal()

bool ListaCadenasADN::insertarEnPosicion(int posicion, const CadenaADN& cadena) {
    // Caso especial: insertar al inicio (posición 0)
    if (posicion == 0) {
        insertarInicio(cadena);
        return true;
    }
    
    // Caso especial: insertar al final (posición = longitud actual)
    if (posicion == longitud()) {
        insertarFinal(cadena);
        return true;
    }
    
    // Caso general: insertar en medio
    // Buscar la posición en la lista
    int posActual = 0;
    for (IteradorLista it = begin(); it != end(); it.step()) {
        if (posActual == posicion) {
            // Encontrada la posición, insertar ANTES de este elemento
            return insertar(it, cadena);
        }
        posActual++;
    }
    
    // Si llegamos aquí, la posición era inválida
    return false;
}

// ===========================================================================
// CÓMO AÑADIR ESTOS MÉTODOS A TU CÓDIGO:
// ===========================================================================
// 
// PASO 1: En ListaCadenasADN.h, añadir en la sección pública:
//
//   CadenaADN* buscarPorDescripcion(const string& descripcionBuscada);
//   ListaCadenasADN filtrarSecuenciasLargas(int longitudMinima);
//   void eliminarDuplicados();
//   int contarPorProporcionGC(double proporcionMinima);
//   int posicionDe(const CadenaADN& buscada);
//   void invertir();
//   CadenaADN obtenerEnPosicion(int posicion);
//   bool insertarEnPosicion(int posicion, const CadenaADN& cadena);
//
// PASO 2: En ListaCadenasADN.cc, copiar las implementaciones anteriores
//         (quitar los comentarios de cada función)
//
// PASO 3: Compilar y probar:
//   g++ -g -std=c++11 -Wall -o Ejemplo CadenaADN.cc ListaCadenasADN.cc Ejemplo.cc
//   ./Ejemplo
//
// ===========================================================================
*/

