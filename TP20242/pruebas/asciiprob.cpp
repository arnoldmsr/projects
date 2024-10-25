#include <iostream>         // Biblioteca para entrada y salida estándar
using namespace std;
int ascii (char car){
  int valorASCII=car;
  return valorASCII;
}
int main(){
  cout<< ascii('ñ') << endl;
  cout<< ascii('Ñ')<<endl;
  cout<< ascii('A')<<endl;
  cout<< ascii('Á')<<endl;
  cout<< ascii('á')<<endl;
  cout<< ascii('é')<<endl;
  cout<< ascii('É')<<endl;
  cout<< ascii('í')<<endl;
  cout<< ascii('Í')<<endl;
  cout<< ascii('ó')<<endl;
  cout<< ascii('Ó')<<endl;
  cout<< ascii('ú')<<endl;
  cout<< ascii('Ú')<<endl;
  cout<< ascii('ü')<<endl;
  cout<< ascii('Ü')<<endl;
  return 0;
}