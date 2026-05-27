#pragma once
#include <cstdint>
#include <vector>

#include "DoublyLinkedList.hpp"

/**
 * @class ChainedHashTable
 * @brief Plantilla para una Tabla Hash con Encadenamiento.
 * @tparam DataType El tipo de dato a almacenar en la tabla.
 */
template <typename DataType>

class ChainedHashTable {
 public:
  /**
   * @brief Constructor.
   * @details Inicializa el vector de listas doblemente enlazadas con el tamaño especificado.
   * @param size El tamaño (m) de la tabla hash.
   */
  ChainedHashTable(size_t size) : size(size), table(size) {};

  /**
   * @brief Destructor.
   */
  ~ChainedHashTable() {
  }

  /**
   * @brief Inserta un valor en la tabla.
   * @details Calcula el índice usando la función hash y luego inserta el valor
   * en la lista doblemente enlazada correspondiente. La lista gestiona los duplicados.
   * @param value El valor a insertar.
   */
  void insert(const DataType& value){
    size_t index = hashFunction(value); /**< calcula el indice usando la funcion h(k) = k mod m */
    table[index].insert(value); /**< la lista ya verifica los duplicados de forma interna */
  }

  /**
   * @brief Busca un valor en la tabla.
   * @details Calcula el índice y busca el valor dentro de la lista enlazada en ese slot.
   * @param value El valor a buscar.
   * @return Un puntero al nodo de lista que contiene el valor, o el puntero centinela (nil)
   * de esa lista si el valor no se encuentra.
   */
  DLListNode<DataType>* search(const DataType& value) const{
    size_t index = hashFunction(value); /**< calcular el indice */
    
    return table[index].search(value);  /**< Buscar en la lista correspondiente */
  }

  /**
   * @brief Elimina un valor de la tabla.
   * @details Calcula el índice y llama a la función de eliminación de la lista enlazada en ese slot.
   * @param value El valor a eliminar.
   */
  void remove(const DataType& value){
    size_t index = hashFunction(value); /**< calcular el indice usando la funcion hash */

    table[index].remove(value);
  }

  /**
   * @brief Obtiene el tamaño total (capacidad) de la tabla.
   * @return El tamaño 'm' de la tabla.
   */
  size_t getSize() const{
    return size;
  }

 private:
  size_t size; /**< @brief Capacidad total de la tabla (m). */

  std::vector<DLList<DataType>> table; /**< @brief Vector de listas doblemente enlazadas (los slots de la tabla). */

  /**
   * @brief Función hash de división.
   * @details Fórmula: h(k) = k mod m.
   * @param value El valor (clave) a hashear.
   * @return Un índice en el rango [0, m-1].
   */
  // Funcion hash: h(k) = k mod m
  size_t hashFunction(const DataType& value) const {
    return static_cast<size_t>(value) % size;
  }

  /**
   * @brief Cuenta cuantos elementos tiene una lista específica.
   * @details Recorre la lista doblemente enlazada, desde el centinela hasta volver a él.
   * @param list La lista a contar.
   * @return El número de elementos en la lista.
   */
  // Cuenta cuantos elementos tiene una lista especifica
  size_t countListSize(const DLList<DataType>& list) const {
    size_t count = 0;
    DLListNode<DataType>* current = list.getNil()->getNext();
    DLListNode<DataType>* nil = list.getNil();
    
    // Recorrer la lista desde el centinela hasta volver a el
    while (current != nil) {
      count++;
      current = current->getNext();
    }
    
    return count;
  }

  /**
   * @brief Cuenta el total de colisiones en toda la tabla.
   * @details En encadenamiento, una colisión ocurre cuando un slot tiene más de 1 elemento.
   * El número de colisiones para un slot es (n - 1), donde n es el tamaño de la lista.
   * @return El número total de colisiones.
   */
  // Cuenta el total de colisiones en toda la tabla
  // Una colision ocurre cuando un slot tiene mas de 1 elemento
  size_t countCollisions() const {
    size_t collisions = 0;
    
    // Revisar cada slot de la tabla
    for (size_t i = 0; i < size; i++) {
      size_t listSize = countListSize(table[i]);
      // Si hay mas de 1 elemento, hay (n-1) colisiones
      if (listSize > 1) {
        collisions += (listSize - 1);
      }
    }
    
    return collisions;
  }

  /**
   * @brief Cuenta el total de elementos almacenados en toda la tabla.
   * @details Suma el tamaño de todas las listas en la tabla.
   * @return El número total de elementos.
   */
  // Cuenta el total de elementos almacenados en toda la tabla
  size_t countElements() const {
    size_t count = 0;
    
    // Sumar elementos de cada slot
    for (size_t i = 0; i < size; i++) {
      count += countListSize(table[i]);
    }
    
    return count;
  }

  /**
   * @brief Calcula el factor de carga (alpha) de la tabla.
   * @details Fórmula: alpha = n / m (elementos / size).
   * @return El factor de carga como un valor double.
   */
  // Calcula el factor de carga: alfa = n/m (elementos/size)
  double getLoadFactor() const {
    return static_cast<double>(countElements()) / static_cast<double>(size);
  }
};
