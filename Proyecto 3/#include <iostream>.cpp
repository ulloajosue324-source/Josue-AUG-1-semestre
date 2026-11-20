#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Alumno {
    string nombre, matricula;
    float calif[3];
    int grupo;
};

struct Maestro {
    string nombre, materia;
};

struct Grupo {
    string nombre, carrera;
};

Alumno alumnos[100];
Maestro maestros[100];
Grupo grupos[100];

int na = 0, nm = 0, ng = 0;

float promedio(Alumno a) {
    return (a.calif[0] + a.calif[1] + a.calif[2]) / 3;
}

void guardar() {
    ofstream archivo("alumnos.txt");

    archivo << na << endl;

    for (int i = 0; i < na; i++) {
        archivo << quoted(alumnos[i].nombre) << " "
                << quoted(alumnos[i].matricula) << " "
                << alumnos[i].calif[0] << " "
                << alumnos[i].calif[1] << " "
                << alumnos[i].calif[2] << " "
                << alumnos[i].grupo << endl;
    }

    archivo << ng << endl;

    for (int i = 0; i < ng; i++) {
        archivo << quoted(grupos[i].nombre) << " "
                << quoted(grupos[i].carrera) << endl;
    }

    archivo << nm << endl;

    for (int i = 0; i < nm; i++) {
        archivo << quoted(maestros[i].nombre) << " "
                << quoted(maestros[i].materia) << endl;
    }

    archivo.close();
    cout << "Datos guardados\n";
}

void cargar() {
    ifstream archivo("alumnos.txt");

    if (!archivo) {
        cout << "No hay datos guardados\n";
        return;
    }

    if (!(archivo >> na) || na < 0 || na > 100) {
        na = 0;
        cout << "Archivo incorrecto\n";
        return;
    }

    for (int i = 0; i < na; i++) {
        if (!(archivo >> quoted(alumnos[i].nombre)
              >> quoted(alumnos[i].matricula)
              >> alumnos[i].calif[0]
              >> alumnos[i].calif[1]
              >> alumnos[i].calif[2]
              >> alumnos[i].grupo)) {
            na = 0;
            cout << "Error al cargar\n";
            return;
        }
    }

    if (!(archivo >> ng) || ng < 0 || ng > 100) {
        na = 0;
        ng = 0;
        cout << "Archivo incorrecto\n";
        return;
    }

    for (int i = 0; i < ng; i++) {
        if (!(archivo >> quoted(grupos[i].nombre)
              >> quoted(grupos[i].carrera))) {
            na = 0;
            ng = 0;
            cout << "Error al cargar\n";
            return;
        }
    }

    if (!(archivo >> nm) || nm < 0 || nm > 100) {
        na = 0;
        ng = 0;
        nm = 0;
        cout << "Archivo incorrecto\n";
        return;
    }

    for (int i = 0; i < nm; i++) {
        if (!(archivo >> quoted(maestros[i].nombre)
              >> quoted(maestros[i].materia))) {
            na = 0;
            ng = 0;
            nm = 0;
            cout << "Error al cargar\n";
            return;
        }
    }

    archivo.close();
    cout << "Datos cargados\n";
}

void reporte() {
    ofstream archivo("reporte_alumnos.txt");

    int orden[100];

    for (int i = 0; i < na; i++)
        orden[i] = i;

    for (int i = 0; i < na - 1; i++) {
        for (int j = 0; j < na - 1 - i; j++) {
            if (promedio(alumnos[orden[j]]) <
                promedio(alumnos[orden[j + 1]])) {
                int aux = orden[j];
                orden[j] = orden[j + 1];
                orden[j + 1] = aux;
            }
        }
    }

    archivo << fixed << setprecision(2);
    archivo << "REPORTE DE ALUMNOS\n\n";

    for (int i = 0; i < na; i++) {
        int p = orden[i];

        archivo << "Lugar: " << i + 1 << endl;
        archivo << "Nombre: " << alumnos[p].nombre << endl;
        archivo << "Matricula: " << alumnos[p].matricula << endl;
        archivo << "Promedio: " << promedio(alumnos[p]) << endl;
        archivo << "Grupo: " << alumnos[p].grupo << endl;
        archivo << "-------------------\n";
    }

    if (na == 0)
        archivo << "No hay alumnos registrados\n";

    archivo.close();
    cout << "Reporte creado\n";
}

