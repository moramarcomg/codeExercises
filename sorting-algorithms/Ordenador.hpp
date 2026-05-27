#include <cstdint>
#pragma once

#include <iostream>
#include <string>
#include <cmath>

/**
 * @class Ordenador
 * @brief Clase que implementa varios algoritmos de ordenamiento
 * 
 * Esta clase contiene implementaciones de diferentes algoritmos de ordenamiento
 * incluyendo selección, inserción, mezcla, montículos, rápido y residuos.
 */
class Ordenador {
    private:
    // Defina aquí los métodos auxiliares de los algoritmos de ordenamiento solamente.
    // Puede definir cuantos métodos quiera.
    
    //QuickSort:
    /**
     * @brief Implementación recursiva del algoritmo QuickSort
     * @param A Puntero al arreglo a ordenar
     * @param p Índice inicial del subarreglo
     * @param r Índice final del subarreglo
     */
    void rapidoRecursivo(int *A, int p, int r) const;
    
    /**
     * @brief Función de partición para QuickSort estándar
     * @param A Puntero al arreglo a particionar
     * @param p Índice inicial del subarreglo
     * @param r Índice final del subarreglo (pivote)
     * @return Índice final del pivote después de la partición
     */
    int partition(int *A, int p, int r) const;
    
    //Para el QuickSort con pivote de mediana de 3:
    /**
     * @brief Implementación recursiva del QuickSort con mediana de 3
     * @param A Puntero al arreglo a ordenar
     * @param p Índice inicial del subarreglo
     * @param r Índice final del subarreglo
     */
    void rapidoRecursivoV2(int *A, int p, int r) const;
    
    /**
     * @brief Función de partición con mediana de 3 para selección de pivote
     * @param A Puntero al arreglo a particionar
     * @param p Índice inicial del subarreglo
     * @param r Índice final del subarreglo
     * @return Índice final del pivote después de la partición
     */
    int partitionV2(int *A, int p, int r) const;
    
    //Desde aqui uso uint32 para no hacer castings
    //MergeSort:
    /**
     * @brief Implementación recursiva del algoritmo MergeSort
     * @param A Puntero al arreglo a ordenar
     * @param p Índice inicial del subarreglo
     * @param r Índice final del subarreglo
     */
    void mergeSort(std::uint32_t *A, std::uint32_t p, std::uint32_t r) const;
    
    /**
     * @brief Función que mezcla dos subarreglos ordenados
     * @param A Puntero al arreglo original
     * @param p Índice inicial del primer subarreglo
     * @param q Índice final del primer subarreglo
     * @param r Índice final del segundo subarreglo
     */
    void mezcla(std::uint32_t *A, std::uint32_t p, std::uint32_t q, std::uint32_t r) const;
    
    //HeapSort:
    /**
     * @brief Mantiene la propiedad de max-heap para un nodo dado
     * @param A Puntero al arreglo que representa el heap
     * @param i Índice del nodo a heapificar
     * @param heapSize Tamaño actual del heap
     */
    void maxHeapify(std::uint32_t *A, std::uint32_t i, std::uint32_t heapSize) const;
    
    /**
     * @brief Construye un max-heap a partir de un arreglo desordenado
     * @param A Puntero al arreglo a convertir en heap
     * @param n Tamaño del arreglo
     */
    void buildMaxHeap(std::uint32_t *A, std::uint32_t n) const;
    
    //Radix con el counting incluido:
    /**
     * @brief Implementación de Counting Sort para un dígito específico (usado en Radix Sort)
     * @param A Puntero al arreglo a ordenar
     * @param n Tamaño del arreglo
     * @param exp Exponente que representa el dígito actual (1, 10, 100, etc.)
     */
    void countingSort(std::uint32_t *A, std::uint32_t n, std::uint32_t exp) const;
    
    /**
     * @brief Encuentra el valor máximo en el arreglo
     * @param A Puntero al arreglo
     * @param n Tamaño del arreglo
     * @return El valor máximo encontrado en el arreglo
     */
    std::uint32_t getMax(std::uint32_t *A, std::uint32_t n) const;

    public:
    Ordenador() = default;
    ~Ordenador() = default;
    /* Nota:
     - Si no planea implementar algunos de los métodos de ordenamiento, no los borre.
     - Simplemente déjelos con el cuerpo vacío para evitar errores de compilación, ya
       que se ejecutará el mismo main para todas las tareas.
     - Recuerde hacer uso de programación defensiva y documentar los métodos con formato Doxygen, por ejemplo.
     - No cambié la firma de los métodos de la clase Ordenador.
     - No lance excepciones para el manejo de errores.
       Ante un error, basta con que el método no modifique el arreglo original y que no cause la caída del programa.
    */ 
  
