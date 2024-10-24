#include <iostream>         // Biblioteca para entrada y salida estándar
#include <fstream>          // Biblioteca para operaciones de archivos
#include <vector>           // Biblioteca para utilizar el contenedor vector
#include <string>           // Biblioteca para utilizar el contenedor string
#include <algorithm>        // Biblioteca para funciones de algoritmos como transform
// Incluir la biblioteca unordered_map #include <unordered_map>    

using namespace std;

// Función para convertir una cadena a minúsculas y normalizar caracteres
string normalizar(const string& str) {
    string resultado;
    for (char c : str) {
        switch (c) {
            case 'á': case 'Á': resultado += 'a'; break;
            case 'é': case 'É': resultado += 'e'; break;
            case 'í': case 'Í': resultado += 'i'; break;
            case 'ó': case 'Ó': resultado += 'o'; break;
            case 'ú': case 'Ú': resultado += 'u'; break;
            case 'ü': case 'Ü': resultado += 'u'; break;
            default: resultado += tolower(c); break;
        }
    }
    return resultado;
}

// Función de comparación para ordenar según el alfabeto español, incluyendo caracteres con acentos y diéresis
bool compareCastellano(const string& a, const string& b) {
    return normalizar(a) > normalizar(b);
}

// Función iterativa para ordenar un vector de palabras utilizando Quicksort
void ordenarapido(vector<string>& palabras, vector<string>& originales) {
    vector<pair<int, int>> stack;
    stack.push_back({0, palabras.size() - 1});

    while (!stack.empty()) {
        int inicio = stack.back().first;
        int fin = stack.back().second;
        stack.pop_back();

        if (inicio >= fin) continue;

        string pivote = palabras[fin];
        string pivoteOriginal = originales[fin];
        int i = inicio - 1;

        for (int j = inicio; j < fin; ++j) {
            if (compareCastellano(palabras[j], pivote)) {
                ++i;
                swap(palabras[i], palabras[j]);
                swap(originales[i], originales[j]);
            }
        }

        swap(palabras[i + 1], palabras[fin]);
        swap(originales[i + 1], originales[fin]);
        int p = i + 1;

        stack.push_back({inicio, p - 1});
        stack.push_back({p + 1, fin});
    }
}

int main() {
    // Nombre del archivo
    string nombreArchivo = "palabras.txt";
    ifstream archivo(nombreArchivo);

    // Verificar si se pudo abrir el archivo
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return 1;
    }

    vector<string> palabras;
    vector<string> originales;
    string palabra;

    // Leer las palabras del archivo y almacenarlas en los vectores
    while (getline(archivo, palabra)) {
        originales.push_back(palabra); // Almacenar la palabra original
        palabras.push_back(normalizar(palabra)); // Almacenar la palabra normalizada
    }

    // Cerrar el archivo
    archivo.close();

    // Ordenar las palabras de la Z a la A usando Quicksort iterativo y la comparación personalizada
    ordenarapido(palabras, originales);

    // Imprimir las palabras originales ordenadas
    cout << "Lista de palabras ordenadas de la Z a la A:" << endl;
    for (const auto& p : originales) {
        cout << p << endl;
    }

    return 0;
}