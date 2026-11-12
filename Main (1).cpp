#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

// Nodo de un árbol general: puede tener cualquier cantidad de hijos
struct NodoGeneral {
    string dato;
    vector<NodoGeneral*> hijos;
    NodoGeneral(string d) : dato(d) {}

    // Agrega un hijo y devuelve el hijo agregado
    NodoGeneral* agregar(string d) {
        NodoGeneral* hijo = new NodoGeneral(d);
        hijos.push_back(hijo);
        return hijo;
    }
};

// Contar nodos
int contar(NodoGeneral* nodo) {
    if (nodo == nullptr) return 0;
    int total = 1;
    for (NodoGeneral* hijo : nodo->hijos) total += contar(hijo);
    return total;
}

// Altura (número de niveles)
int altura(NodoGeneral* nodo) {
    if (nodo == nullptr) return 0;
    int mayor = 0;
    for (NodoGeneral* hijo : nodo->hijos) mayor = max(mayor, altura(hijo));
    return 1 + mayor;
}

// Buscar un valor
bool buscar(NodoGeneral* nodo, const string& valor) {
    if (nodo == nullptr) return false;
    if (nodo->dato == valor) return true;
    for (NodoGeneral* hijo : nodo->hijos)
        if (buscar(hijo, valor)) return true;
    return false;
}

// Contar hojas (nodos sin hijos)
int hojas(NodoGeneral* nodo) {
    if (nodo == nullptr) return 0;
    if (nodo->hijos.empty()) return 1;
    int total = 0;
    for (NodoGeneral* hijo : nodo->hijos) total += hojas(hijo);
    return total;
}

// Preorden: Raíz -> todos los hijos (de izquierda a derecha)
void preorden(NodoGeneral* nodo) {
    if (nodo == nullptr) return;
    cout << nodo->dato << " ";
    for (NodoGeneral* hijo : nodo->hijos) preorden(hijo);
}

// Inorden (convención): primer hijo -> Raíz -> demás hijos
void inorden(NodoGeneral* nodo) {
    if (nodo == nullptr) return;
    if (nodo->hijos.empty()) {
        cout << nodo->dato << " ";
        return;
    }
    inorden(nodo->hijos[0]);
    cout << nodo->dato << " ";
    for (size_t i = 1; i < nodo->hijos.size(); i++) inorden(nodo->hijos[i]);
}

// Postorden: todos los hijos -> Raíz
void postorden(NodoGeneral* nodo) {
    if (nodo == nullptr) return;
    for (NodoGeneral* hijo : nodo->hijos) postorden(hijo);
    cout << nodo->dato << " ";
}

// Liberar la memoria del árbol
void liberar(NodoGeneral* nodo) {
    if (nodo == nullptr) return;
    for (NodoGeneral* hijo : nodo->hijos) liberar(hijo);
    delete nodo;
}

int main() {
    NodoGeneral* raiz = new NodoGeneral("Raiz");
    NodoGeneral* docs  = raiz->agregar("Docs");
    NodoGeneral* fotos = raiz->agregar("Fotos");
    raiz->agregar("Musica");
    docs->agregar("Tareas");
    fotos->agregar("2025");
    fotos->agregar("2026");

    cout << "Nodos: " << contar(raiz) << endl;
    cout << "Altura: " << altura(raiz) << endl;
    cout << "Hojas: " << hojas(raiz) << endl;
    cout << "Existe Fotos? " << (buscar(raiz, "Fotos") ? "si" : "no") << endl;

    cout << "Preorden:  "; preorden(raiz);  cout << endl;
    cout << "Inorden:   "; inorden(raiz);   cout << endl;
    cout << "Postorden: "; postorden(raiz); cout << endl;

    liberar(raiz);
    return 0;
}
