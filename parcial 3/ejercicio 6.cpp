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
    Alumno alumnos[100], aux;
    ifstream archivo("alumnos.txt");

    if (!archivo) {
        cout << "No se pudo abrir el archivo";
        return 1;
    }

    int n = 0;

    while (n < 100 && archivo >> alumnos[n].nombre
                              >> alumnos[n].matricula
                              >> alumnos[n].calif[0]
                              >> alumnos[n].calif[1]
                              >> alumnos[n].calif[2]
                              >> alumnos[n].grupo) {
        n++;
    }

    archivo.close();

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            float p1 = (alumnos[i].calif[0] + alumnos[i].calif[1] +
                        alumnos[i].calif[2]) / 3;

            float p2 = (alumnos[j].calif[0] + alumnos[j].calif[1] +
                        alumnos[j].calif[2]) / 3;

            if (p2 > p1) {
                aux = alumnos[i];
                alumnos[i] = alumnos[j];
                alumnos[j] = aux;
            }
        }
    }

    ofstream reporte("reporte.txt");

    for (int i = 0; i < n; i++) {
        float promedio = (alumnos[i].calif[0] +
                          alumnos[i].calif[1] +
                          alumnos[i].calif[2]) / 3;

        reporte << alumnos[i].nombre << " "
                << alumnos[i].matricula << " "
                << promedio << endl;
    }

    reporte.close();

    cout << "Reporte creado correctamente";

    return 0;
}