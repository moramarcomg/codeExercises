#include "Ordenador.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std::chrono;

void generarDatosRandom(std::uint32_t *A, std::uint32_t length) {
    for (std::uint32_t p = 0; p < length; p++) {
        A[p] = rand() % 100000;
    }
}

void copiarArreglo(std::uint32_t* origen, std::uint32_t* destino, std::uint32_t n) {
    for(std::uint32_t i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

int main() {
    srand(42); // Semilla fija para reproducibilidad
    
    Ordenador sortObj;
    std::uint32_t arraySizes[] = {1000, 10000, 100000, 1000000};
    const int iterations = 3;
    
    std::ofstream file("resultados_todos_algoritmos.txt");
    std::cout << "=== PRUEBA TODOS LOS ALGORITMOS ===\n";
    std::cout << sortObj.imprimirDatosDeTarea() << "\n\n";
    
    for (int t = 0; t < 4; t++) {
        std::uint32_t arraySize = arraySizes[t];
        std::cout << "Procesando array size: " << arraySize << " elementos...\n";
        file << "Tamaño de array: " << arraySize << std::endl;
        
        // Generar UN array base para este tamaño
        std::uint32_t *arrayOriginal = new std::uint32_t[arraySize];
        std::uint32_t *arrayTrabajo = new std::uint32_t[arraySize];
        generarDatosRandom(arrayOriginal, arraySize);
        
        // Probar cada algoritmo 3 veces con EL MISMO array
        std::string algoritmos[] = {"Seleccion", "Insercion", "Mezcla", "Monticulos", "Rapido", "Residuos"};
        
        for (int alg = 0; alg < 6; alg++) {
            std::cout << "  " << algoritmos[alg] << ":\n";
            file << "Algoritmo: " << algoritmos[alg] << std::endl;
            
            for (int iter = 0; iter < iterations; iter++) {
                // COPIAR el mismo array original
                copiarArreglo(arrayOriginal, arrayTrabajo, arraySize);
                
                auto startTime = high_resolution_clock::now();
                
                // Llamar al algoritmo correspondiente
                switch(alg) {
                    case 0: sortObj.ordenamientoPorSeleccion(arrayTrabajo, arraySize); break;
                    case 1: sortObj.ordenamientoPorInserccion(arrayTrabajo, arraySize); break;
                    case 2: sortObj.ordenamientoPorMezcla(arrayTrabajo, arraySize); break;
                    case 3: sortObj.ordenamientoPorMonticulos(arrayTrabajo, arraySize); break;
                    case 4: sortObj.ordenamientoRapido(arrayTrabajo, arraySize); break;
                    case 5: sortObj.ordenamientoPorResiduos(arrayTrabajo, arraySize); break;
                }
                
                auto endTime = high_resolution_clock::now();
                auto executionTime = duration<double, std::milli>(endTime - startTime);
                
                // Validar ordenamiento
                bool validSort = true;
                std::uint32_t pos = 1;
                while (pos < arraySize && validSort) {
                    if (arrayTrabajo[pos] < arrayTrabajo[pos-1]) {
                        validSort = false;
                    }
                    pos++;
                }
                
                std::cout << "    Corrida " << (iter+1) << ": " << executionTime.count() << " ms - ";
                if (validSort) {
                    std::cout << "CORRECTO\n";
                } else {
                    std::cout << "ERROR\n";
                }
                
                file << "  Corrida " << (iter+1) << ": " << executionTime.count() 
                     << " ms - " << (validSort ? "CORRECTO" : "ERROR") << std::endl;
            }
            file << std::endl;
        }
        
        delete[] arrayOriginal;
        delete[] arrayTrabajo;
        std::cout << std::endl;
        file << std::endl;
    }
    
    file.close();
    std::cout << "=== PRUEBA FINALIZADA ===\n";
    return 0;
}