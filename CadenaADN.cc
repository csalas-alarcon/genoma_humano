#include "CadenaADN.h"
#include <vector> // Necesario para obtenerCodones()
#include <sstream>
#include <algorithm>
using namespace std;

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
// NOTA: Esta función cuenta ocurrencias SOLAPADAS o NO SOLAPADAS 
// dependiendo de cómo se utilice. Aquí se implementa de manera simple (posible solapamiento).
int CadenaADN::contador(const string &serie) const {
    int contador = 0;
    int longitud_serie = serie.length();

    for (int i = 0; i < secuencia.length(); i++) {
        // Asegura que hay suficiente espacio para la subserie
        if ((i + longitud_serie) <= secuencia.length()) { 
             if (secuencia.substr(i, longitud_serie) == serie) { 
                contador++; 
             }
        }
    }
    return contador;
}

// =============================================
// CONSTRUCTORES Y DESTRUCTOR
// =============================================

// Constructor por defecto
CadenaADN::CadenaADN() : secuencia("ATG"), descripcion("") {}

// Constructor con parámetros
CadenaADN::CadenaADN(const string &isec, const string &idesc) {
    if (validador(isec, idesc)) {
        secuencia = isec; 
        descripcion = idesc;
    } else {
        secuencia = "ATG"; // Valor por defecto si no es válido
        descripcion = "";
    }
}

// Constructor de copia
CadenaADN::CadenaADN(const CadenaADN &molecula) 
    : secuencia(molecula.secuencia), descripcion(molecula.descripcion) {}

// Destructor
CadenaADN::~CadenaADN() {}

// Operador de asignación
CadenaADN& CadenaADN::operator=(const CadenaADN &molecula) {
    if (this != &molecula) {
        secuencia = molecula.secuencia; 
        descripcion = molecula.descripcion;
    }
    return (*this);
}

// =============================================
// OPERADORES DE COMPARACIÓN
// =============================================

// Operador de igualdad - compara secuencia Y descripción (Seguimos la implementación que me diste)
// NOTA: Para ListaCadenasADN::contar y diferencia, SOLO se usa la secuencia.
bool CadenaADN::operator==(const CadenaADN &molecula) const { 
    return (secuencia == molecula.secuencia && descripcion == molecula.descripcion);
}

// Operador de desigualdad
bool CadenaADN::operator!=(const CadenaADN &molecula) const { 
    return !(*this == molecula);
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
    // Usamos "" como descripción temporal para validar solo la secuencia
    if (validador(isec, "")) { 
        secuencia = isec; 
    }
}

void CadenaADN::setDescripcion(const string &idesc) { 
    // Usamos secuencia actual para validar solo la descripción
    if (validador(secuencia, idesc)) { 
        descripcion = idesc; 
    }
}

// =============================================
// CONTEO DE NUCLEÓTIDOS
// =============================================

int CadenaADN::cuentaA() const { return contador("A"); }
int CadenaADN::cuentaT() const { return contador("T"); }
int CadenaADN::cuentaC() const { return contador("C"); }
int CadenaADN::cuentaG() const { return contador("G"); }

// Verifica si cumple las proporciones de Chargaff
bool CadenaADN::cumpleChargaff() const {
    int numA = cuentaA();
    int numT = cuentaT();
    int numC = cuentaC();
    int numG = cuentaG();
    
    // Simplificación de la regla de Chargaff: A=T y C=G
    return (numA == numT) && (numC == numG);
}

// Calcula la proporción de G y C en la secuencia
double CadenaADN::proporcionGC() const {
    int cuentaGC = cuentaC() + cuentaG();
    int total = secuencia.length();
    if (total == 0) return 0.0;
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

// NUEVO: Método para obtener todos los codones de la secuencia (sin solapamiento)
vector<string> CadenaADN::obtenerCodones() const {
    vector<string> codones;
    const int longitud_codon = 3;
    
    // Recorrer la secuencia saltando de 3 en 3 (sin solapamiento)
    for (int i = 0; (i + longitud_codon) <= secuencia.length(); i += longitud_codon) {
        codones.push_back(secuencia.substr(i, longitud_codon));
    }
    
    return codones;
}


// =============================================
// BÚSQUEDA DE SUBSECUENCIAS
// =============================================

// Busca la primera aparición de una subsecuencia
int CadenaADN::buscarSubsecuencia(const string &serie) const { 
    // Usamos el método find de std::string para mayor eficiencia
    size_t pos = secuencia.find(serie);
    if (pos == string::npos) {
        return -1;
    }
    return (int)pos;
}

// Busca la última aparición de una subsecuencia
int CadenaADN::posicionUltimaAparicion(const string &serie) const {
    // Usamos el método rfind de std::string
    size_t pos = secuencia.rfind(serie);
    if (pos == string::npos) {
        return -1;
    }
    return (int)pos;
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
            maxima = max(maxima, actual);
            actual = 0;
        }
    }
    
    return max(maxima, actual); // Verificar la última secuencia
}

// Encuentra la longitud máxima de cualquier nucleótido consecutivo
int CadenaADN::longitudMaximaConsecutivaCualquiera() const {
    int maximo = 0;
    maximo = max(maximo, longitudMaximaConsecutiva('A'));
    maximo = max(maximo, longitudMaximaConsecutiva('T'));
    maximo = max(maximo, longitudMaximaConsecutiva('C'));
    maximo = max(maximo, longitudMaximaConsecutiva('G'));
    
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
    if (secuencia.length() != molecula.secuencia.length()) { 
        return false; 
    }
    
    for (int i = 0; i < secuencia.length(); i++) {
        char n1 = secuencia[i];
        char n2 = molecula.secuencia[i];
        
        if (!((n1 == 'A' && n2 == 'T') || (n1 == 'T' && n2 == 'A') ||
              (n1 == 'C' && n2 == 'G') || (n1 == 'G' && n2 == 'C'))) {
            return false;
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
            case 'A': secuencia[i] = 'T'; break;
            case 'T': secuencia[i] = 'A'; break;
            case 'C': secuencia[i] = 'G'; break;
            case 'G': secuencia[i] = 'C'; break;
        }
    }
    // Opcional: invertir el orden de los nucleótidos también (no especificado, pero típico en inversión)
    reverse(secuencia.begin(), secuencia.end());
}

// =============================================
// ALMACENAJE Y LECTURA DE FICHEROS
// =============================================

// Guarda la cadena ADN en un fichero
bool CadenaADN::guardarEnFichero(const string &path) const {
    ofstream fichero(path);
    if (fichero.is_open()) {
        fichero << descripcion << "\n";
        fichero << secuencia; // No se añade salto de línea al final según el formato típico de archivos
        fichero.close();
        return true;
    }
    return false;
}

// Carga la cadena ADN desde un fichero
bool CadenaADN::cargarDesdeFichero(const string &path) {
    ifstream fichero(path);
    if (fichero.is_open()) {
        string linea_descripcion, linea_secuencia;
        
        if (getline(fichero, linea_descripcion) && getline(fichero, linea_secuencia)) {
            // Validar la secuencia cargada
            if (validador(linea_secuencia, linea_descripcion)) {
                descripcion = linea_descripcion;
                secuencia = linea_secuencia;
                fichero.close();
                return true;
            }
        }
        fichero.close();
    }
    return false;
}