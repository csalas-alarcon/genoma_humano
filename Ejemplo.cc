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
    void check(bool condition, const string &desc) {
        total++;
        if (condition) {
            passed++;
            cout << "OK " << desc << endl;
        } else {
            cout << "ERROR " << desc << endl;
        }
    }

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

    void summary() const {
        cout << "\n=== RESULTADO FINAL: " << passed << "/" << total
             << " pruebas superadas (" << (100.0 * passed / total) << "%) ===" << endl;
    }
};

/* ========= Funciones auxiliares ========= */

vector<string> obtenerSecuencias(ListaCadenasADN &lista) {
    vector<string> v;
    for (IteradorLista it = lista.begin(); it != lista.end(); it.step())
        v.push_back(lista.getCadenaADN(it).getSecuencia());
    return v;
}

vector<string> obtenerSecuenciasInversa(ListaCadenasADN &lista) {
    vector<string> v;
    for (IteradorLista it = lista.rbegin(); it != lista.rend(); it.rstep())
        v.push_back(lista.getCadenaADN(it).getSecuencia());
    return v;
}

/* ========= Programa principal ========= */
int main() {
    TestSuite test;
    cout << "=== PRUEBAS DE ListaCadenasADN ===" << endl;

    CadenaADN c1("ATG", "Inicio");
    CadenaADN c2("GATATC", "EcoRV");
    CadenaADN c3("AGTCAA", "Otra cadena");
    CadenaADN c4("GATGAT", "Cadena1");
    CadenaADN c4bis("GATGAT", "Otra descripción");
    CadenaADN c5("TTGCAA", "Final");

    ListaCadenasADN lista;
    test.check(lista.esVacia(), "Lista vacía inicial");
    test.expectEqual(lista.longitud(), 0, "Longitud inicial = 0");

    lista.insertarInicio(c1); 
    lista.insertarFinal(c2);  
    lista.insertarFinal(c3);  
    lista.insertarInicio(c5); 
    test.expectEqual(lista.longitud(), 4, "Longitud tras 4 inserciones");
    test.expectEqualVec(obtenerSecuencias(lista), {"TTGCAA", "ATG", "GATATC", "AGTCAA"  }, "Orden correcto tras inserciones");
    test.expectEqualVec(obtenerSecuenciasInversa(lista), {  "AGTCAA" , "GATATC" ,  "ATG", "TTGCAA" }, "Orden inverso correcto tras inserciones");

    ListaCadenasADN copia(lista);
    ListaCadenasADN asignada;
    asignada = lista;
    test.expectEqualVec(obtenerSecuencias(copia), obtenerSecuencias(lista), "Constructor de copia correcto");
    test.expectEqualVec(obtenerSecuencias(asignada), obtenerSecuencias(lista), "Operador de asignación correcto");

    lista.insertarFinal(c4);
    test.check(obtenerSecuencias(lista) != obtenerSecuencias(copia), "Copia independiente del original");

    IteradorLista it = copia.begin();
    copia.asignar(it, c4); 
    test.expectEqualVec(obtenerSecuencias(copia), {"GATGAT", "ATG", "GATATC", "AGTCAA"}, "asignar() modifica nodo correcto");

    copia.borrarPrimera();
    copia.borrarUltima();
    test.expectEqualVec(obtenerSecuencias(copia), {"ATG", "GATATC"}, "Borrado de extremos correcto");

    ListaCadenasADN vacia;
    test.check(! vacia.borrarPrimera(), "BorrarPrimera de lista vacía correcto" );
    test.check(! vacia.borrarUltima(), "BorrarUltima de lista vacía correcto" );

    ListaCadenasADN lista2;
    lista2.insertarFinal(c1); 
    lista2.insertarFinal(c2); 
    lista2.insertarFinal(c3); 
    IteradorLista itpos = lista2.begin();
    itpos.step(); 
    lista2.insertar(itpos, c4); 
    test.expectEqualVec(obtenerSecuencias(lista2), {"ATG", "GATGAT", "GATATC", "AGTCAA"}, "Inserción intermedia correcta");
    test.expectEqualVec(obtenerSecuenciasInversa(lista2), { "AGTCAA", "GATATC","GATGAT",  "ATG"}, "Inserción intermedia correcta (orden inverso)");

    test.expectEqual(lista2.contar(c4), 1, "Contar() encuentra 1 coincidencia");
    lista2.insertarFinal(c4);
    test.expectEqual(lista2.contar(c4), 2, "Contar() encuentra 2 coincidencias tras duplicar");
    test.expectEqual(lista2.contar(c4bis), 2, "Contar() encuentra 2 coincidencias con distina descripción");

    ListaCadenasADN lista3;
    lista3.insertarInicio(c3);
    lista3.insertarInicio(c2); 
    ListaCadenasADN dif = lista2.diferencia(lista3);
    test.expectEqualVec(obtenerSecuencias(dif), {"ATG", "GATGAT", "GATGAT"}, "diferencia() devuelve elementos esperados");

    ListaCadenasADN concat;
    concat = lista2.concatenar(lista3);
    test.expectEqualVec(obtenerSecuencias(concat),
                        {"ATG", "GATGAT", "GATATC", "AGTCAA", "GATGAT", "GATATC", "AGTCAA"},
                        "concatenar(Lista) mantiene orden");

    CadenaADN total = lista2.concatenar();
    string esperado = "ATGGATGATGATATCAGTCAAGATGAT";
    test.expectEqual(total.getSecuencia(), esperado, "concatenar() crea secuencia completa correcta");

    IteradorLista itb = lista2.begin();
    itb.step(); 
    lista2.borrar(itb);
    test.expectEqual(lista2.contar(c4), 1, "borrar(Iterador) elimina un nodo");
    test.expectEqualVec(obtenerSecuencias(lista2), {"ATG", "GATATC", "AGTCAA", "GATGAT"}, "borrar (Iterador): resultado correcto");

    ListaCadenasADN lista4;
    lista4.insertarFinal(c1);
    lista4.insertarFinal(c2);
    string salida = lista4.aCadena();
    test.check(salida=="Inicio:ATG\nEcoRV:GATATC", "aCadena devuelve la salida correcta");

    ListaCadenasADN lista5;
    salida = lista5.aCadena();
    test.check(salida=="", "aCadena devuelve la salida correcta para lista vacía");

    while (!lista2.esVacia()) lista2.borrarPrimera();
    test.expectEqual(lista2.longitud(), 0, "Borrado completo de lista correcto");

    /* PRUEBAS COMPLETADAS POR EL ALUMNADO  */

    // --- InsertarDespues en posición intermedia ---
    ListaCadenasADN lista10;
    lista10.insertarFinal(c1);
    lista10.insertarFinal(c2);
    lista10.insertarFinal(c3);
    
    IteradorLista it10 = lista10.begin();
    it10.step(); // apunta a GATATC [cite: 167, 208]

    lista10.insertarDespues(it10, c4); // Inserta GATGAT después de GATATC [cite: 119]

    test.expectEqualVec(obtenerSecuencias(lista10), {"ATG", "GATATC", "GATGAT", "AGTCAA"}, "Inserción intermedia (después) correcta");
    test.expectEqualVec(obtenerSecuenciasInversa(lista10), { "AGTCAA", "GATGAT", "GATATC", "ATG"}, "Inserción intermedia (después) correcta (orden inverso)");

    // --- InsertarDespues en posición final ---
    ListaCadenasADN lista11;
    lista11.insertarFinal(c1);
    lista11.insertarFinal(c2);
    lista11.insertarFinal(c3);
    
    IteradorLista it11 = lista11.rbegin(); // apunta al último: AGTCAA [cite: 79, 240]
    
    lista11.insertarDespues(it11, c4);

    test.expectEqualVec(obtenerSecuencias(lista11), {"ATG", "GATATC", "AGTCAA", "GATGAT"}, "Inserción intermedia (después) correcta");
    test.expectEqualVec(obtenerSecuenciasInversa(lista11), { "GATGAT", "AGTCAA", "GATATC", "ATG"}, "Inserción intermedia (después) correcta (orden inverso)");

    // --- Cuentas de codones y cadenas ---
    CadenaADN cc1("ATG", "Cadena 1");
    CadenaADN cc2("GATATCATC", "Cadena 2");
    CadenaADN cc3("GCATCG", "Borrar 1");
    CadenaADN cc4("GCATCG", "Cadena 3");
    CadenaADN cc5("CCTAGAATC", "Cadena 4");
    CadenaADN cc6("GCATCG", "Otra cadena");
    CadenaADN cc7("CCCATC", "Borrar 2");

    ListaCadenasADN lista12;
    lista12.insertarFinal(cc1);
    lista12.insertarFinal(cc2);
    lista12.insertarFinal(cc3);
    lista12.insertarFinal(cc4);
    lista12.insertarFinal(cc5);
    lista12.insertarFinal(cc6);
    lista12.insertarFinal(cc7);

    IteradorLista it12 = lista12.begin();
    it12.step(); it12.step(); // apunta a cc3
    lista12.borrar(it12); // Borra cc3 [cite: 102]

    it12 = lista12.rbegin(); // apunta a cc7
    lista12.borrar(it12); // Borra cc7

    test.expectEqualVec(obtenerSecuencias(lista12), {"ATG", "GATATCATC", "GCATCG", "CCTAGAATC", "GCATCG"}, "Inserción y borrado pre probar cuentas correcta");
    test.expectEqualVec(obtenerSecuenciasInversa(lista12), {"GCATCG", "CCTAGAATC", "GCATCG", "GATATCATC",  "ATG" }, "Inserción y borrado pre probar cuentas (orden inverso)");

    test.expectEqual( lista12.frecuenciaCodon("ATC"), 3, "frecuenciaCodon"); // Frecuencia total del codón [cite: 121, 163]
    test.expectEqual( lista12.frecuenciaCadena(cc3), 2, "frecuenciaCadena"); // Frecuencia de la secuencia [cite: 123, 171]

    test.expectEqual(lista12.listaCodones(),string("AGA\nATC\nATG\nCCT\nGAT\nGCA\nTCG"),"listaCodones"); // Listado ordenado alfabéticamente [cite: 125, 173]
    test.expectEqual(lista12.listaCadenasADN(),string("ATG\nCCTAGAATC\nGATATCATC\nGCATCG"),"listaCadenasADN"); // Secuencias únicas ordenadas [cite: 129, 185]

    test.expectEqual(lista12.listaCadenasConCodon("ATC"),string("CCTAGAATC\nGATATCATC"),"listaCadenasConCodon"); // Filtrado por codón [cite: 131, 192]

    // --- eliminaDuplicados ---
    lista12.eliminaDuplicados(); // Elimina duplicados manteniendo la primera instancia [cite: 133, 197]
    test.expectEqualVec(obtenerSecuencias(lista12), {"ATG", "GATATCATC", "GCATCG", "CCTAGAATC"}, "eliminaDuplicados");
    test.expectEqualVec(obtenerSecuenciasInversa(lista12), {"CCTAGAATC", "GCATCG", "GATATCATC",  "ATG" }, "eliminaDuplicados (orden inverso)");

    test.summary();
    return 0;
}