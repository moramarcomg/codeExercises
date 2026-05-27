#pragma once

/**
 * @enum colors
 * @brief Define los colores posibles para un nodo de Árbol Rojo-Negro.
 */
enum colors { RED, BLACK };

template <typename DataType>
class RBTree;

/**
 * @class RBTreeNode
 * @brief Plantilla para un nodo de Árbol Rojo-Negro.
 * @tparam DataType El tipo de dato que almacena el nodo.
 */
template <typename DataType>
class RBTreeNode {
 public:
  /**
   * @brief Declara a RBTree como clase amiga para acceder a miembros privados.
   */
  friend class RBTree<DataType>;

  /**
   * @brief Constructor por defecto.
   */
  RBTreeNode() = default;

  /**
   * @brief Constructor con parámetros.
   * @details Inicializa el nodo con un valor, punteros y un color. Por defecto, un nuevo nodo es ROJO (RED).
   * @param value El valor (clave) que almacenará el nodo.
   * @param parent Puntero al nodo padre (por defecto nullptr).
   * @param left Puntero al hijo izquierdo (por defecto nullptr).
   * @param right Puntero al hijo derecho (por defecto nullptr).
   * @param c El color del nodo (por defecto RED).
   */
  RBTreeNode(const DataType &value, RBTreeNode<DataType> *parent = nullptr,
             RBTreeNode<DataType> *left = nullptr,
             RBTreeNode<DataType> *right = nullptr, enum colors c = RED) 
             : key(value), parent(parent), left(left), right(right), color(c){
             }

  /**
   * @brief Destructor.
   */
  ~RBTreeNode(){
  }

  /**
   * @brief Obtiene la clave (valor) del nodo.
   * @return La clave almacenada.
   */
  DataType getKey() const{
    return key;
  }

  /**
   * @brief Obtiene un puntero al nodo padre.
   * @return Puntero al padre.
   */
  RBTreeNode<DataType> *getParent() const{
    return parent;
  }

  /**
   * @brief Obtiene un puntero al hijo izquierdo.
   * @return Puntero al hijo izquierdo.
   */
  RBTreeNode<DataType> *getLeft() const{
    return left;
  }

  /**
   * @brief Obtiene un puntero al hijo derecho.
   * @return Puntero al hijo derecho.
   */
  RBTreeNode<DataType> *getRight() const{
    return right;
  }

  /**
   * @brief Establece la clave (valor) del nodo.
   * @param key El nuevo valor.
   */
  void setKey(DataType key){
    this->key = key;
  }

  /**
   * @brief Establece el puntero al nodo padre.
   * @param parent El nuevo nodo padre.
   */
  void setParent(RBTreeNode<DataType> *parent){
    this->parent = parent;
  }

  /**
   * @brief Establece el puntero al hijo izquierdo.
   * @param left El nuevo hijo izquierdo.
   */
  void setLeft(RBTreeNode<DataType> *left){
    this->left = left;
  }

  /**
   * @brief Establece el puntero al hijo derecho.
   * @param right El nuevo hijo derecho.
   */
  void setRight(RBTreeNode<DataType> *right){
    this->right = right;
  }

  /**
   * @brief Establece el color del nodo.
   * @param newColor El nuevo color (RED o BLACK).
   */
  void setColor(enum colors newColor){
    this->color = newColor;
  }

 private:
  DataType key; /**< @brief El valor (clave) almacenado en el nodo. */ //valor

  RBTreeNode<DataType> *parent; /**< @brief Puntero al nodo padre. */

  RBTreeNode<DataType> *left; /**< @brief Puntero al hijo izquierdo. */

  RBTreeNode<DataType> *right; /**< @brief Puntero al hijo derecho. */

  enum colors color = RED; /**< @brief Color del nodo (RED o BLACK). */
};


/**
 * @class RBTree
 * @brief Plantilla para un Árbol Rojo-Negro (Red-Black Tree).
 * @tparam DataType El tipo de dato que almacenarán los nodos del árbol.
 */
template <typename DataType>
class RBTree {
 public:
    /**
     * @brief Constructor por defecto.
     * @details Inicializa un árbol vacío creando un nodo centinela 'nil'. 
     * El centinela es siempre NEGRO y representa todas las hojas (null).
     * La raíz apunta inicialmente al centinela.
     */
    RBTree() { //inicializa arbol vacio con centinela
      // crea nodo centinela - siempre es BLACK
      nil = new RBTreeNode<DataType>();
      nil->setColor(BLACK);
      nil->setParent(nil);
      nil->setLeft(nil);
      nil->setRight(nil);
      
      // arbol vacio, y el root apunta al centinela
      root = nil;
    }

