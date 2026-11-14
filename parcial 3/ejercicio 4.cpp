#include <iostream>
#include <fstream>
using namespace std;

struct Alumno {
    string nombre;
    string matricula;
    float calif[3];
    int grupo;
};

int main() {
    Alumno alumnos[3] = {
        {"Josue", "001", {9, 8, 10}, 1},
        {"Pedro", "002", {8, 9, 8}, 1},
        {"Juanito", "003", {10, 9, 9}, 2}
    };

    ofstream archivo("alumnos.dat", ios::binary);

    if (!archivo) {
        cout << "Error al crear el archivo";
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        int largo = alumnos[i].nombre.size();
        archivo.write((char*)&largo, sizeof(largo));
        archivo.write(alumnos[i].nombre.c_str(), largo);

        largo = alumnos[i].matricula.size();
        archivo.write((char*)&largo, sizeof(largo));
        archivo.write(alumnos[i].matricula.c_str(), largo);

        archivo.write((char*)alumnos[i].calif, sizeof(alumnos[i].calif));
        archivo.write((char*)&alumnos[i].grupo, sizeof(alumnos[i].grupo));
    }

    archivo.close();

    ifstream texto("alumnos.txt", ios::binary | ios::ate);
    ifstream binario("alumnos.dat", ios::binary | ios::ate);

    cout << "Tamano del archivo de texto: " << texto.tellg() << " bytes" << endl;
    cout << "Tamano del archivo binario: " << binario.tellg() << " bytes";

    return 0;
}