    /**
     * @brief Implementa el algoritmo de ordenamiento por selección
     * @param A Puntero al arreglo de enteros sin signo a ordenar
     * @param n Tamaño del arreglo
     * 
     * Complejidad temporal: O(n^2) en todos los casos
     * Complejidad espacial: O(1)
     * Es un algoritmo in-place pero no estable
     */
    void ordenamientoPorSeleccion(std::uint32_t *A, std::uint32_t n) const;
    
    /**
     * @brief Implementa el algoritmo de ordenamiento por inserción
     * @param A Puntero al arreglo de enteros sin signo a ordenar
     * @param n Tamaño del arreglo
     * 
     * Complejidad temporal: O(n^2) en el peor caso, O(n) en el mejor caso
     * Complejidad espacial: O(1)
     * Es un algoritmo in-place y estable
     */
    void ordenamientoPorInserccion(std::uint32_t *A, std::uint32_t n) const;
    
    /**
     * @brief Implementa el algoritmo de ordenamiento por mezcla (MergeSort)
     * @param A Puntero al arreglo de enteros sin signo a ordenar
     * @param n Tamaño del arreglo
     * 
     * Complejidad temporal: O(n log n) en todos los casos
     * Complejidad espacial: O(n)
     * Es un algoritmo estable pero no in-place
     */
    void ordenamientoPorMezcla(std::uint32_t *A, std::uint32_t n) const;
    
    /**
     * @brief Implementa el algoritmo de ordenamiento por montículos (HeapSort)
     * @param A Puntero al arreglo de enteros sin signo a ordenar
     * @param n Tamaño del arreglo
     * 
     * Complejidad temporal: O(n log n) en todos los casos
     * Complejidad espacial: O(1)
     * Es un algoritmo in-place pero no estable
     */
    void ordenamientoPorMonticulos(std::uint32_t *A, std::uint32_t n) const;
    
    /**
     * @brief Implementa el algoritmo de ordenamiento rápido (QuickSort)
     * @param A Puntero al arreglo de enteros sin signo a ordenar
     * @param n Tamaño del arreglo
     * 
     * Utiliza QuickSort estándar si el primer elemento es impar,
     * o QuickSort con mediana de 3 si el primer elemento es par.
     * 
     * Complejidad temporal: O(n log n) promedio, O(n²) peor caso
     * Complejidad espacial: O(log n) promedio por la recursión
     * Es un algoritmo in-place pero no estable
     */
    void ordenamientoRapido(std::uint32_t *A, std::uint32_t n) const;
    
    /**
     * @brief Implementa el algoritmo de ordenamiento por residuos (Radix Sort)
     * @param A Puntero al arreglo de enteros sin signo a ordenar
     * @param n Tamaño del arreglo
     * 
     * Ordena los números procesando cada dígito desde el menos significativo
     * hasta el más significativo usando Counting Sort como subrutina.
     * 
     * Complejidad temporal: O(d(n+k)) donde d es el número de dígitos y k es el rango de cada dígito
     * Complejidad espacial: O(n+k)
     * Es un algoritmo estable pero no in-place
     */
    void ordenamientoPorResiduos(std::uint32_t *A, std::uint32_t n) const;

    /**
     * @brief Retorna un std::string con los datos de la tarea.
     * 
     * Este método devuelve una cadena de texto que contiene el carné, nombre y tarea.
     * 
     * @return std::string Una cadena de texto con los datos de la tarea.
     */
    constexpr const char* imprimirDatosDeTarea() const {
      return "Carné: C4H541, Nombre: Marco Antonio Mora Gomez, Tarea 1";
    } 
};


/**
 * @brief Implementación del algoritmo de ordenamiento por selección
 * 
 * Busca repetitivamente el elemento mínimo del subarreglo no ordenado
 * y lo coloca en su posición correcta al inicio del subarreglo ordenado.
 */
