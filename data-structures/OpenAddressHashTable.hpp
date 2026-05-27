#pragma once
#include <cstdint>
#include <vector>

// Valores especiales para marcadores (definidos aqui para evitar problemas de linkeo)
/** @def HASH_EMPTY
 * @brief Marcador para un slot vacío (nunca usado).
 */
#define HASH_EMPTY -1
/** @def HASH_DELETED
 * @brief Marcador para un slot que tuvo un elemento y fue borrado.
 */
#define HASH_DELETED -2
/** @def HASH_WEYL_SEQUENCE
 * @brief Constante (Secuencia de Weyl) usada en la función hash h1 (Middle-Squared).
 */
#define HASH_WEYL_SEQUENCE 0xB5AD4ECEDA1CE2A9ULL

/**
 * @class OpenAddressHashTable
 * @brief Plantilla para una Tabla Hash con Direccionamiento Abierto (Open Addressing).
 * @tparam DataType El tipo de dato a almacenar. Se asume que puede ser
 * convertido a `uint32_t` para el hashing y que
 * `HASH_EMPTY` y `HASH_DELETED` son valores reservados.
 */
template <typename DataType>
class OpenAddressHashTable {
 public:
  /**
   * @brief Constructor.
   * @param size El tamaño (m) de la tabla hash.
   */
  OpenAddressHashTable(size_t size) : size(size), table(size, HASH_EMPTY), numElements(0) {
    // Inicializar toda la tabla con el marcador EMPTY
  }

  /**
   * @brief Destructor.
   */
  ~OpenAddressHashTable() {}

  /**
   * @brief Inserta un valor en la tabla.
   * @details No permite duplicados ni valores reservados (EMPTY, DELETED).
   * Si la tabla está llena, no inserta.
   * Utiliza sondeo por doble hashing para encontrar un slot.
   * @param value El valor a insertar.
   */
  void insert(const DataType& value) {
    // No permitir insertar valores reservados
    if (value == HASH_EMPTY || value == HASH_DELETED) {
      return;
    }

    // No permitir duplicados
    if (search(value) != static_cast<size_t>(-1)) {
      return;
    }

    // Verificar si hay espacio
    if (numElements >= size) {
      return;
    }

    // Buscar un slot vacio o DELETED usando h(k,i)
    for (size_t i = 0; i < size; i++) {
      size_t index = hashFunction(value, i);
      
      // Si esta vacio o marcado como DELETED, insertar aqui
      if (table[index] == HASH_EMPTY || table[index] == HASH_DELETED) {
        table[index] = value;
        numElements++;
        return;
      }
    }
  }

  /**
   * @brief Busca un valor en la tabla.
   * @details Sigue la secuencia de sondeo. Se detiene si encuentra el valor
   * o si encuentra un slot `HASH_EMPTY` (nunca usado).
   * @param value El valor a buscar.
   * @return El índice donde se encuentra el valor, o `static_cast<size_t>(-1)` 
   * (equivalente a -1 pero sin signo) si no se encuentra.
   */
  size_t search(const DataType& value) const {
    // No buscar valores reservados
    if (value == HASH_EMPTY || value == HASH_DELETED) {
      return static_cast<size_t>(-1);
    }

    // Sondear hasta encontrar el valor o un slot vacio
    for (size_t i = 0; i < size; i++) {
      size_t index = hashFunction(value, i);
      
      // Si encontramos el valor, retornar indice
      if (table[index] == value) {
        return index;
      }
      
      // Si encontramos un slot vacio (nunca usado), el elemento no existe
      if (table[index] == HASH_EMPTY) {
        return static_cast<size_t>(-1);
      }
      
      // Si esta DELETED, seguir buscando
    }
    
    return static_cast<size_t>(-1);
  }

  /**
   * @brief Elimina un valor de la tabla.
   * @details Busca el valor y, si lo encuentra, marca el slot como `HASH_DELETED`.
   * @param value El valor a eliminar.
   */
  void remove(const DataType& value) {
    size_t index = search(value);
    
    // Si encontramos el elemento, marcarlo como DELETED
    if (index != static_cast<size_t>(-1)) {
      table[index] = HASH_DELETED;
      numElements--;
    }
  }

  /**
   * @brief Obtiene el tamaño total (capacidad) de la tabla.
   * @return El tamaño 'm' de la tabla.
   */
  size_t getSize() const {
    return size;
  }

