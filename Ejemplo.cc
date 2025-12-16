#include <iostream>
#include <vector>
#include <string>
#include "CadenaADN.h"
#include "ListaCadenasADN.h"
using namespace std;

/* ========= Clase auxiliar para pruebas ========= */
class TestSuite {
    int total = 0;
    int passed = 0;

    // Formatea un vector<string> en "[elem1, elem2, ...]"
    static string vectorToStr(const vector<string> &v) {
        string s = "[";
        for (size_t i = 0; i < v.size(); i++) {
            s += v[i];
            if (i + 1 < v.size()) s += ", ";
        }
        s += "]";
        return s;
    }

public:
    // Prueba genérica con condición booleana
    void check(bool condition, const string &desc) {
        total++;
        if (condition) {
            passed++;
            cout << "OK " << desc << endl;
        } else {
            cout << "ERROR " << desc << endl;
        }
    }

    // Prueba de igualdad entre dos valores escalares
    template <typename T>
    void expectEqual(const T &obtained, const T &expected, const string &desc) {
        total++;
        if (obtained == expected) {
            passed++;
            cout << "OK " << desc << endl;
        } else {
            cout << "ERROR " << desc << endl;
            cout << "   ├─ Obtenido: " << obtained << endl;
            cout << "   └─ Esperado: " << expected << endl;
        }
    }

    // Prueba de igualdad entre dos vectores<string>
    void expectEqualVec(const vector<string> &obt, const vector<string> &exp, const string &desc) {
        total++;
        if (obt == exp) {
            passed++;
            cout << "OK " << desc << endl;
        } else {
            cout << "ERROR " << desc << endl;
            cout << "   ├─ Obtenido: " << vectorToStr(obt) << endl;
            cout << "   └─ Esperado: " << vectorToStr(exp) << endl;
        }
    }

    // Resumen final
    void summary() const {
        cout << "\n=== RESULTADO FINAL: " << passed << "/" << total
             << " pruebas superadas (" << (100.0 * passed / total) << "%) ===" << endl;
    }
};

/* ========= Funciones auxiliares ========= */

// Devuelve las secuencias de una lista en orden
vector<string> obtenerSecuencias(const ListaCadenasADN &lista) {
    vector<string> v;
    for (IteradorLista it = lista.begin(); it != lista.end(); it.step())
        v.push_back(lista.getCadenaADN(it).getSecuencia());
    return v;
}

// Devuelve las secuencias de una lista en orden inverso
vector<string> obtenerSecuenciasInversa(const ListaCadenasADN &lista) {
    vector<string> v;
    for (IteradorLista it = lista.rbegin(); it != lista.rend(); it.rstep())
        v.push_back(lista.getCadenaADN(it).getSecuencia());
    return v;
}

