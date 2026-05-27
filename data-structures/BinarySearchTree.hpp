#pragma once
#include <cstddef>
#include <stack>

template <typename DataType>
class BSTree;

/**
 * @class BSTreeNode
 * @brief Plantilla para un nodo de Árbol Binario de Búsqueda.
 * @tparam DataType El tipo de dato que almacena el nodo.
 */
template <typename DataType>
class BSTreeNode {
 public:
  /**
   * @brief Declara a BSTree como clase amiga para acceder a miembros privados.
   */
  friend class BSTree<DataType>;

  /**
   * @brief Constructor por defecto.
   */
  BSTreeNode() = default;
  /**
   * @brief Constructor con parámetros.
   * @param value El valor (clave) que almacenará el nodo.
   * @param parent Puntero al nodo padre (por defecto nullptr).
   * @param left Puntero al hijo izquierdo (por defecto nullptr).
   * @param right Puntero al hijo derecho (por defecto nullptr).
   */
  BSTreeNode(const DataType &value, BSTreeNode<DataType> *parent = nullptr,
             BSTreeNode<DataType> *left = nullptr,
             BSTreeNode<DataType> *right = nullptr)
             : key(value), parent(parent), left(left), right(right){} //inicializa directamente en vez de crear y luego asignar
  /**
   * @brief Destructor.
   */
  ~BSTreeNode(){
  }

  /**
   * @brief Obtiene la clave (valor) del nodo.
   * @return La clave almacenada.
   */
  DataType getKey() const {
    return key;
  }

  /**
   * @brief Obtiene un puntero al nodo padre.
   * @return Puntero al padre.
   */
  BSTreeNode<DataType> *getParent() const{
    return parent;
  }

  /**
   * @brief Obtiene un puntero al hijo izquierdo.
   * @return Puntero al hijo izquierdo.
   */
  BSTreeNode<DataType> *getLeft() const{
    return left;
  }

  /**
   * @brief Obtiene un puntero al hijo derecho.
   * @return Puntero al hijo derecho.
   */
  BSTreeNode<DataType> *getRight() const{
    return right;
  }

  /**
   * @brief Establece el puntero al nodo padre.
   * @param parent El nuevo nodo padre.
   */
  void setParent(BSTreeNode<DataType> *parent) {
    this->parent = parent; //this variable, parent parametro
  }

  /**
   * @brief Establece el puntero al hijo izquierdo.
   * @param left El nuevo hijo izquierdo.
   */
  void setLeft(BSTreeNode<DataType> *left){
    this->left = left;
  }

  /**
   * @brief Establece el puntero al hijo derecho.
   * @param right El nuevo hijo derecho.
   */
  void setRight(BSTreeNode<DataType> *right){
    this->right = right;
  }

 private:
  DataType key; /**< @brief El valor (clave) almacenado en el nodo. */ //valor

  BSTreeNode<DataType> *parent = nullptr; /**< @brief Puntero al nodo padre. */

  BSTreeNode<DataType> *left = nullptr; /**< @brief Puntero al hijo izquierdo. */

  BSTreeNode<DataType> *right = nullptr; /**< @brief Puntero al hijo derecho. */
};

/**
 * @class BSTree
 * @brief Plantilla para un Árbol Binario de Búsqueda (BST).
 * @tparam DataType El tipo de dato que almacenarán los nodos del árbol.
 */
template <typename DataType>
class BSTree {
 public:
  /**
   * @brief Constructor por defecto.
   * @details Inicializa un árbol vacío estableciendo la raíz a nullptr.
   */
  BSTree(){ //arbol vacio
    root = nullptr; 
  }

