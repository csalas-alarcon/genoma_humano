#include "CadenaADN.h"
#include <string>
#include <list>          // Para el contenedor principal (similar a lista enlazada)
#include <map>           // Para listados ordenados y eficientes (listaCodones, etc.)
#include <unordered_map> // Para frecuencias de tiempo constante

using namespace std;

// Declaración forward de ListaCadenasADN
class ListaCadenasADN;

/**
 * @brief Clase IteradorLista. Simula el iterador de STL para recorrer ListaCadenasADN.
 * Se ha modificado para usar un iterador del contenedor STL elegido (std::list<CadenaADN>::iterator).
 */
class IteradorLista {
    friend class ListaCadenasADN;

   private:
    // Atributo interno que guarda el iterador STL. Se asume que ListaCadenasADN usa std::list.
    // Si se usara std::vector, este tipo cambiaría a std::vector<CadenaADN>::iterator.
    list<CadenaADN>::iterator iter;
    // Puntero al contenedor principal, necesario para métodos como rbegin/rend y step/rstep si es bidireccional.
    // Lo simplificaremos asumiendo la estructura propuesta en el enunciado.
    
    // NOTA: Para simplificar, la implementación de step/rstep y begin/end/rbegin/rend
    // debe usar las propiedades del iterador STL (que es bidireccional para list).

   public:
    // Constructor por defecto: inicializa el iterador a un estado "vacío" o por defecto.
    IteradorLista();
    // Constructor de copia
    IteradorLista(const IteradorLista&);
    // Destructor
    ~IteradorLista();
    // Operador de asignación
    IteradorLista& operator=(const IteradorLista&);
    // Avanza una posición en la lista (it.step())
    void step();
    // Retrocede una posición en la lista (it.rstep())
    void rstep();
    // Operador de comparación
    bool operator==(const IteradorLista&) const;
    // Operador de comparación
    bool operator!=(const IteradorLista&) const;
    // NUEVO: comprueba si el iterador ha sido creado con su constructor por defecto
    bool esVacio() const;
};


/**
 * @brief Clase ListaCadenasADN. Utiliza tipos de datos avanzados de STL
 * para una implementación eficiente.
 */
class ListaCadenasADN{
private:
    // 1. Contenedor principal STL (Requisito: usar un tipo STL)
    list<CadenaADN> data;
    
    // 2. Atributos auxiliares STL para O(1) en frecuenciaCodon/frecuenciaCadena (Requisito: múltiples atributos privados STL)

    // Mapa para O(1) en frecuenciaCadena: (Secuencia_ADN, Frecuencia)
    // Usamos unordered_map ya que la clave (secuencia) es un string y el orden no importa para la frecuencia.
    unordered_map<string, int> frecuencia_secuencias;

    // Mapa para O(1) en frecuenciaCodon: (Codón, Frecuencia)
    unordered_map<string, int> frecuencia_codones;

    // 3. Atributos auxiliares STL para listados rápidos O(1) (Requisito: tiempo independiente de la longitud)

    // Set o Map para listaCodones(): (Codón, bool o int) - para almacenar codones sin duplicados y ordenados.
    // Usamos map para mantener el orden alfabético automáticamente (std::map lo hace) y para que listaCodones() sea rápido.
    map<string, bool> codones_unicos_ordenados;

    // Map para listaCadenasConCodon(): (Codón, Set_de_Secuencias_Unicas_y_Ordenadas)
    // Almacena qué cadenas contienen cada codón. Esto permite que listaCadenasConCodon() sea O(1) respecto a la longitud de 'data'.
    map<string, map<string, bool>> cadenas_por_codon;

    void actualizarEstructurasAlInsertar(const CadenaADN& cadena);
    void actualizarEstructurasAlBorrar(const CadenaADN& cadena);

public:
    // Constructor por defecto: lista vacía
    ListaCadenasADN();
    // Constructor de copia
    ListaCadenasADN(const ListaCadenasADN&);
    // Operador de asignación
    ListaCadenasADN& operator=(const ListaCadenasADN &);
    // Destructor
    ~ListaCadenasADN();
    
    // Métodos que devuelven iteradores (usando el iterador STL subyacente)
    IteradorLista begin();
    IteradorLista end();
    IteradorLista rbegin();
    IteradorLista rend();
    
    // Métodos básicos y de gestión (conservan la firma)
    CadenaADN getCadenaADN(IteradorLista);
    bool esVacia();
    void insertarInicio(const CadenaADN&);
    void insertarFinal(const CadenaADN&);
    bool insertar( IteradorLista, const CadenaADN&);
    // NUEVO: Inserta después de la posición apuntada por el iterador
    bool insertarDespues (IteradorLista, const CadenaADN&);
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
    
    /* MÉTODOS NUEVOS DE LA PRÁCTICA 3 */
    
    // Devuelve la frecuencia del codón pasado como parámetro (O(1))
    int frecuenciaCodon (const string &);
    // Devuelve la frecuencia de la secuencia de ADN pasada como parámetro (O(1))
    int frecuenciaCadena (const CadenaADN&);
    // Lista los codones en orden alfabético (Tiempo independiente de la longitud de la lista principal)
    string listaCodones();
    // Lista las cadenas en orden alfabético (Tiempo independiente de la longitud de la lista principal)
    string listaCadenasADN();
    // Lista las cadenas que contienen un codón determinado, sin repetidos (Tiempo independiente de la longitud de la lista principal)
    string listaCadenasConCodon (const string& );
    // Elimina las cadenas de ADN con la misma secuencia, dejando sólo la primera
    void eliminaDuplicados();
};