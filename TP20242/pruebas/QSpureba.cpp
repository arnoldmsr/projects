#include <iostream>
#include <locale>
using namespace std;
int main() {
    // Obtener la configuración local actual
    locale loc("es_ES");

    // Imprimir la configuración local
    cout << "Configuración local actual: " << loc.name() << endl;

    return 0;
}