  /**
   * @brief Destructor.
   * @details Libera toda la memoria asignada por los nodos del árbol
   * utilizando un recorrido postorden.
   */
  ~BSTree() { //liberar memoria con funcion auxiliar
    destruirArbol(root);
  }

  
  /**
   * @brief Inserta un nuevo valor en el árbol.
   * @details No se permiten valores duplicados. Si el valor ya existe, 
   * la función no hace nada.
   * @param value El valor a insertar.
   */
  void insert(const DataType &value) { // Inserta un valor en el arbol sin duplicados
      if (search(root, value) != nullptr) { //ver si ya sirve
          return;  // Ya existe, no insertamos duplicados
      }

      // Crear el nuevo nodo con el valor
      BSTreeNode<DataType> *nuevoNodo = new BSTreeNode<DataType>(value);
      BSTreeNode<DataType> *padre = nullptr;     // guardar el padre del nuevo nodo
      BSTreeNode<DataType> *actual = root;       // empezar desde la raiz

      // buscar la posicion donde insertar
      while (actual != nullptr) {
          padre = actual;  // Guardamos el nodo actual como posible padre
          
          if (value < actual->getKey()) {
              actual = actual->getLeft();   // ir al subarbol izquierdo
          } else {
              actual = actual->getRight();  // ir al subarbol derecho
          }
      }
      // establecer el padre del nuevo nodo
      nuevoNodo->setParent(padre);

      if (padre == nullptr) { // Insertar como hijo del padre
          root = nuevoNodo;  // El arbol estaba vacio, este es el primer nodo
      } 
      else {
          if (value < padre->getKey()) {
              padre->setLeft(nuevoNodo);   // insertar como hijo izquierdo
          } 
          else {
              padre->setRight(nuevoNodo);  // insertar como hijo derecho
          }
      }
  }

  /**
   * @brief Elimina un valor del árbol.
   * @details Maneja los tres casos de eliminación (sin hijos, un hijo, dos hijos).
   * Si el valor no se encuentra, la función no hace nada.
   * @param value El valor a eliminar.
   */
  void remove(const DataType &value){ //eliminar un valor del arbol
    BSTreeNode<DataType> *nodo = search(root, value);
    if(nodo == nullptr){ //si no existe no se hace nada
      return;
    }
    //Caso 1, nodo sin hijo izquierdo
    if(nodo->getLeft() == nullptr){
      transplant(nodo, nodo->getRight()); //funcion auxiliar reemplazando un subarbol por otro, reemplazar por hijo derecho
    }
    else{
      //caso 2, sin hijo derecho
      if(nodo->getRight() == nullptr){
        transplant(nodo, nodo->getLeft()); //reemplazar nodo por su hijo izquierdo
      }
      else{
        //Caso con hijos, se busca el sucesor que es el minimo del subarbol derecho
        BSTreeNode<DataType> *sucesor = getMinimum(nodo->getRight());

        if(sucesor->getParent() != nodo){
          transplant(sucesor, sucesor->getRight());
          sucesor->setRight(nodo->getRight());
          sucesor->getRight()->setParent(sucesor);
        }
      transplant(nodo, sucesor);
      sucesor->setLeft(nodo->getLeft());
      sucesor->getLeft()->setParent(sucesor);
      }
    }
    delete nodo;
  }

  /**
   * @brief Recorre el subárbol en orden (Inorder).
   * @details Visita: Izquierda -> Raíz -> Derecha. 
   * Implementación iterativa usando un std::stack.
   * @param rootOfSubtree El nodo raíz del subárbol a recorrer.
   */
  void inorderWalk(BSTreeNode<DataType> *rootOfSubtree) const{ //Izquierda -> Nodo -> derecha
    if(rootOfSubtree == nullptr){
      return;
    }
    std::stack<BSTreeNode<DataType>*> pila; //stack para la recursion
    BSTreeNode<DataType> *actual = rootOfSubtree;

    while(actual!=nullptr || !pila.empty()){//mientras haya nodos por recorrer
      while(actual!=nullptr){ //mientras haya nodos por procesar
        pila.push(actual); //guardar nodo en el stack
        actual = actual->getLeft(); //ir al hijo izquierdo
      }

      //procesar el nodo en el tope del stack
      actual = pila.top(); //obtener el nodo del tope
      pila.pop(); //remover del stack

      //faltaria procesar el nodo creo

      //ir al subarbol derecho
      actual = actual->getRight();
    }
  }

