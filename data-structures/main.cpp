#include <iostream>
#include <chrono>
#include <random>
#include "Student.hpp"
#include "SinglyLinkedList.hpp"
#include "BinarySearchTree.hpp"
#include "RedBlackTree.hpp"
#include "ChainedHashTable.hpp"
#include "OpenAddressHashTable.hpp"

using namespace std;

void testSinglyLinkedList() {
    cout << "\n=== Prueba Lista Simple Enlazada ===" << endl;
    SLList<int> lista;
    
    // Insertar
    for(int i = 0; i < 10; i++) {
        lista.insert(i * 10);
    }
    cout << "Insertados 10 elementos" << endl;
    
    // Buscar
    if(lista.search(50) != nullptr) {
        cout << " Elemento 50 encontrado" << endl;
    }
    if(lista.search(999) == nullptr) {
        cout << " Elemento 999 no encontrado (correcto)" << endl;
    }
    
    // Eliminar
    lista.remove(50);
    if(lista.search(50) == nullptr) {
        cout << " Elemento 50 eliminado correctamente" << endl;
    }
}

void testBST() {
    cout << "\n=== Prueba Arbol Binario de Búsqueda ===" << endl;
    BSTree<int> arbol;
    
    // Insertar
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    for(int val : valores) {
        arbol.insert(val);
    }
    cout << "Insertados 7 elementos" << endl;
    
    // Buscar
    if(arbol.search(arbol.getRoot(), 40) != nullptr) {
        cout << " Elemento 40 encontrado" << endl;
    }
    
    // Mínimo y Máximo
    auto minNode = arbol.getMinimum(arbol.getRoot());
    auto maxNode = arbol.getMaximum(arbol.getRoot());
    cout << " Minimo: " << minNode->getKey() << endl;
    cout << " Maximo: " << maxNode->getKey() << endl;
    
    // Eliminar
    arbol.remove(30);
    if(arbol.search(arbol.getRoot(), 30) == nullptr) {
        cout << " Elemento 30 eliminado correctamente" << endl;
    }
}

void testRedBlackTree() {
    cout << "\n=== Prueba Arbol Rojinegro ===" << endl;
    RBTree<int> arbol;
    
    // Insertar
    for(int i = 1; i <= 10; i++) {
        arbol.insert(i * 5);
    }
    cout << "Insertados 10 elementos" << endl;
    
    // Buscar
    if(arbol.search(arbol.getRoot(), 25) != nullptr) {
        cout << " Elemento 25 encontrado" << endl;
    }
    
    // Eliminar
    arbol.remove(25);
    if(arbol.search(arbol.getRoot(), 25) == nullptr) {
        cout << " Elemento 25 eliminado correctamente" << endl;
    }
}

void testChainedHashTable() {
    cout << "\n=== Prueba Tabla Hash con Encadenamiento ===" << endl;
    ChainedHashTable<int> tabla(100);
    
    // Insertar
    for(int i = 0; i < 50; i++) {
        tabla.insert(i * 7);
    }
    cout << "Insertados 50 elementos" << endl;
    
    // Buscar - search retorna un puntero al nodo, nullptr si no existe
    DLListNode<int>* resultado = tabla.search(49);
    if(resultado != nullptr) {
        cout << " Elemento 49 encontrado" << endl;
    }
    
    // Eliminar
    tabla.remove(49);
    if(tabla.search(49) == nullptr) {
        cout << " Elemento 49 eliminado correctamente" << endl;
    }
}

void testOpenAddressHashTable() {
    cout << "\n=== Prueba Tabla Hash Direccionamiento Abierto ===" << endl;
    OpenAddressHashTable<int> tabla(200);
    
    // Insertar
    for(int i = 1; i <= 50; i++) {
        tabla.insert(i * 3);
    }
    cout << "Insertados 50 elementos" << endl;
    
    // Buscar
    if(tabla.search(15) != static_cast<size_t>(-1)) {
        cout << " Elemento 15 encontrado" << endl;
    }
    
    // Eliminar
    tabla.remove(15);
    if(tabla.search(15) == static_cast<size_t>(-1)) {
        cout << " Elemento 15 eliminado correctamente" << endl;
    }
}

void performanceTest() {
    cout << "\n=== Prueba de Rendimiento Rapida ===" << endl;
    const int N = 10000;
    
    auto start = chrono::high_resolution_clock::now();
    
    // Test BST
    BSTree<int> arbol;
    mt19937 gen(42);
    uniform_int_distribution<> dis(0, 100000);
    
    for(int i = 0; i < N; i++) {
        arbol.insert(dis(gen));
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "ABB: " << N << " inserciones aleatorias en " 
         << duration.count() << " ms" << endl;
    
    // Test Hash Table
    start = chrono::high_resolution_clock::now();
    ChainedHashTable<int> tabla(10000);
    
    for(int i = 0; i < N; i++) {
        tabla.insert(dis(gen));
    }
    
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Tabla Hash: " << N << " inserciones aleatorias en " 
         << duration.count() << " ms" << endl;
}

int main() {
    cout << imprimirDatosDeTarea() << endl;
    cout << "\n========================================" << endl;
    cout << "Pruebas de Estructuras de Datos" << endl;
    cout << "========================================" << endl;
    
    testSinglyLinkedList();
    testBST();
    testRedBlackTree();
    testChainedHashTable();
    testOpenAddressHashTable();
    performanceTest();
    
    cout << "\n========================================" << endl;
    cout << " Todas las pruebas completadas" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
