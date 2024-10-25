#include <iostream>         // Biblioteca para entrada y salida estándar
#include <fstream>          // Biblioteca para operaciones de archivos
#include <vector>           // Biblioteca para utilizar el contenedor vector
#include <string>           // Biblioteca para utilizar el contenedor string
#include <algorithm>        // Biblioteca para funciones de algoritmos como transform
#include <unordered_map>    // Incluir la biblioteca unordered_map

using namespace std;

// Mapa para normalizar cracteres acentuados
static unordered_map<char, char> mapaAcentos = {
    {'á', 'a'}, {'é', 'e'}, {'í', 'i'},
    {'ó', 'o'}, {'ú', 'u'}, {'ü', 'u'},
    {'Á', 'A'}, {'É', 'E'}, {'Í', 'I'},
    {'Ó', 'O'}, {'Ú', 'U'}, {'Ü', 'U'}
};

// Función para reemplazar caracteres acentuados por normales
string normalizar(const string& palabra, const unordered_map<char, char>& mapaAcentos) {
    string normalizada;
    for (char c : palabra) {
        if (mapaAcentos.find(c) != mapaAcentos.end()) {
            normalizada += mapaAcentos.at(c);
        } else {
            normalizada += c;
        }
    }
    return normalizada;
}

// Función para convertir una palabra en mayúsculas, manejando 'ñ' y 'Ñ' usando valores ASCII
string mayusculas(const string& str) {
    string resultado;
    for (char c : str) {
        int letra = static_cast<int>(c);
        if (letra == 241) { // Código ASCII para 'ñ'
            resultado += static_cast<char>(209); // ASCII code for 'Ñ'
        } else if (letra == 164) { // Código ASCII para 'Ñ' en algunas codificaciones
            resultado += 'Ñ';
        } else {
            resultado += toupper(static_cast<unsigned char>(c));
        }
    }
    return resultado;
}

int main() {
    // Nombre del archivo
    // string nombreArchivo = "C:\\Users\\Arnoldmsr\\projects\\TP20242\\palabras.txt";
    // ifstream archivo(nombreArchivo);

    // Verificar si se pudo abrir el archivo
    //if (!archivo) {
        //cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        //return 1;
    //}

    //vector<string> palabras;
    //vector<string> originales;
    string palabra="Baño";
    string pOriginal= palabra;
    string normalizada = normalizar(palabra, mapaAcentos);
    string caps = mayusculas(normalizada);
    palabra= caps;
    // Leer las palabras del archivo y almacenarlas en los vectores
    //while (getline(archivo, palabra)) {
        //originales.push_back(palabra);                          // Almacenar la palabra original
        // string normalizada = normalizar(palabra, mapaAcentos);  // Almacenar palabra normalizada
        //string caps = mayusculas(normalizada);                  // Almacenar palabra mayúscula
        //palabras.push_back(caps);
    //}

    // Cerrar el archivo
    //archivo.close(); 
    // Imprimir las palabras normalizadas ordenadas
    //cout << "Lista de palabras en mayúsculas:" << endl;
    //for (const auto& p : palabras) {
        //cout << p << endl;
    //}
    cout << "palabra en mayúsculas:" << endl;
    cout << palabra << endl;
    return 0;
}