  /**
   * @brief Recorre el subárbol en preorden (Preorder).
   * @details Visita: Raíz -> Izquierda -> Derecha. 
   * Implementación recursiva. (El procesamiento está comentado).
   * @param rootOfSubtree El nodo raíz del subárbol a recorrer.
   */
  void preorderWalk(BSTreeNode<DataType> *rootOfSubtree) const{
    if (rootOfSubtree == nullptr) {
      return;
    }
    //procesar nodo actual primero
    // std::cout << rootOfSubtree->getKey() << " ";

    //recorrer subarbol izquierdo
    preorderWalk(rootOfSubtree->getLeft());
    
    //recorrer subarbol derecho
    preorderWalk(rootOfSubtree->getRight());
  
  }

  /**
   * @brief Recorre el subárbol en postorden (Postorder).
   * @details Visita: Izquierda -> Derecha -> Raíz. 
   * Implementación recursiva. (El procesamiento está comentado).
   * @param rootOfSubtree El nodo raíz del subárbol a recorrer.
   */
  void postorderWalk(BSTreeNode<DataType> *rootOfSubtree) const{
    if (rootOfSubtree == nullptr) {
      return;
    }
    //recorrer subarbol izquierdo
    postorderWalk(rootOfSubtree->getLeft());
    //recorrer subarbol derecho
    postorderWalk(rootOfSubtree->getRight());

    //procesar nodo actual al final
    // std::cout << rootOfSubtree->getKey() << " ";
    
  }

