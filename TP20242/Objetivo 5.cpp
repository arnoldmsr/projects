#include <iostream>
#include <vector>
#include <queue>
#include <stack> // Para reconstruir las rutas
#include <string> // Incluir esta biblioteca para usar to_string
#include <limits>
using namespace std;

// Renombrando el tipo de dato para las aristas (costo, nodo)
typedef pair<int, int> Arista;  // Define un tipo de dato para las aristas (costo, nodo) 
const int INFINITO = numeric_limits<int>::max(); // Representación de infinito para los costos de caminos no existentes

// Función que implementa el algoritmo de Dijkstra
void dijkstra(int inicio, vector<vector<Arista>>& grafo, vector<int>& capacidades) {
    int numNodos = grafo.size(); // Número de nodos en el grafo
    vector<int> distancias(numNodos, INFINITO); // Vector de distancias inicializado a infinito
    vector<int> predecesores(numNodos, -1); // Vector de predecesores para reconstruir las rutas
    distancias[inicio] = 0; // Distancia del nodo inicial a sí mismo es 0
    priority_queue<Arista, vector<Arista>, greater<Arista>> colaPrioridad; // Cola de prioridad para seleccionar el siguiente nodo con el menor costo
    colaPrioridad.push({0, inicio}); // Insertar el nodo inicial en la cola

    while (!colaPrioridad.empty()) {
        int costoActual = colaPrioridad.top().first; // Costo acumulado hasta el nodo actual
        int nodoActual = colaPrioridad.top().second; // Nodo actual
        colaPrioridad.pop(); // Remover el nodo de la cola

        if (costoActual != distancias[nodoActual]) continue; // Si la distancia almacenada no coincide, continuamos
        
        // Iterar sobre todos los vecinos del nodo actual
        for (auto& arista : grafo[nodoActual]) {
            int nodoVecino = arista.second; // Nodo vecino
            int costoBase = arista.first; // Costo de la arista
            
            // Penalización basada en la capacidad relativa del nodo
            int capacidadMaxima = 10; // Ejemplo de capacidad máxima teórica
            int porcentajeUtilizacion = (capacidades[nodoActual] * 100) / capacidadMaxima;
            int penalizacionCapacidad = (porcentajeUtilizacion < 50) ? 10 : 0; // Penalización alta si la utilización es baja
            int costoTotal = costoBase + penalizacionCapacidad; // Costo total considerando la penalización
            
            // Si encontramos una ruta más corta al nodo vecino
            if (distancias[nodoActual] + costoTotal < distancias[nodoVecino]) {
                distancias[nodoVecino] = distancias[nodoActual] + costoTotal; // Actualizar la distancia
                predecesores[nodoVecino] = nodoActual; // Registrar el predecesor
                colaPrioridad.push({distancias[nodoVecino], nodoVecino}); // Añadir el nodo vecino a la cola
            }
        }
    }

    // Imprimir las distancias desde el nodo inicial al resto de nodos
    for (int i = 0; i < numNodos; ++i) {
        cout << "Distancia desde " << inicio + 1 << " a " << i + 1 << " es " << (distancias[i] == INFINITO ? "INFINITO" : to_string(distancias[i])) << endl;
        // Imprimir la ruta
        if (distancias[i] != INFINITO) {
            stack<int> ruta;
            for (int at = i; at != -1; at = predecesores[at]) {
                ruta.push(at + 1);
            }
            cout << "Ruta: ";
            while (!ruta.empty()) {
                cout << ruta.top();
                ruta.pop();
                if (!ruta.empty()) cout << " -> ";
            }
            cout << endl;
        }
    }
}

int main() {
    int numNodos = 7; // Número de nodos en el grafo
    vector<vector<Arista>> grafo(numNodos); // Lista de adyacencia para representar el grafo

    // Definimos la matriz de costos
    vector<vector<int>> costos = {
        {0, INFINITO, 3, 4, 1, INFINITO, INFINITO},
        {2, 0, 2, 3, INFINITO, INFINITO, INFINITO},
        {2, 4, 0, INFINITO, 2, 1, INFINITO},
        {1, 1, INFINITO, 0, INFINITO, 1, INFINITO},
        {INFINITO, INFINITO, 1, INFINITO, 0, INFINITO, 1},
        {INFINITO, INFINITO, INFINITO, 2, INFINITO, 0, 1},
        {INFINITO, INFINITO, INFINITO, INFINITO, INFINITO, 1, 0}
    };

    // Definiendo las capacidades de los nodos
    vector<int> capacidades = {10, 2, 0, 8, 6, 1, 3}; // Ejemplo de capacidades de los nodos

    // Construyendo la lista de adyacencia a partir de la matriz de costos
    for (int i = 0; i < numNodos; ++i) {
        for (int j = 0; j < numNodos; ++j) {
            if (costos[i][j] != INFINITO && costos[i][j] != 0) { // Añadir solo aristas existentes
                grafo[i].push_back({costos[i][j], j});
            }
        }
    }

    dijkstra(0, grafo, capacidades); // Ejecutar Dijkstra desde el nodo inicial (0 equivalente a nodo 1)
    return 0;
}
