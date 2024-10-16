#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string> // Incluir esta biblioteca para usar to_string
using namespace std;

// Renombrando el tipo de dato para las aristas (costo, nodo)
typedef pair<int, int> Arista; 
const int INFINITO = numeric_limits<int>::max(); // Representación de infinito para los costos de caminos no existentes

// Función que implementa el algoritmo de Dijkstra
void dijkstra(int inicio, vector<vector<Arista>>& grafo, vector<int>& capacidades) {
    int numNodos = grafo.size(); // Número de nodos en el grafo
    vector<int> dist(numNodos, INFINITO); // Vector de distancias inicializado a infinito
    dist[inicio] = 0; // Distancia del nodo inicial a sí mismo es 0
    priority_queue<Arista, vector<Arista>, greater<Arista>> colaPrioridad; // Cola de prioridad para seleccionar el siguiente nodo con el menor costo
    colaPrioridad.push({0, inicio}); // Insertar el nodo inicial en la cola

    while (!colaPrioridad.empty()) {
        int costoActual = colaPrioridad.top().first; // Costo acumulado hasta el nodo actual
        int nodoActual = colaPrioridad.top().second; // Nodo actual
        colaPrioridad.pop(); // Remover el nodo de la cola

        // Si la distancia almacenada no coincide, continuamos
        if (costoActual != dist[nodoActual]) continue;

        // Iterar sobre todos los vecinos del nodo actual
        for (auto& arista : grafo[nodoActual]) {
            int nodoVecino = arista.second; // Nodo vecino
            int costoBase = arista.first; // Costo de la arista

            // Penalización basada en la capacidad relativa del nodo
            int capacidadMaxima = 50; // Ajustando según el nodo con mayor capacidad
            int porcentajeUtilizacion = (capacidades[nodoActual] * 100) / capacidadMaxima;
            int penalizacionCapacidad = (porcentajeUtilizacion < 20) ? 10 : (porcentajeUtilizacion < 40) ? 5 : 0; // Penalización según la utilización

            int costoTotal = costoBase + penalizacionCapacidad; // Costo total considerando la penalización

            // Si encontramos una ruta más corta al nodo vecino
            if (dist[nodoActual] + costoTotal < dist[nodoVecino]) {
                dist[nodoVecino] = dist[nodoActual] + costoTotal; // Actualizar la distancia
                colaPrioridad.push({dist[nodoVecino], nodoVecino}); // Añadir el nodo vecino a la cola
            }
        }
    }

    // Imprimir las distancias desde el nodo inicial al resto de nodos
    for (int i = 0; i < numNodos; ++i) {
        cout << "Distancia desde " << inicio + 1 << " a " << i + 1 << " es " << (dist[i] == INFINITO ? "INFINITO" : to_string(dist[i])) << endl;
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
    vector<int> capacidades = {10, 20, 0, 40, 30, 5, 15}; // Ejemplo de capacidades de los nodos

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