  /**
   * @brief Busca un valor en el subárbol.
   * @details Implementación iterativa.
   * @param rootOfSubtree El nodo raíz del subárbol donde buscar.
   * @param value El valor a buscar.
   * @return Un puntero al nodo que contiene el valor, o nullptr si no se encuentra.
   */
  BSTreeNode<DataType> *search(const BSTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const{
    const BSTreeNode<DataType> *actual = rootOfSubtree;
    BSTreeNode<DataType> *resultado = nullptr;

    while(actual!= nullptr){
      if(actual->getKey() == value){
        resultado = const_cast<BSTreeNode<DataType>*>(actual);//cast porque actual es const
        actual = nullptr;//salir del loop
      }
      else{
        if(value<actual->getKey()){
          actual = actual->getLeft();
        }
        else{
          actual = actual->getRight();
        }
      }
    }
    return resultado;
  }

  /**
   * @brief Encuentra el nodo con el valor mínimo en un subárbol.
   * @details El mínimo es el nodo que se encuentra más a la izquierda.
   * @param rootOfSubtree El nodo raíz del subárbol.
   * @return Puntero al nodo con el valor mínimo, o nullptr si el subárbol está vacío.
   */
  BSTreeNode<DataType> *getMinimum(
      const BSTreeNode<DataType> *rootOfSubtree) const{
        if(rootOfSubtree == nullptr){
          return nullptr;
        }

        const BSTreeNode<DataType> *actual = rootOfSubtree;
        while(actual->getLeft() != nullptr){ //el minimo esta en el nodo mas a la izquierda
          actual = actual->getLeft();
        }
        return const_cast<BSTreeNode<DataType>*>(actual);
      }

  /**
   * @brief Encuentra el nodo con el valor máximo en un subárbol.
   * @details El máximo es el nodo que se encuentra más a la derecha.
   * @param rootOfSubtree El nodo raíz del subárbol.
   * @return Puntero al nodo con el valor máximo, o nullptr si el subárbol está vacío.
   */
  BSTreeNode<DataType> *getMaximum(const BSTreeNode<DataType> *rootOfSubtree) const{
    if(rootOfSubtree == nullptr){
          return nullptr;
    }

    const BSTreeNode<DataType> *actual = rootOfSubtree;

    while(actual->getRight() != nullptr){ //el maximo esta en el nodo mas a la derecha
      actual = actual->getRight();
    }

    return const_cast<BSTreeNode<DataType>*>(actual);
  }

  /**
   * @brief Encuentra el sucesor de un nodo.
   * @details El sucesor es el nodo con el siguiente valor más grande en el árbol.
   * @param node El nodo del cual se quiere encontrar el sucesor.
   * @return Puntero al nodo sucesor, o nullptr si el nodo es el máximo del árbol.
   */
  BSTreeNode<DataType> *getSuccessor(const BSTreeNode<DataType> *node) const{
    if(node == nullptr){
      return nullptr;
    }

    //Si tiene hijo derecho el sucesor es el minimo del subarbol derecho
    if(node->getRight() != nullptr){
      return getMinimum(node->getRight());
    }

    const BSTreeNode<DataType> *actual = node;
    const BSTreeNode<DataType> *padre = node->getParent();

    while(padre != nullptr && actual == padre->getRight()){
      actual = padre;
      padre = padre->getParent();
    }

    return const_cast<BSTreeNode<DataType>*>(padre);
  }

  /**
   * @brief Obtiene el nodo raíz del árbol.
   * @return Puntero al nodo raíz.
   */
  BSTreeNode<DataType> *getRoot() const{ //retornar la raiz
    return root;
  }

  /**
   * @brief Inserta 'n' nodos de forma rápida, creando un árbol degenerado.
   * @details Limpia el árbol actual e inserta valores de 0 a n-1. 
   * El árbol resultante es una lista enlazada donde cada nodo
   * es el hijo derecho del anterior.
   * @param n El número de nodos a insertar.
   */
  void fastInsert(size_t n){
    root = nullptr; //arbol vacio
    BSTreeNode<DataType> *actual = nullptr; //puntero al ultimo nodo insertado
    
    for(size_t i = 0; i<n; ++i){ //insertar valores de 0 hasta n-1
      BSTreeNode<DataType> *nuevoNodo = new BSTreeNode<DataType>(static_cast<DataType>(i)); //crea nuevo nodo con valor i

      if(i==0){
        //establecer el primer nodo como raiz
        root = nuevoNodo;
        actual = root;
      }
      else{
        actual->setRight(nuevoNodo); //actual apunta al nuevo nodo
        nuevoNodo->setParent(actual); //nuevo nodo tiene a actual como padre
        actual = nuevoNodo; //acrtualizar actual al nuevo nodo
      }
    }
  }
  
 private:
  BSTreeNode<DataType> *root; /**< @brief Puntero al nodo raíz del árbol. */ //raiz arbol


  /**
   * @brief Función auxiliar recursiva para destruir el árbol (en postorden).
   * @details Libera la memoria de los nodos recursivamente.
   * @param nodo El nodo raíz del subárbol actual a destruir.
   */
  //Funcion auxiliar para destruir el arbol(en post orden)
  void destruirArbol(BSTreeNode<DataType> *nodo) {
    if (nodo == nullptr) {
      return;
    }
    
    destruirArbol(nodo->getLeft());
    destruirArbol(nodo->getRight());
    delete nodo;
  }

  /**
   * @brief Reemplaza un subárbol (raíz 'u') por otro (raíz 'v').
   * @details Función auxiliar utilizada en la eliminación. Mueve el subárbol 'v' 
   * a la posición del subárbol 'u', actualizando los punteros del padre.
   * @param u El nodo (y subárbol) a ser reemplazado.
   * @param v El nodo (y subárbol) que reemplazará a 'u'.
   */
  void transplant(BSTreeNode<DataType> *u, BSTreeNode<DataType> *v){ //funcion auxiliar para reemplazar un subarbol por otro
    if(u->getParent()==nullptr){
      root = v; //u era la raiz
    }
    else{
      if(u == u->getParent()->getLeft()){
        u->getParent()->setLeft(v); //u era hijo izquierdo
      }
      else{
        u->getParent()->setRight(v); //u era derecho
      }
    }

    if(v!=nullptr){
      v->setParent(u->getParent());
    }
  }
};