void Ordenador::ordenamientoPorSeleccion(std::uint32_t *A, std::uint32_t n) const{
  for(std::uint32_t i = 0; i < n-1; ++i){  //Iterar a traves de todos los elementos menos el ultimo
    std::uint32_t m = i; //elemento actual es el minimo
    for(std::uint32_t j = i + 1; j < n; ++j){ //busca el elemento minimo en el subarreglo sin ordenar
      if(A[j] < A[m]){ //si encuentra un menor que el minimo actual actualiza la posicion del minimo
        m = j;
      }
    }
    std::swap(A[i], A[m]); //intercambia el elemento actual con el mínimo encontrado
  }
}

/**
 * @brief Implementación del algoritmo de ordenamiento por inserción
 * 
 * Construye el arreglo ordenado elemento por elemento, insertando cada
 * nuevo elemento en su posición correcta dentro de la parte ya ordenada.
 */
void Ordenador::ordenamientoPorInserccion(std::uint32_t *A, std::uint32_t n) const{
  for(std::uint32_t i = 1; i < n; ++i){
    std::uint32_t key = A[i]; //guarda el valor actual que se va a insertar

    int j = static_cast<int>(i) - 1; //esto es necesario para que j pueda llegar a ser negativo
    while(j>=0 && A[j] > key){ //mueve los elementos mayores que key a la derecha
      A[j+1] = A[j];
      j = j-1;
    }
    A[j+1] = key; //key en su posicion correcta
  }
} 

/**
 * @brief Método público que inicia el algoritmo MergeSort
 * 
 * Actúa como interfaz pública para el algoritmo recursivo de ordenamiento por mezcla.
 */
 void Ordenador::ordenamientoPorMezcla(std::uint32_t *A, std::uint32_t n) const{
  mergeSort(A, 0, n-1); //llama a la funcion recursiva
 }

/**
 * @brief Implementación recursiva del algoritmo MergeSort
 * 
 * Divide el arreglo en dos mitades, las ordena recursivamente
 * y luego las mezcla en orden.
 */
void Ordenador::mergeSort(std::uint32_t *A, std::uint32_t p, std::uint32_t r) const{
  if(p >= r) { //si el subarreglo tiene 0 o 1 ya esta ordenado
    return;
  }
  std::uint32_t q = (p + r) /2; //calcula el punto medio para dividir el arreglo en 2
  mergeSort(A, p, q); //ordena recursivamente la izquierda
  mergeSort(A, q+1, r); //tambien la derecha
  mezcla(A, p, q, r); //mezcla las dos mitades ordenadas
}


/**
 * @brief Mezcla dos subarreglos ordenados en uno solo ordenado
 * 
 * Combina los subarreglos A[p..q] y A[q+1..r] asumiendo que ambos
 * ya están ordenados, produciendo A[p..r] ordenado.
 */
void Ordenador::mezcla(std::uint32_t *A, std::uint32_t p, std::uint32_t q, std::uint32_t r) const{
  //Size de los subarreglos:
  std::uint32_t nL = q - p + 1; //izquierdo/left
  std::uint32_t nR = r-q; //derecho/right
  //Arreglos temporales para almacenar las dos mitades:
  std::uint32_t *L = new std::uint32_t[nL];
  std::uint32_t *R = new std::uint32_t[nR];

  //Copiar datos a los arreglos temporales:
  for(std::uint32_t i = 0; i < nL; ++i){ //el izquierdo
    L[i] = A[p+i];
  }
  for(std::uint32_t j = 0; j < nR; ++j){ //el derecho
    R[j] = A[q+j+1];
  }

  //Mezclar los arreglos temporales de vuelta en A[desde p hasta r]
  std::uint32_t i = 0; //índice para el arreglo izquierdo L
  std::uint32_t j = 0; //índice para el arreglo derecho R
  std::uint32_t k = p; //índice para el arreglo original A

  while(i<nL && j<nR){ //mientras hayan elementos en los arrays temporales
    if(L[i] <= R[j]){ //compara elementos de L y R, coloca el menor en A
      A[k] = L[i];
      ++i;
    }
    else{
      A[k] = R[j];
      ++j;
    }
    ++k;
  }
  while(i<nL){ //copiar los elementos restantes de L
    A[k] = L[i];
    ++i;
    ++k;
  }
  while(j<nR){ //copiar los elementos restantes de R
    A[k] = R[j];
    ++j;
    ++k;
  }
  //liberar memoria de los temporales
  delete [] L;
  delete [] R;
}

/**
 * @brief Implementación del algoritmo HeapSort
 * 
 * Construye un max-heap y extrae repetitivamente el máximo,
 * colocándolo al final del arreglo ordenado.
 */