  /**
   * @brief Destructor.
   * @details Libera la memoria de todos los nodos del árbol y del nodo centinela.
   */
  ~RBTree() {
    destruirArbol(root);
    delete nil;
  }

  /**
   * @brief Inserta un nuevo valor en el árbol.
   * @details Realiza una inserción estándar de BST, colorea el nuevo nodo de ROJO
   * y luego llama a `insertFixup` para rebalancear el árbol y mantener
   * las propiedades Rojo-Negro. No inserta duplicados.
   * @param value El valor a insertar.
   */
  void insert(const DataType &value){
    if(search(root, value) != nil){
      return;
    }

    //crear nuevo nodo, rojo por defecto
    RBTreeNode<DataType> *nuevoNodo = new RBTreeNode<DataType>(value);
    nuevoNodo->setLeft(nil);
    nuevoNodo->setRight(nil);
    nuevoNodo->setColor(RED);
    //insercion BST
    RBTreeNode<DataType> *padre = nil; 
    RBTreeNode<DataType> *actual = root;

    while(actual != nil){
      padre = actual;
      if(value < actual->getKey()){
        actual = actual->getLeft();
      }
      else{
        actual = actual->getRight();
      }
    }
  //establecer el padre del nuevo nodo
  nuevoNodo->setParent(padre);

    // enlazar al padre con nuevo nodo
    if (padre == nil) {
      root = nuevoNodo;  // arbol estaba vacuo
    } 
    else {
      if (value < padre->getKey()) {
        padre->setLeft(nuevoNodo);
      } 
      else {
        padre->setRight(nuevoNodo);
      }
    }

    // Corregir propiedades del arbol rojinegro
    insertFixup(nuevoNodo);
  }

  
  /**
   * @brief Elimina un valor del árbol.
   * @details Busca el nodo y lo elimina usando la lógica de BST (con `transplant`).
   * Si el nodo eliminado (o el que lo reemplazó) era NEGRO, 
   * llama a `removeFixup` para restaurar las propiedades Rojo-Negro.
   * @param value El valor a eliminar.
   */
  void remove(const DataType &value){
    // Buscar el nodo que se quiere eliminar
    RBTreeNode<DataType> *nodoEliminar = search(root, value);
    
    if (nodoEliminar == nil) {
      return;  // No existe
    }

    // nodoMover = nodo que se mueve o elimina 
    RBTreeNode<DataType> *nodoMover = nodoEliminar;
    
    // aqui se guarda el color original del nodo que se mueve
    enum colors colorOriginal = nodoMover->color;
    
    // nodoReemplazo = nodo que reemplaza
    RBTreeNode<DataType> *nodoReemplazo;

    // caso en el que el nodoEliminar no tiene hijo izquierdo
    if (nodoEliminar->getLeft() == nil) {
      nodoReemplazo = nodoEliminar->getRight();
      transplant(nodoEliminar, nodoEliminar->getRight());
    } 
    else {
      // caso en el que el nodoEliminar no tiene hijo derecho
      if (nodoEliminar->getRight() == nil) {
        nodoReemplazo = nodoEliminar->getLeft();
        transplant(nodoEliminar, nodoEliminar->getLeft());
      } 
      else {
        // caso en el que el nodoEliminar tiene dos hijos - usar sucesor
        nodoMover = getMinimum(nodoEliminar->getRight());  // Sucesor
        colorOriginal = nodoMover->color;
        nodoReemplazo = nodoMover->getRight();

        // Si el sucesor es hijo directo de nodoEliminar
        if (nodoMover->getParent() == nodoEliminar) {
          nodoReemplazo->setParent(nodoMover);  // caso especial
        } 
        else {
          transplant(nodoMover, nodoMover->getRight());
          nodoMover->setRight(nodoEliminar->getRight());
          nodoMover->getRight()->setParent(nodoMover);
        }

        transplant(nodoEliminar, nodoMover);
        nodoMover->setLeft(nodoEliminar->getLeft());
        nodoMover->getLeft()->setParent(nodoMover);
        nodoMover->setColor(nodoEliminar->color);
      }
    }

    // si se elimina un nodo BLACK, corregir propiedades
    if (colorOriginal == BLACK) {
      removeFixup(nodoReemplazo);
    }

    delete nodoEliminar;
  }

