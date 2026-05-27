#pragma once
template <typename DataType>
/**
 * @brief Clase DLList que representa una lista doblemente enlazada.
 *
 * Esta clase maneja nodos que contienen enlaces hacia el nodo siguiente y el nodo anterior.
 * Permite realizar operaciones como agregar, eliminar y recorrer la lista en ambos sentidos.
 */
class DLList;

template <typename DataType>
/**
 * @brief Clase DLListNode que representa una lista doblemente enlazada.
 *
 * Esta clase maneja nodos que contienen enlaces hacia el nodo siguiente y el nodo anterior.
 * Permite realizar operaciones como agregar, eliminar y recorrer la lista en ambos sentidos.
 */
class DLListNode {
 public:
  friend /**
 * @brief Clase DLList que representa una lista doblemente enlazada.
 *
 * Esta clase maneja nodos que contienen enlaces hacia el nodo siguiente y el nodo anterior.
 * Permite realizar operaciones como agregar, eliminar y recorrer la lista en ambos sentidos.
 */
class DLList<DataType>;

  DLListNode() = default;

  DLListNode(const DataType& value, DLListNode<DataType>* next = nullptr,
             DLListNode<DataType>* prev = nullptr)
             :key(value), next(next), prev(prev){
             }

  ~DLListNode() {};

/**
 * @brief Método de la lista doblemente enlazada.
 * @return Valor correspondiente a la operación.
 */
  DataType getKey() const{
    return key;
  }

  DLListNode<DataType>* getPrev() const{
    return prev;
  }

  DLListNode<DataType>* getNext() const{
    return next;
  }

/**
 * @brief Método de la lista doblemente enlazada.
 * @param key Parámetro de tipo DataType.
 * @return No devuelve valor.
 */
  void setKey(DataType key){
    this->key = key;
  }

/**
 * @brief Método de la lista doblemente enlazada.
 * @return No devuelve valor.
 */
  void setPrev(DLListNode<DataType>* prev){
    this->prev = prev;
  }

/**
 * @brief Método de la lista doblemente enlazada.
 * @return No devuelve valor.
 */
  void setNext(DLListNode<DataType>* next){
    this->next = next;
  }

 private:
  DataType key;

  DLListNode<DataType>* next;

  DLListNode<DataType>* prev;
};

template <typename DataType>
/**
 * @brief Clase DLList que representa una lista doblemente enlazada.
 *
 * Esta clase maneja nodos que contienen enlaces hacia el nodo siguiente y el nodo anterior.
 * Permite realizar operaciones como agregar, eliminar y recorrer la lista en ambos sentidos.
 */
class DLList {
 public:
  DLList() {
    // crear el nodo centinela
    nil = new DLListNode<DataType>();
    // En lista vacia, el centinela apunta a si mismo en ambas direcciones
    nil->setNext(nil);
    nil->setPrev(nil);
  }

  ~DLList() {
    DLListNode<DataType>* actual = nil->getNext();  // Empezar después del centinela
    
    // eliminar todos los nodos hasta volver al centinela
    while (actual != nil) {
      DLListNode<DataType>* temp = actual;
      actual = actual->getNext();
      delete temp;
    }
    
    // eliminar el centinela
    delete nil;
  }

/**
 * @brief Método de la lista doblemente enlazada.
 * @return No devuelve valor.
 */
  void insert(const DataType& value) {
    if (search(value) != nullptr) {
      return;  // Ya existe, no insertar
    }
    
    // crear nuevo nodo
    DLListNode<DataType>* nuevoNodo = new DLListNode<DataType>(value);
    
    
    nuevoNodo->setNext(nil->getNext()); // Insertar al inicio (después del centinela)
    nuevoNodo->setPrev(nil); // nuevoNodo apunta al centinela y al primer elemento actual
    
    // el primer elemento actual ahora apunta hacia atras al nuevo nodo
    nil->getNext()->setPrev(nuevoNodo);
    
    // el centinela apunta al nuevo nodo
    nil->setNext(nuevoNodo);
  }

  DLListNode<DataType>* search(const DataType& value) const { //buscar un valor y retorna el nodo
    DLListNode<DataType>* actual = nil->getNext();  // Empezar después del centinela
    DLListNode<DataType>* resultado = nullptr;
    
    // Recorrer la lista
    while (actual != nil) {
      if (actual->getKey() == value) {
        resultado = actual;  // Encontrado
        actual = nil;        // Salir del loop
      } 
      else {
        actual = actual->getNext();
      }
    }
    
    return resultado;
  }

  // Elimina un valor de la lista
/**
 * @brief Método de la lista doblemente enlazada.
 * @return No devuelve valor.
 */
  void remove(const DataType& value) {
    // Buscar el nodo
    DLListNode<DataType>* nodo = search(value);
    
    if (nodo == nullptr) {
      return;  // No existe
    }
    
    // Eliminar el nodo usando la versión que recibe puntero
    remove(nodo);
  }

  // Elimina un nodo especifico (thetha(1) gracias a los enlaces dobles)
/**
 * @brief Método de la lista doblemente enlazada.
 * @return No devuelve valor.
 */
  void remove(DLListNode<DataType>* nodo) {
    if (nodo == nullptr || nodo == nil) {
      return;  // Nodo inválido o es el centinela
    }
    
    // Conectar el nodo anterior con el siguiente
    // Esto es O(1) porque tenemos acceso directo al prev
    nodo->getPrev()->setNext(nodo->getNext());  // prev salta a next
    nodo->getNext()->setPrev(nodo->getPrev());  // next apunta a prev
    
    // liberar memoria del nodo
    delete nodo;
  }

  // Obtener el nodo centinela
  DLListNode<DataType>* getNil() const {
    return nil;
  }

 private:
  DLListNode<DataType>* nil;
};