void Ordenador::ordenamientoPorMonticulos(std::uint32_t *A, std::uint32_t n) const{
  // Construye un max-heap a partir del arreglo desordenado
  buildMaxHeap(A,n);
  //Extrae elementos uno por uno del heap
  for(std::uint32_t i = n; i>1; --i){ //Esta incluido el A.heap-size = A.heap-size - 1
    std::swap(A[0], A[i - 1]); //mover max al final
    maxHeapify(A, 0, i - 1); // i - 1 ahora es el nuevo size del heap
  }
}



/**
 * @brief Mantiene la propiedad de max-heap hacia abajo desde un nodo
 * 
 * Asegura que el subárbol con raíz en el índice i satisfaga
 * la propiedad de max-heap, asumiendo que los subárboles
 * izquierdo y derecho ya son max-heaps válidos.
 */
void Ordenador::maxHeapify(std::uint32_t *A, std::uint32_t i, std::uint32_t heapSize) const{
  std::uint32_t l = 2 * i + 1; //Indice del hijo del nodo izquierdo
  std::uint32_t r = 2 * i + 2; //Indice del hijo del nodo derecho
  std::uint32_t largest = i; //asume nodo actual es el mas grande

  if(l < heapSize && A[l] > A[i]){ //compara si con el hijo de la izquierda si existe y es mayor
    largest = l;
  }

  if(r < heapSize && A[r] > A[largest]){ //lo mismo con el derecho
    largest = r;
  }

  if(largest!=i){ //revisa si el actual no es el mas grande, si no lo es lo ajusta
    std::swap(A[i], A[largest]); //actual por el mas grande
    maxHeapify(A, largest, heapSize); //heapify recursivo
  }
}

/**
 * @brief Construye un max-heap a partir de un arreglo desordenado
 * 
 * Aplica maxHeapify desde el último nodo no-hoja hacia arriba
 * hasta convertir todo el arreglo en un max-heap válido.
 */
void Ordenador::buildMaxHeap(std::uint32_t *A, std::uint32_t n) const {
    // Empezar desde el último nodo no-hoja e ir hacia arriba
    for(int i = (n / 2) - 1; i >= 0; --i) { //int para que pueda llegar a ser negativos
        maxHeapify(A, i, n);
    }
}

/**
 * @brief Implementación recursiva estándar del algoritmo QuickSort
 * 
 * Particiona el arreglo usando el último elemento como pivote
 * y ordena recursivamente las dos particiones.
 */
void Ordenador::rapidoRecursivo(int *A, int p, int r) const {
  if( p < r ){ //si el arreglo tiene mas de un elemento
    int q = partition(A, p, r); //obtiene el indice del pivote en su posición final
    rapidoRecursivo(A, p, q-1); //ordena recursivamente el subarreglo izquierdo
    rapidoRecursivo(A, q+1, r); //ahora el derecho
  }
}

/**
 * @brief Función de partición estándar para QuickSort
 * 
 * Reorganiza el subarreglo A[p..r] de manera que todos los elementos
 * menores o iguales al pivote queden a la izquierda y los mayores a la derecha.
 */
int Ordenador::partition(int *A, int p, int r) const{
  int x = A[r]; //selecciona el ultimo elemento como pivote
  int i = p - 1; // i marca la posicion donde termina el subarreglo de elementos que son menores o iguales que el pivote
  for(int j = p; j < r; ++j){ //recorre todos los elementos desde p hasta r-1
    if(A[j] <= x){ //si el elemento es menor o igual al pivote expande el subarreglo izquierdo
      i = i+1;
      std::swap(A[i], A[j]); //coloca el elemento en la parte izquierda
    }
  }
  std::swap(A[i+1], A[r]); //coloca el pivote en su posicion correcta
  return i+1; // retorna posicion final
}

/**
 * @brief Función de partición con estrategia de mediana de 3
 * 
 * Utiliza la mediana de tres elementos (primero, medio, último) como pivote
 * para mejorar el rendimiento en casos donde el arreglo está parcialmente ordenado.
 */