  /**
   * @brief Busca un valor en el subárbol.
   * @details Implementación iterativa.
   * @param rootOfSubtree El nodo raíz del subárbol donde buscar.
   * @param value El valor a buscar.
   * @return Un puntero al nodo que contiene el valor, o el puntero 'nil' si no se encuentra.
   */
  RBTreeNode<DataType> *search(const RBTreeNode<DataType> *rootOfSubtree, const DataType &value) const{
    const RBTreeNode<DataType> *actual = rootOfSubtree;
    RBTreeNode<DataType> *resultado = nil;

    while (actual != nil) {
      if (actual->getKey() == value) {
        resultado = const_cast<RBTreeNode<DataType>*>(actual);
        actual = nil;  // Salir del loop
      } 
      else {
        if (value < actual->getKey()) {
          actual = actual->getLeft();
        } 
        else {
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
   * @return Puntero al nodo con el valor mínimo, o 'nil' si el subárbol está vacío.
   */
  RBTreeNode<DataType> *getMinimum(const RBTreeNode<DataType> *rootOfSubtree) const{
    if (rootOfSubtree == nil) {
      return nil;
    }

    const RBTreeNode<DataType> *actual = rootOfSubtree;

    // El minimo esta en el nodo mas a la izquierda
    while (actual->getLeft() != nil) {
      actual = actual->getLeft();
    }

    return const_cast<RBTreeNode<DataType>*>(actual);
  }

  /**
   * @brief Encuentra el nodo con el valor máximo en un subárbol.
   * @details El máximo es el nodo que se encuentra más a la derecha.
   * @param rootOfSubtree El nodo raíz del subárbol.
   * @return Puntero al nodo con el valor máximo, o 'nil' si el subárbol está vacío.
   */
  RBTreeNode<DataType> *getMaximum(const RBTreeNode<DataType> *rootOfSubtree) const{
    if (rootOfSubtree == nil) {
      return nil;
    }

    const RBTreeNode<DataType> *actual = rootOfSubtree;

    // El maximo esta en el nodo mas a la derecha
    while (actual->getRight() != nil) {
      actual = actual->getRight();
    }

    return const_cast<RBTreeNode<DataType>*>(actual);
  }

  /**
   * @brief Encuentra el sucesor de un nodo (el siguiente nodo en orden).
   * @param node El nodo del cual se quiere encontrar el sucesor.
   * @return Puntero al nodo sucesor, o 'nil' si el nodo es el máximo del árbol.
   */
  RBTreeNode<DataType> *getSuccessor(const RBTreeNode<DataType> *node) const{
    if (node == nil) {
      return nil;
    }

    // Si tiene hijo derecho, el sucesor es el mínimo del subárbol derecho
    if (node->getRight() != nil) {
      return getMinimum(node->getRight());
    }

    // Si no, subir hasta encontrar un ancestro que sea hijo izquierdo
    const RBTreeNode<DataType> *actual = node;
    const RBTreeNode<DataType> *padre = node->getParent();

    while (padre != nil && actual == padre->getRight()) {
      actual = padre;
      padre = padre->getParent();
    }

    return const_cast<RBTreeNode<DataType>*>(padre);
  }

  /**
   * @brief Obtiene el nodo raíz del árbol.
   * @return Puntero al nodo raíz (puede ser 'nil' si el árbol está vacío).
   */
  RBTreeNode<DataType> *getRoot() const{
    return root;
  }

  /**
   * @brief Obtiene el nodo centinela 'nil'.
   * @return Puntero al nodo centinela.
   */
  RBTreeNode<DataType> *getNil() const{
    return nil;
  }


 private:
  RBTreeNode<DataType> *root; /**< @brief Puntero al nodo raíz del árbol. */

  RBTreeNode<DataType> *nil; /**< @brief Puntero al nodo centinela (hoja nula). */

/**
 * @brief Función auxiliar recursiva para destruir el árbol (en postorden).
 * @details Libera la memoria de los nodos recursivamente. Se detiene al llegar a 'nil'.
 * @param nodo El nodo raíz del subárbol actual a destruir.
 */
// Funcion auxiliar para destruir el arbol en postorden
  void destruirArbol(RBTreeNode<DataType> *nodo) {
    if (nodo == nil) {
      return;
    }

    destruirArbol(nodo->getLeft());
    destruirArbol(nodo->getRight());
    delete nodo;
  }

  /**
   * @brief Realiza una rotación a la izquierda alrededor del nodo 'nodoX'.
   * @param nodoX El nodo que actúa como pivote de la rotación.
   */
  // Rotacion a la izquierda
  void leftRotate(RBTreeNode<DataType> *nodoX) {
    // nodoY = hijo derecho de nodoX (y = x.right)
    RBTreeNode<DataType> *nodoY = nodoX->getRight();
    
    // Convertir el hijo izquierdo de Y en hijo derecho de X
    nodoX->setRight(nodoY->getLeft());
    
    if (nodoY->getLeft() != nil) {
      nodoY->getLeft()->setParent(nodoX);
    }

    // El padre de X se convierte en padre de Y
    nodoY->setParent(nodoX->getParent());
    
    if (nodoX->getParent() == nil) {
      root = nodoY;  // Y es la nueva raíz
    } 
    else {
      if (nodoX == nodoX->getParent()->getLeft()) {
        nodoX->getParent()->setLeft(nodoY);
      } 
      else {
        nodoX->getParent()->setRight(nodoY);
      }
    }

    // X se convierte en hijo izquierdo de Y
    nodoY->setLeft(nodoX);
    nodoX->setParent(nodoY);
  }

  /**
   * @brief Realiza una rotación a la derecha alrededor del nodo 'nodoY'.
   * @param nodoY El nodo que actúa como pivote de la rotación.
   */
  // Rotacion a la derecha 
  void rightRotate(RBTreeNode<DataType> *nodoY) {
    // nodoX = hijo izquierdo de nodoY (x = y.left)
    RBTreeNode<DataType> *nodoX = nodoY->getLeft();
    
    // Convertir el hijo derecho de X en hijo izquierdo de Y
    nodoY->setLeft(nodoX->getRight());
    
    if (nodoX->getRight() != nil) {
      nodoX->getRight()->setParent(nodoY);
    }

    // El padre de Y se convierte en padre de X
    nodoX->setParent(nodoY->getParent());
    
    if (nodoY->getParent() == nil) {
      root = nodoX;  // X es la nueva raíz
    } 
    else {
      if (nodoY == nodoY->getParent()->getLeft()) {
        nodoY->getParent()->setLeft(nodoX);
      } 
      else {
        nodoY->getParent()->setRight(nodoX);
      }
    }

    // Y se convierte en hijo derecho de X
    nodoX->setRight(nodoY);
    nodoY->setParent(nodoX);
  }

  /**
   * @brief Restaura las propiedades Rojo-Negro después de una inserción.
   * @details Corrige violaciones (ej. padre e hijo ROJOS) mediante recoloración
   * y rotaciones, moviéndose hacia arriba del árbol.
   * @param nodo El nodo recién insertado (que es ROJO).
   */
  // Corregir propiedades despues de insertar
  void insertFixup(RBTreeNode<DataType> *nodo) {
    // Mientras el padre sea RED (viola propiedad)
    while (nodo->getParent()->color == RED) {
      
      // Caso A: el padre es hijo izquierdo del abuelo
      if (nodo->getParent() == nodo->getParent()->getParent()->getLeft()) {
        // tio = hermano del padre
        RBTreeNode<DataType> *tio = nodo->getParent()->getParent()->getRight();
        
        // Caso 1: El tio es RED
        if (tio->color == RED) {
          nodo->getParent()->setColor(BLACK);
          tio->setColor(BLACK);
          nodo->getParent()->getParent()->setColor(RED);
          nodo = nodo->getParent()->getParent();
        } 
        else {
          // Caso 2: El tio es BLACK y nodo es hijo derecho
          if (nodo == nodo->getParent()->getRight()) {
            nodo = nodo->getParent();
            leftRotate(nodo);
          }
          // Caso 3: El tio es BLACK y nodo es hijo izquierdo
          nodo->getParent()->setColor(BLACK);
          nodo->getParent()->getParent()->setColor(RED);
          rightRotate(nodo->getParent()->getParent());
        }
      } 
      else {
        // Caso B: El padre es hijo derecho del abuelo
        RBTreeNode<DataType> *tio = nodo->getParent()->getParent()->getLeft();
        
        // Caso 1: El tio es RED
        if (tio->color == RED) {
          nodo->getParent()->setColor(BLACK);
          tio->setColor(BLACK);
          nodo->getParent()->getParent()->setColor(RED);
          nodo = nodo->getParent()->getParent();
        } 
        else {
          // Caso 2: El tio es BLACK y nodo es hijo izquierdo
          if (nodo == nodo->getParent()->getLeft()) {
            nodo = nodo->getParent();
            rightRotate(nodo);
          }
          // Caso 3: El tio es BLACK y nodo es hijo derecho
          nodo->getParent()->setColor(BLACK);
          nodo->getParent()->getParent()->setColor(RED);
          leftRotate(nodo->getParent()->getParent());
        }
      }
    }
    
    // La raiz siempre debe ser BLACK
    root->setColor(BLACK);
  }

  /**
   * @brief Restaura las propiedades Rojo-Negro después de una eliminación.
   * @details Corrige el "doble NEGRO" (una violación de la altura negra)
   * que ocurre cuando se elimina un nodo NEGRO.
   * @param nodo El nodo que reemplazó al nodo eliminado (o 'nil').
   */
  // Corregir propiedades despues de eliminar
  void removeFixup(RBTreeNode<DataType> *nodo) {
    // Mientras nodo no sea la raiz y sea BLACK
    while (nodo != root && nodo->color == BLACK) {
      
      // Caso A: nodo es hijo izquierdo
      if (nodo == nodo->getParent()->getLeft()) {
        // hermano = hermano de nodo
        RBTreeNode<DataType> *hermano = nodo->getParent()->getRight();
        
        // Caso 1: El hermano es RED
        if (hermano->color == RED) {
          hermano->setColor(BLACK);
          nodo->getParent()->setColor(RED);
          leftRotate(nodo->getParent());
          hermano = nodo->getParent()->getRight();
        }
        
        // Caso 2: El hermano es BLACK y ambos hijos son BLACK
        if (hermano->getLeft()->color == BLACK && hermano->getRight()->color == BLACK) {
          hermano->setColor(RED);
          nodo = nodo->getParent();
        } 
        else {
          // Caso 3: El hermano es BLACK, hijo derecho BLACK, hijo izquierdo RED
          if (hermano->getRight()->color == BLACK) {
            hermano->getLeft()->setColor(BLACK);
            hermano->setColor(RED);
            rightRotate(hermano);
            hermano = nodo->getParent()->getRight();
          }
          // Caso 4: El hermano es BLACK y el hijo derecho es RED
          hermano->setColor(nodo->getParent()->color);
          nodo->getParent()->setColor(BLACK);
          hermano->getRight()->setColor(BLACK);
          leftRotate(nodo->getParent());
          nodo = root;  // Terminamos
        }
      } 
      else {
        // Caso B: nodo es hijo derecho
        RBTreeNode<DataType> *hermano = nodo->getParent()->getLeft();
        
        // Caso 1: El hermano es RED
        if (hermano->color == RED) {
          hermano->setColor(BLACK);
          nodo->getParent()->setColor(RED);
          rightRotate(nodo->getParent());
          hermano = nodo->getParent()->getLeft();
        }
        
        // Caso 2: El hermano es BLACK y ambos hijos son BLACK
        if (hermano->getRight()->color == BLACK && hermano->getLeft()->color == BLACK) {
          hermano->setColor(RED);
          nodo = nodo->getParent();
        } 
        else {
          // Caso 3: El hermano es BLACK, hijo izquierdo BLACK, hijo derecho RED
          if (hermano->getLeft()->color == BLACK) {
            hermano->getRight()->setColor(BLACK);
            hermano->setColor(RED);
            leftRotate(hermano);
            hermano = nodo->getParent()->getLeft();
          }
          // Caso 4: El hermano es BLACK y el hijo izquierdo es RED
          hermano->setColor(nodo->getParent()->color);
          nodo->getParent()->setColor(BLACK);
          hermano->getLeft()->setColor(BLACK);
          rightRotate(nodo->getParent());
          nodo = root;  // Terminamos
        }
      }
    }
    
    // Asegurar que nodo sea BLACK
    nodo->setColor(BLACK);
  }

  /**
   * @brief Reemplaza un subárbol (raíz 'nodoU') por otro (raíz 'nodoV').
   * @details Función auxiliar utilizada en la eliminación. Mueve el subárbol 'nodoV' 
   * a la posición del subárbol 'nodoU', actualizando los punteros del padre.
   * @param nodoU El nodo (y subárbol) a ser reemplazado.
   * @param nodoV El nodo (y subárbol) que reemplazará a 'nodoU'.
   */
  // Funcion auxiliar para reemplazar un subarbol por otro
  void transplant(RBTreeNode<DataType> *nodoU, RBTreeNode<DataType> *nodoV) {
    if (nodoU->getParent() == nil) {
      root = nodoV;  // nodoU era la raiz
    } 
    else {
      if (nodoU == nodoU->getParent()->getLeft()) {
        nodoU->getParent()->setLeft(nodoV);  // nodoU era hijo izquierdo
      } 
      else {
        nodoU->getParent()->setRight(nodoV);  // nodoU era hijo derecho
      }
    }
    nodoV->setParent(nodoU->getParent());
  }
};