void mostrar() {
    for (int i = 0; i < na; i++) {
        cout << alumnos[i].nombre << " ";
        cout << promedio(alumnos[i]) << endl;
    }

    for (int g = 1; g <= ng; g++) {
        int mejor = -1;

        for (int i = 0; i < na; i++) {
            if (alumnos[i].grupo == g) {
                if (mejor == -1 ||
                    promedio(alumnos[i]) > promedio(alumnos[mejor]))
                    mejor = i;
            }
        }

        cout << "Mejor del grupo " << grupos[g - 1].nombre << ": ";

        if (mejor != -1)
            cout << alumnos[mejor].nombre << endl;
        else
            cout << "Sin alumnos\n";
    }

    for (int g = 0; g < ng; g++) {
        bool repetida = false;

        for (int j = 0; j < g; j++) {
            if (grupos[j].carrera == grupos[g].carrera)
                repetida = true;
        }

        if (!repetida) {
            int total = 0;

            for (int i = 0; i < na; i++) {
                int num = alumnos[i].grupo;

                if (num >= 1 && num <= ng &&
                    grupos[num - 1].carrera == grupos[g].carrera)
                    total++;
            }

            cout << grupos[g].carrera << ": "
                 << total << " alumnos\n";
        }
    }
}

int main() {
    int op;

    cargar();

    do {
        cout << "\n1. Capturar alumnos\n";
        cout << "2. Capturar grupos\n";
        cout << "3. Capturar maestros\n";
        cout << "4. Mostrar reportes\n";
        cout << "5. Guardar\n";
        cout << "6. Cargar\n";
        cout << "7. Generar reporte\n";
        cout << "8. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {

            case 1: {
                int n;
                cout << "Cantidad de alumnos: ";
                cin >> n;

                if (n < 1 || n > 100 - na) break;

                for (int i = 0; i < n; i++) {
                    cin.ignore(1000, '\n');

                    cout << "Nombre: ";
                    getline(cin, alumnos[na].nombre);

                    cout << "Matricula: ";
                    getline(cin, alumnos[na].matricula);

                    for (int j = 0; j < 3; j++) {
                        cout << "Calificacion " << j + 1 << ": ";
                        cin >> alumnos[na].calif[j];
                    }

                    cout << "Grupo: ";
                    cin >> alumnos[na].grupo;

                    na++;
                }
                break;
            }

            case 2: {
                int n;
                cout << "Cantidad de grupos: ";
                cin >> n;

                if (n < 1 || n > 100 - ng) break;

                cin.ignore(1000, '\n');

                for (int i = 0; i < n; i++) {
                    cout << "Nombre del grupo: ";
                    getline(cin, grupos[ng].nombre);

                    cout << "Carrera: ";
                    getline(cin, grupos[ng].carrera);

                    ng++;
                }
                break;
            }

            case 3: {
                int n;
                cout << "Cantidad de maestros: ";
                cin >> n;

                if (n < 1 || n > 100 - nm) break;

                cin.ignore(1000, '\n');

                for (int i = 0; i < n; i++) {
                    cout << "Nombre: ";
                    getline(cin, maestros[nm].nombre);

                    cout << "Materia: ";
                    getline(cin, maestros[nm].materia);

                    nm++;
                }
                break;
            }

            case 4:
                mostrar();
                break;

            case 5:
                guardar();
                break;

            case 6:
                cargar();
                break;

            case 7:
                reporte();
                break;

            case 8:
                guardar();
                cout << "Programa terminado\n";
                break;

            default:
                cout << "Opcion incorrecta\n";
        }

    } while (op != 8);

    return 0;
}