/* ========= Programa principal ========= */
int main() {
    TestSuite test;
    cout << "=== PRUEBAS DE ListaCadenasADN ===" << endl;

    // --- Crear cadenas base ---
    CadenaADN c1("ATG", "Inicio");
    CadenaADN c2("GATATC", "EcoRV");
    CadenaADN c3("AGTCAA", "Otra cadena");
    CadenaADN c4("GATGAT", "Cadena1");
    CadenaADN c4bis("GATGAT", "Otra descripción");
    CadenaADN c5("TTGCAA", "Final");

    // --- Lista vacía ---
    ListaCadenasADN lista;
    test.check(lista.esVacia(), "Lista vacía inicial");
    test.expectEqual(lista.longitud(), 0, "Longitud inicial = 0");

    // --- Inserciones al inicio y final ---
    lista.insertarInicio(c1); // [ATG]
    lista.insertarFinal(c2);  // [ATG, GATATC]
    lista.insertarFinal(c3);  // [ATG, GATATC, AGTCAA]
    lista.insertarInicio(c5); // [ TTGCAA, ATG, GATATC, AGTCAA]
    test.expectEqual(lista.longitud(), 4, "Longitud tras 4 inserciones");
    test.expectEqualVec(obtenerSecuencias(lista), {"TTGCAA", "ATG", "GATATC", "AGTCAA"  }, "Orden correcto tras inserciones");
    test.expectEqualVec(obtenerSecuenciasInversa(lista), {  "AGTCAA" , "GATATC" ,  "ATG", "TTGCAA" }, "Orden inverso correcto tras inserciones");

    // --- Copia y operador de asignación ---
    ListaCadenasADN copia(lista);
    ListaCadenasADN asignada;
    asignada = lista;
    test.expectEqualVec(obtenerSecuencias(copia), obtenerSecuencias(lista), "Constructor de copia correcto");
    test.expectEqualVec(obtenerSecuencias(asignada), obtenerSecuencias(lista), "Operador de asignación correcto");

    lista.insertarFinal(c4);
    test.check(obtenerSecuencias(lista) != obtenerSecuencias(copia), "Copia independiente del original");

    // --- Asignar en posición ---
    IteradorLista it = copia.begin();
    copia.asignar(it, c4); // reemplaza el primero
    test.expectEqualVec(obtenerSecuencias(copia), {"GATGAT", "ATG", "GATATC", "AGTCAA"}, "asignar() modifica nodo correcto");

    // --- BorrarPrimera y BorrarUltima ---
    copia.borrarPrimera();
    copia.borrarUltima();
    test.expectEqualVec(obtenerSecuencias(copia), {"ATG", "GATATC"}, "Borrado de extremos correcto");

    ListaCadenasADN vacia;
    test.check(! vacia.borrarPrimera(), "BorrarPrimera de lista vacía correcto" );
    test.check(! vacia.borrarUltima(), "BorrarUltima de lista vacía correcto" );

    // --- Insertar en posición intermedia ---
    ListaCadenasADN lista2;
    lista2.insertarFinal(c1); // [ATG]
    lista2.insertarFinal(c2); // [ATG, GATATC]
    lista2.insertarFinal(c3); // [ATG, GATATC, AGTCAA]
    IteradorLista itpos = lista2.begin();
    itpos.step(); // posición intermedia
    lista2.insertar(itpos, c4); // [ATG, GATGAT, GATATC, AGTCAA]
    test.expectEqualVec(obtenerSecuencias(lista2), {"ATG", "GATGAT", "GATATC", "AGTCAA"}, "Inserción intermedia correcta");
    test.expectEqualVec(obtenerSecuenciasInversa(lista2), { "AGTCAA", "GATATC","GATGAT",  "ATG"}, "Inserción intermedia correcta (orden inverso)");

    // --- Contar() ---
    test.expectEqual(lista2.contar(c4), 1, "Contar() encuentra 1 coincidencia");
    lista2.insertarFinal(c4);
    test.expectEqual(lista2.contar(c4), 2, "Contar() encuentra 2 coincidencias tras duplicar");

    test.expectEqual(lista2.contar(c4bis), 2, "Contar() encuentra 2 coincidencias con distina descripción");

    // --- diferencia() ---
    ListaCadenasADN lista3;
    lista3.insertarInicio(c3);
    lista3.insertarInicio(c2); // [GATATC, AGTCAA]
    ListaCadenasADN dif = lista2.diferencia(lista3);
    test.expectEqualVec(obtenerSecuencias(dif), {"ATG", "GATGAT", "GATGAT"}, "diferencia() devuelve elementos esperados");
    test.expectEqualVec(obtenerSecuencias(dif), {"ATG", "GATGAT", "GATGAT"}, "diferencia() devuelve elementos esperados (orden inverso)");

    // --- concatenar(Lista) ---
    ListaCadenasADN concat = lista2.concatenar(lista3);
    test.expectEqualVec(obtenerSecuencias(concat),
                        {"ATG", "GATGAT", "GATATC", "AGTCAA", "GATGAT", "GATATC", "AGTCAA"},
                        "concatenar(Lista) mantiene orden");
    test.expectEqualVec(obtenerSecuenciasInversa(concat),
                        {"AGTCAA", "GATATC", "GATGAT", "AGTCAA","GATATC", "GATGAT", "ATG"},
                        "concatenar(Lista) mantiene orden inverso");

    // --- concatenar() genera CadenaADN con secuencia total ---
    CadenaADN total = lista2.concatenar();
    string esperado = "ATGGATGATGATATCAGTCAAGATGAT";
    test.expectEqual(total.getSecuencia(), esperado, "concatenar() crea secuencia completa correcta");

    // ---  borrar(Iterador) ---
    IteradorLista itb = lista2.begin();
    itb.step(); // GATGAT
    lista2.borrar(itb);
    test.expectEqual(lista2.contar(c4), 1, "borrar(Iterador) elimina un nodo");
    test.expectEqualVec(obtenerSecuencias(lista2), {"ATG", "GATATC", "AGTCAA", "GATGAT"}, "borrar (Iterador): resultado correcto");
    test.expectEqualVec(obtenerSecuenciasInversa(lista2), { "GATGAT", "AGTCAA", "GATATC", "ATG"}, "borrar (Iterador): resultado correcto (orden inverso)");


    // --- aCadena() ---
    ListaCadenasADN lista4;
    lista4.insertarFinal(c1);
    lista4.insertarFinal(c2);
    string salida = lista4.aCadena();
    test.check(salida=="Inicio:ATG\nEcoRV:GATATC", "aCadena devuelve la salida correcta");

    ListaCadenasADN lista5;
    salida = lista5.aCadena();
    test.check(salida=="", "aCadena devuelve la salida correcta para lista vacía");

    // --- Vaciar---
    while (!lista2.esVacia()) lista2.borrarPrimera();
    test.expectEqual(lista2.longitud(), 0, "Borrado completo de lista correcto");

    // --- Resultado global ---
    test.summary();
    return 0;
}

