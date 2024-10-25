#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <locale>
#include <codecvt>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/locale.hpp>

using namespace std;
using namespace boost::locale;

// Función para leer las palabras desde el archivo
vector<string> leerArchivo(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<string> palabras;
    string palabra;

    if (archivo.is_open()) {
        while (getline(archivo, palabra)) {
            palabras.push_back(palabra);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    return palabras;
}

int main() {
    // Nombre del archivo
    string nombreArchivo = "palabras.txt";

    // Leer las palabras del archivo
    vector<string> palabras = leerArchivo(nombreArchivo);

    // Inicializar la biblioteca locale
    generator gen;
    locale loc = gen("es_ES.UTF-8");
    locale::global(loc);
    cout.imbue(loc);

    // Ordenar las palabras de Z a A usando boost::locale
    sort(palabras.begin(), palabras.end(), loc);
    reverse(palabras.begin(), palabras.end());

    // Imprimir las palabras ordenadas
    cout << "Palabras ordenadas de Z a A:" << endl;
    for (const string &palabra : palabras) {
        cout << palabra << endl;
    }

    return 0;
}
