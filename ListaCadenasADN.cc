#include "ListaCadenasADN.h"
#include <sstream>
#include <algorithm>
#include <unordered_set>

IteradorLista::IteradorLista() : vacio(true) {}
IteradorLista::IteradorLista(const IteradorLista& other) : iter(other.iter), vacio(other.vacio) {}
IteradorLista::~IteradorLista() {}
IteradorLista& IteradorLista::operator=(const IteradorLista& other) {
    if (this != &other) { iter = other.iter; vacio = other.vacio; }
    return *this;
}
void IteradorLista::step() { if (!vacio) ++iter; }
void IteradorLista::rstep() { if (!vacio) --iter; }
bool IteradorLista::operator==(const IteradorLista& other) const {
    if (vacio && other.vacio) return true;
    if (vacio || other.vacio) return false;
    return iter == other.iter;
}
bool IteradorLista::operator!=(const IteradorLista& other) const { return !(*this == other); }
bool IteradorLista::esVacio() const { return vacio; }

// --- ListaCadenasADN ---
ListaCadenasADN::ListaCadenasADN() {}
ListaCadenasADN::ListaCadenasADN(const ListaCadenasADN& other) { *this = other; }
ListaCadenasADN& ListaCadenasADN::operator=(const ListaCadenasADN& other) {
    if (this != &other) {
        data = other.data;
        frecSecuencias = other.frecSecuencias;
        frecCodones = other.frecCodones;
        codonesUnicos = other.codonesUnicos;
        mapaCodonSecuencias = other.mapaCodonSecuencias;
    }
    return *this;
}
ListaCadenasADN::~ListaCadenasADN() {}

void ListaCadenasADN::actualizarEstructuras(const CadenaADN& cadena, int inc) {
    string seq = cadena.getSecuencia();
    frecSecuencias[seq] += inc;
    if (frecSecuencias[seq] <= 0) frecSecuencias.erase(seq);

    vector<string> cods = cadena.obtenerCodones();
    for (const string& c : cods) {
        frecCodones[c] += inc;
        
        if (inc > 0) {
            codonesUnicos[c] = true;
            mapaCodonSecuencias[c][seq] = true;
        } else {
            // Si estamos borrando (inc < 0)
            if (frecCodones[c] <= 0) {
                frecCodones.erase(c);
                codonesUnicos.erase(c);
                mapaCodonSecuencias.erase(c);
            } else {
                // Si el codón aún existe en otras cadenas, 
                // pero queremos ver si esta secuencia específica ya no lo tiene
                if (frecSecuencias[seq] <= 0) {
                    mapaCodonSecuencias[c].erase(seq);
                }
            }
        }
    }
}

IteradorLista ListaCadenasADN::begin() { IteradorLista it; it.iter = data.begin(); it.vacio = false; return it; }
IteradorLista ListaCadenasADN::end() { IteradorLista it; it.iter = data.end(); it.vacio = false; return it; }
IteradorLista ListaCadenasADN::rbegin() { IteradorLista it; if (data.empty()) it = end(); else { it.iter = --data.end(); it.vacio = false; } return it; }
IteradorLista ListaCadenasADN::rend() { IteradorLista it; it.iter = --data.begin(); it.vacio = false; return it; }

CadenaADN ListaCadenasADN::getCadenaADN(IteradorLista it) { return (it.esVacio() || it.iter == data.end()) ? CadenaADN() : *it.iter; }
bool ListaCadenasADN::esVacia() { return data.empty(); }
void ListaCadenasADN::insertarInicio(const CadenaADN& c) { data.push_front(c); actualizarEstructuras(c, 1); }
void ListaCadenasADN::insertarFinal(const CadenaADN& c) { data.push_back(c); actualizarEstructuras(c, 1); }

bool ListaCadenasADN::insertar(IteradorLista it, const CadenaADN& c) {
    if (it.esVacio()) return false;
    data.insert(it.iter, c); actualizarEstructuras(c, 1); return true;
}
bool ListaCadenasADN::insertarDespues(IteradorLista it, const CadenaADN& c) {
    if (it.esVacio() || it.iter == data.end()) return false;
    auto next = it.iter; data.insert(++next, c); actualizarEstructuras(c, 1); return true;
}
bool ListaCadenasADN::asignar(IteradorLista it, const CadenaADN& c) {
    if (it.esVacio() || it.iter == data.end()) return false;
    actualizarEstructuras(*it.iter, -1); *it.iter = c; actualizarEstructuras(c, 1); return true;
}
bool ListaCadenasADN::borrarPrimera() { if (data.empty()) return false; actualizarEstructuras(data.front(), -1); data.pop_front(); return true; }
bool ListaCadenasADN::borrarUltima() { if (data.empty()) return false; actualizarEstructuras(data.back(), -1); data.pop_back(); return true; }
bool ListaCadenasADN::borrar(IteradorLista &it) {
    if (it.esVacio() || it.iter == data.end()) return false;
    actualizarEstructuras(*it.iter, -1); data.erase(it.iter); it = IteradorLista(); return true;
}

int ListaCadenasADN::longitud() { return data.size(); }
int ListaCadenasADN::contar(const CadenaADN& c) { return frecSecuencias[c.getSecuencia()]; }

ListaCadenasADN ListaCadenasADN::concatenar(ListaCadenasADN& otra) {
    ListaCadenasADN res = *this;
    for (auto& c : otra.data) res.insertarFinal(c);
    return res;
}
ListaCadenasADN ListaCadenasADN::diferencia(ListaCadenasADN& otra) {
    ListaCadenasADN res;
    for (auto& c : data) if (otra.frecSecuencias.find(c.getSecuencia()) == otra.frecSecuencias.end()) res.insertarFinal(c);
    return res;
}
CadenaADN ListaCadenasADN::concatenar() {
    string s = ""; for (auto& c : data) s += c.getSecuencia();
    return CadenaADN(s, "");
}
string ListaCadenasADN::aCadena() {
    stringstream ss;
    for (auto it = data.begin(); it != data.end(); ++it) {
        ss << it->getDescripcion() << ":" << it->getSecuencia();
        if (next(it) != data.end()) ss << "\n";
    }
    return ss.str();
}

int ListaCadenasADN::frecuenciaCodon(const string& c) { return frecCodones[c]; }
int ListaCadenasADN::frecuenciaCadena(const CadenaADN& c) { return frecSecuencias[c.getSecuencia()]; }

string ListaCadenasADN::listaCodones() {
    string res = "";
    for (auto const& [codon, val] : codonesUnicos) res += (res == "" ? "" : "\n") + codon;
    return res;
}
string ListaCadenasADN::listaCadenasADN() {
    map<string, bool> unicas; for (auto& c : data) unicas[c.getSecuencia()] = true;
    string res = "";
    for (auto const& [seq, val] : unicas) res += (res == "" ? "" : "\n") + seq;
    return res;
}
string ListaCadenasADN::listaCadenasConCodon(const string& codon) {
    string res = "";
    if (mapaCodonSecuencias.count(codon))
        for (auto const& [seq, val] : mapaCodonSecuencias[codon]) res += (res == "" ? "" : "\n") + seq;
    return res;
}
void ListaCadenasADN::eliminaDuplicados() {
    unordered_set<string> vistas;
    for (auto it = data.begin(); it != data.end(); ) {
        if (vistas.count(it->getSecuencia())) {
            actualizarEstructuras(*it, -1);
            it = data.erase(it);
        } else { vistas.insert(it->getSecuencia()); ++it; }
    }
}