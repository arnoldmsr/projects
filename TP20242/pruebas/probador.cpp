#include <iostream>         // Biblioteca para entrada y salida estándar
#include <fstream>          // Biblioteca para operaciones de archivos
#include <vector>           // Biblioteca para utilizar el contenedor vector
#include <string>           // Biblioteca para utilizar el contenedor string
#include <algorithm>        // Biblioteca para funciones de algoritmos como transform
#include <map>              // Incluir la biblioteca map
#include <locale>
#include <codecvt>

using namespace std;

map<char32_t, int> crearMapa() {
    map<char32_t, int> mapa;
    u32string caracteres = U"AaÁáBbCcDdEeÉéFfGgHhIiÍíJjKkLlMmNnÑñOoÓóPpQqRrSsTtUuÚúVvWwXxYyZz";
    for (int i = 0; i < caracteres.size(); ++i) {
        mapa[caracteres[i]] = i;
    }
    return mapa;
}

bool comparacionManual(const u32string &a, const u32string &b, const map<char32_t, int> &mapa) {
    size_t minLength = min(a.size(), b.size());
    for (size_t i = 0; i < minLength; ++i) {
        if (mapa.at(a[i]) != mapa.at(b[i])) {
            return mapa.at(a[i]) > mapa.at(b[i]);
        }
    }
    return a.size() > b.size();
}

vector<u32string> leerArchivo(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<u32string> palabras;
    wstring_convert<codecvt_utf8<char32_t>, char32_t> convert;
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            palabras.push_back(convert.from_bytes(linea));
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    return palabras;
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");

    string nombreArchivo = "C:\\Users\\Arnoldmsr\\projects\\TP20242\\palabras.txt";
    vector<u32string> palabras = leerArchivo(nombreArchivo);
    map<char32_t, int> mapa = crearMapa();

    sort(palabras.begin(), palabras.end(), [&](const u32string &a, const u32string &b) {
        return comparacionManual(a, b, mapa);
    });

    cout << "Palabras ordenadas de Z a A:" << endl;
    wstring_convert<codecvt_utf8<char32_t>, char32_t> convert;
    for (const u32string &palabra : palabras) {
        cout << convert.to_bytes(palabra) << endl;
    }

    return 0;
}
