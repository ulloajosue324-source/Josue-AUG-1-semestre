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
        {"Josue", "1", {8, 9, 10}, 1},
        {"Pedro", "2", {7, 8, 9}, 2},
        {"juanito", "3", {10, 9, 10}, 1}
    };

    ofstream archivo("alumnos.txt");

    if (archivo) {
        for (int i = 0; i < 3; i++) {
            archivo << alumnos[i].nombre << " "
                    << alumnos[i].matricula << " "
                    << alumnos[i].calif[0] << " "
                    << alumnos[i].calif[1] << " "
                    << alumnos[i].calif[2] << " "
                    << alumnos[i].grupo << endl;
        }
        
        archivo.close();
        cout << "Alumnos guardados.";
    } else {
        cout << "No se pudo abrir el archivo.";
    }

    return 0;

    Alumno leidos[100];
int cantidad = 0;

ifstream archivoLeer("alumnos.txt");

if (archivoLeer.is_open()) {
    while (archivoLeer >> leidos[cantidad].nombre
                       >> leidos[cantidad].matricula
                       >> leidos[cantidad].calif[0]
                       >> leidos[cantidad].calif[1]
                       >> leidos[cantidad].calif[2]
                       >> leidos[cantidad].grupo) {
        cantidad++;
    }

    archivoLeer.close();

    for (int i = 0; i < cantidad; i++) {
        cout << leidos[i].nombre << " "
             << leidos[i].matricula << " "
             << leidos[i].calif[0] << " "
             << leidos[i].calif[1] << " "
             << leidos[i].calif[2] << " "
             << leidos[i].grupo << endl;
    }
}
else {
    cout << "Error al abrir archivo.";
}
}