 private:
  size_t size; /**< @brief Capacidad total de la tabla (m). */
  std::vector<DataType> table; /**< @brief El vector que almacena los datos. */
  size_t numElements; /**< @brief Contador de elementos actualmente en la tabla. */

  /**
   * @brief Primera función hash (h1) usando el método "Middle-Squared".
   * @details Pasos: 
   * 1. Convierte 'value' a uint32_t (k).
   * 2. Calcula k^2 (uint64_t).
   * 3. Suma la secuencia de Weyl.
   * 4. Extrae los 20 bits centrales del resultado de 64 bits.
   * 5. Aplica módulo 'size' (m) al resultado.
   * @param value El valor (clave) a hashear.
   * @return Un índice en el rango [0, m-1].
   */
  // h1(k): Middle-Squared Method (segun especificacion del PDF)
  // Pasos: k^2, sumar Weyl, extraer 20 bits centrales
  size_t h1(const DataType& value) const {
    // 1. Convertir a uint32_t
    uint32_t k = static_cast<uint32_t>(value);
    
    // 2. Elevar al cuadrado (resultado es uint64_t)
    uint64_t k_squared = static_cast<uint64_t>(k) * static_cast<uint64_t>(k);
    
    // 3. Sumar secuencia de Weyl
    uint64_t k_prime = k_squared + HASH_WEYL_SEQUENCE;
    
    // 4. Extraer los 20 bits centrales
    // De 64 bits, desplazar 22 bits a la derecha y aplicar mascara de 20 bits
    uint64_t middle_bits = (k_prime >> 22) & 0xFFFFF;
    
    // 5. Asegurar que este en rango [0, m-1]
    return static_cast<size_t>(middle_bits % size);
  }

  /**
   * @brief Segunda función hash (h2) para Double Hashing.
   * @details Fórmula: h2(k) = 1 + (k mod (m-1)).
   * Esto garantiza que h2(k) nunca sea 0, lo cual es crucial
   * para que el sondeo visite toda la tabla (si m es primo).
   * @param value El valor (clave) a hashear.
   * @return Un valor en el rango [1, m-1].
   */
  // h2(k): Segunda funcion hash para Double Hashing
  // h2(k) = 1 + (k mod (m-1))
  // Garantiza: 1 <= h2(k) <= m-1 (nunca es 0)
  size_t h2(const DataType& value) const {
    uint32_t k = static_cast<uint32_t>(value);
    return 1 + (k % (size - 1));
  }

  /**
   * @brief Función de sondeo completa para Double Hashing.
   * @details Fórmula: h(k, i) = (h1(k) + i * h2(k)) mod m.
   * @param value La clave 'k'.
   * @param i El número de intento (índice de sondeo).
   * @return El índice de la tabla a probar.
   */
  // Funcion hash con Double Hashing: h(k,i) = (h1(k) + i*h2(k)) mod m
  size_t hashFunction(const DataType& value, size_t i) const {
    return (h1(value) + i * h2(value)) % size;
  }

  // Metodos auxiliares privados

  /**
   * @brief Cuenta el número total de colisiones.
   * @details Una colisión se cuenta si un elemento no está en su
   * posición "ideal" calculada por h1(k).
   * @return El número de elementos que no están en su slot h1.
   */
  // Cuenta el total de colisiones
  size_t countCollisions() const {
    size_t collisions = 0;
    
    for (size_t i = 0; i < size; i++) {
      if (table[i] != HASH_EMPTY && table[i] != HASH_DELETED) {
        // Si el elemento no esta en su posicion ideal h1(k), es colision
        size_t idealPos = h1(table[i]);
        if (idealPos != i) {
          collisions++;
        }
      }
    }
    
    return collisions;
  }

  /**
   * @brief Obtiene el número de elementos almacenados.
   * @return El valor de `numElements`.
   */
  // Cuenta el total de elementos
  size_t countElements() const {
    return numElements;
  }

  /**
   * @brief Calcula el factor de carga (alpha) de la tabla.
   * @details Fórmula: alpha = n / m (numElements / size).
   * @return El factor de carga como un valor double.
   */
  // Calcula el factor de carga
  double getLoadFactor() const {
    return static_cast<double>(numElements) / static_cast<double>(size);
  }
};
