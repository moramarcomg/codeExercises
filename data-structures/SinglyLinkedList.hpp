#pragma once
template <typename DataType>
/** 
 * @brief Clase SLList que representa una lista simplemente enlazada.
 *
 * Esta clase gestiona nodos de una lista enlazada, permitiendo agregar, eliminar,
 * y recorrer elementos.
 */
class SLList;

template <typename DataType>
/** 
 * @brief Clase SLListNode que representa una lista simplemente enlazada.
 *
 * Esta clase gestiona nodos de una lista enlazada, permitiendo agregar, eliminar,
 * y recorrer elementos.
 */
class SLListNode {
 public:
/** 
 * @brief Clase SLList que representa una lista simplemente enlazada.
 *
 * Esta clase gestiona nodos de una lista enlazada, permitiendo agregar, eliminar,
 * y recorrer elementos.
 */
    friend class SLList<DataType>;

  SLListNode(){
    key = DataType();
    next = nullptr;
  }

  SLListNode(const DataType& value, SLListNode<DataType>* next = nullptr){
    this->key = value; //guarda el valor
    this->next = next; //guarda el puntero al siguiente
  }

  ~SLListNode(){}

/**
 * @brief Método de la lista enlazada.
 * @return Valor correspondiente a la operación.
 */
  DataType getKey() const{ //retorna el valor
    return key;
  }

  SLListNode<DataType>* getNext() const { //retorna puntero al siguiente nodo
    return next;
  }

/**
 * @brief Método de la lista enlazada.
 * @param key Parámetro de tipo DataType.
 * @return No devuelve valor.
 */
  void setKey(DataType key) { //cambia el valor del nodo
    this->key = key;
  }

/**
 * @brief Método de la lista enlazada.
 * @return No devuelve valor.
 */
  void setNext(SLListNode<DataType>* newNode){ //cambia al siguiente nodo
    this->next= newNode;
  }

 private:
  DataType key; //valor almacenado

  SLListNode<DataType>* next; //puntero al siguiente
};

template <typename DataType>
/** 
 * @brief Clase SLList que representa una lista simplemente enlazada.
 *
 * Esta clase gestiona nodos de una lista enlazada, permitiendo agregar, eliminar,
 * y recorrer elementos.
 */
class SLList {
 public:
  SLList(){
    nil = new SLListNode<DataType>(); //crear el centinela
    nil->setNext(nil); //en lista vacia se apunta al nil mismo
  }

  ~SLList() {
    SLListNode<DataType>* actual = nil->getNext(); //Empezar despues del centinela

    while (actual != nil){ //Eliminar los nodos actuales hasta llegar al centinela
      SLListNode<DataType>* temp = actual; //guardar el nodo actual
      actual = actual->getNext(); //avanzar al siguiente
      delete temp; //se elimina el nodo guardado
    }
    delete nil; //se elimina el centinela
  }

/**
 * @brief Método de la lista enlazada.
 * @return No devuelve valor.
 */
  void insert(const DataType& value){ //ver si se insertan duplicados o no
    if(search(value) != nullptr){
      return;
    }

    
    SLListNode<DataType>* newNode = new SLListNode<DataType>(value, nil->getNext()); //Se crea un nodo que apunta al primer elemento actual
    
    nil->setNext(newNode); //El centinela apunta al nuevo nodo ahora
  }

  SLListNode<DataType>* search(const DataType& value) const{
    SLListNode<DataType>* resultado = nullptr; //no encontrado
    SLListNode<DataType>* actual = nil->getNext(); //empezar despues del centinela

    while(actual!=nil){
      if(actual->getKey()==value){
        resultado = actual; //guardar el nodo encontrado
        actual = nil; //forzar salida
      }
      else{
        actual = actual->getNext(); //seguir buscando
      }
    }

    return resultado;
  }

/**
 * @brief Método de la lista enlazada.
 * @return No devuelve valor.
 */
  void remove(const DataType& value){
    SLListNode<DataType>* prev = nil; //Nodo anterior, que empieza en centinela
    SLListNode<DataType>* actual = nil->getNext(); //Primer elemento que es el nodo actual

    //recorre lista
    while(actual != nil){
      if(actual->getKey() == value){
        prev->setNext(actual->getNext());
        delete actual;
        return;
      }

      prev = actual; //no es ese por lo que se avanzan ambos punteros
      actual = actual->getNext();
    }
    //si sale del while el valor no estaba en la lista
  }

  SLListNode<DataType>* getNil() const{
    return nil;
  }
  
 private:
  SLListNode<DataType>* nil; //nodo centinela

};
