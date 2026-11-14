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
    Alumno alumnos[100];
    ifstream archivo("alumnos.txt");

    if (!archivo) {
        cout << "No se pudo abrir el archivo";
        return 1;
    }

    int n = 0;

    while (archivo >> alumnos[n].nombre
                   >> alumnos[n].matricula
                   >> alumnos[n].calif[0]
                   >> alumnos[n].calif[1]
                   >> alumnos[n].calif[2]
                   >> alumnos[n].grupo && n < 100) {
        n++;
    }

    archivo.close();

    for (int i = 0; i < n; i++) {
        cout << "\nNombre: " << alumnos[i].nombre;
        cout << "\nMatricula: " << alumnos[i].matricula;
        cout << "\nGrupo: " << alumnos[i].grupo;
        cout << "\nPromedio: "
             << (alumnos[i].calif[0] + alumnos[i].calif[1] +
                 alumnos[i].calif[2]) / 3 << endl;
    }

    return 0;
}