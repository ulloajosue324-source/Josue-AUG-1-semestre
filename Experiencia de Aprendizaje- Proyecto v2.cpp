#include <iostream>
#include <string>
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

Alumno alumnos[100]; Maestro maestros[100]; Grupo grupos[100];

int na = 0, nm = 0, ng = 0;

float promedio(Alumno a) {
    return (a.calif[0] + a.calif[1] + a.calif[2]) / 3;
}

int main() {
    int op;

    do {
        cout << "\n--- SISTEMA DE ALUMNOS ---\n";
        cout << "1. Capturar N alumnos\n";
        cout << "2. Capturar grupos y carreras\n";
        cout << "3. Capturar maestros\n";
        cout << "4. Mostrar reportes\n";
        cout << "5. Salir\n";
        cout << "Elige una opcion: ";
        cin >> op;

        switch (op) {
            case 1: {
                int n;
                cout << "Capturar N alumnos: ";
                cin >> n;

                if (n < 1 || n > 100 - na) {
                    cout << "Captura no valida\n";
                    break;
                }

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

                    cout << "Numero de grupo: ";
                    cin >> alumnos[na].grupo;
                    na++;
                }
                break;
            }

            case 2: {
                int n;
                cout << "Capturar grupos y carreras: ";
                cin >> n;

                if (n < 1 || n > 100 - ng) {
                    cout << "Cantidad no valida\n";
                    break;
                }

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
                cout << "Capturar maestros: ";
                cin >> n;

                if (n < 1 || n > 100 - nm) {
                    cout << "Captura no valida\n";
                    break;
                }

                cin.ignore(1000, '\n');

                for (int i = 0; i < n; i++) {
                    cout << "Nombre del maestro: ";
                    getline(cin, maestros[nm].nombre);

                    cout << "Materia: ";
                    getline(cin, maestros[nm].materia);
                    nm++;
                }
                break;
            }

            case 4: {
                for (int i = 0; i < na; i++) {
                    cout << alumnos[i].nombre
                         << " - Mostrar reportes: "
                         << promedio(alumnos[i]) << endl;
                }

                for (int g = 1; g <= ng; g++) {
                    int mejor = -1;

                    for (int i = 0; i < na; i++) {
                        if (alumnos[i].grupo == g &&
                            (mejor == -1 ||
                            promedio(alumnos[i]) >
                            promedio(alumnos[mejor]))) {
                            mejor = i;
                        }
                    }

                    cout << "Mejor del grupo "
                         << grupos[g - 1].nombre << ": ";

                    if (mejor != -1)
                        cout << alumnos[mejor].nombre << endl;
                    else
                        cout << "Sin alumnos\n";
                }

                for (int g = 0; g < ng; g++) {
                    bool repetida = false;

                    for (int j = 0; j < g; j++) {
                        if (grupos[g].carrera == grupos[j].carrera)
                            repetida = true;
                    }

                    if (!repetida) {
                        int total = 0;

                        for (int i = 0; i < na; i++) {
                            int num = alumnos[i].grupo;

                            if (num >= 1 && num <= ng &&
                                grupos[num - 1].carrera ==
                                grupos[g].carrera)
                                total++;
                        }

                        cout << "Carrera " << grupos[g].carrera
                             << ": " << total << " alumnos\n";
                    }
                }
                break;
            }

            case 5:
                cout << "Salir\n";
                break;

            default:
                cout << "Opcion incorrecta\n";
        }

    } while (op != 5);

    return 0;
}