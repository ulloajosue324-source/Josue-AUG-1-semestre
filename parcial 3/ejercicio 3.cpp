#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream archivo("alumnos.txt", ios::app);

    if (!archivo) {
        cout << "Error al abrir el archivo";
        return 1;
    }

    archivo << "Luis 004 9 8 10 2" << endl;

    archivo.close();

    cout << "Alumno agregado correctamente";

    return 0;
}