int Ordenador::partitionV2(int *A, int p, int r) const{
    // Aplicar mediana de tres
    if (r - p >= 2) {
        int mid = p + (r - p) / 2;
        
        // Ordenar los tres elementos de referencia
        if (A[mid] < A[p]) {
            std::swap(A[p], A[mid]);
        }
        if (A[r] < A[p]) {
            std::swap(A[p], A[r]);
        }
        if (A[r] < A[mid]) {
            std::swap(A[mid], A[r]);
        }
        
        // Colocar la mediana al final como pivote
        std::swap(A[mid], A[r]);
    }
    
    // Partition normal con el pivote seleccionado
    int x = A[r];
    int i = p - 1;
    for(int j = p; j < r; ++j){
        if(A[j] <= x){
            i = i+1;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i+1], A[r]);
    return i+1;
}

/**
 * @brief Implementación recursiva de QuickSort con mediana de 3
 * 
 * Versión mejorada de QuickSort que utiliza la estrategia de mediana de 3
 * para la selección del pivote, reduciendo la probabilidad del peor caso.
 */
void Ordenador::rapidoRecursivoV2(int *A, int p, int r) const {
    if(p < r){
        int q = partitionV2(A, p, r);  // Usa la versión V2
        rapidoRecursivoV2(A, p, q-1);
        rapidoRecursivoV2(A, q+1, r);
    }
}

/**
 * @brief Método público que implementa QuickSort con selección adaptativa de estrategia
 * 
 * Si el primer elemento es par, usa QuickSort con mediana de 3.
 * Si el primer elemento es impar, usa QuickSort estándar.
 */
void Ordenador::ordenamientoRapido(std::uint32_t *A, std::uint32_t n) const{
  // Casting seguro para trabajar internamente con int
   if (A[0] % 2 == 0) { //esta parte es que si el numero del primer elemento del array es par utiliza mediana de 3
        rapidoRecursivoV2(reinterpret_cast<int*>(A), 0, static_cast<int>(n-1));
    } else { //sino, utiliza el quicksort estandar
        rapidoRecursivo(reinterpret_cast<int*>(A), 0, static_cast<int>(n-1));
    }
}

/**
 * @brief Implementación del algoritmo Radix Sort
 * 
 * Ordena los números procesando cada dígito desde el menos significativo
 * hasta el más significativo, utilizando Counting Sort como subrutina estable.
 */
void Ordenador::ordenamientoPorResiduos(std::uint32_t *A, std::uint32_t n) const{
  std::uint32_t max = getMax(A,n); //Encontrar el numero maximo y sacar cuantos digitos se deben procesar
  for(std::uint32_t exp = 1; max/exp > 0; exp*=10){ //Hacer counting sort para cada digito, y el exp es 10^i, i siendo el digito actual
    countingSort(A,n,exp);
  }
}


/**
 * @brief Implementación de Counting Sort para un dígito específico
 * 
 * Ordena el arreglo basándose en el dígito especificado por el exponente,
 * manteniendo la estabilidad necesaria para Radix Sort.
 */
void Ordenador::countingSort(std::uint32_t *A, std::uint32_t n, std::uint32_t exp) const{
    // Arreglo de salida
    std::uint32_t *output = new std::uint32_t[n];
    
    // Arreglo de conteo para dígitos 0-9
    std::uint32_t count[10] = {0};
    
    // Contar ocurrencias de cada dígito
    for (std::uint32_t i = 0; i < n; i++) {
        std::uint32_t digit = (A[i] / exp) % 10;
        count[digit]++;
    }
    
    // Cambiar count[i] para que contenga la posición real del dígito
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Construir el arreglo de salida (de derecha a izquierda para mantener estabilidad)
    for (int i = n - 1; i >= 0; i--) {
        std::uint32_t digit = (A[i] / exp) % 10;
        output[count[digit] - 1] = A[i];
        count[digit]--;
    }
    
    // Copiar el arreglo de salida de vuelta al arreglo original
    for (std::uint32_t i = 0; i < n; i++) {
        A[i] = output[i];
    }
    
    // Liberar memoria
    delete[] output;
}

/**
 * @brief Encuentra el valor máximo en el arreglo
 * 
 * Recorre todo el arreglo para determinar el elemento con mayor valor,
 * necesario para calcular el número de dígitos en Radix Sort.
 */
std::uint32_t Ordenador::getMax(std::uint32_t *A, std::uint32_t n) const{
  // Inicializa la variable max con el primer elemento del arreglo
  std::uint32_t max = A[0];
  for(std::uint32_t i = 1; i<n; ++i){
    if(A[i] > max){ //revisa el elemento actual con el valor maximo hasta ahora
      max = A[i]; //si el elemento actual es mayor, actualiza el maximo
    }
  }
  return max;
}
