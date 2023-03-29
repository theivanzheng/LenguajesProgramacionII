//
//  main.c
//  practica6
//
//  Created by Ivan Zheng on 29/3/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct notaAlumno{
    char asignatura[20];
    float fNota;
    int convocatoria;
};

struct infoPersona{
    char numexpediente[6];
    char nombre[20];
    char titulacion[30];
    struct notaAlumno structNota;
};

struct tipoNodoPersona{
    struct infoPersona info;
    struct tipoNodoPersona *siguiente;
    struct tipoNodoPersona *anterior;
};

struct listaAlumnos{
    struct tipoNodoPersona *primero;
    struct tipoNodoPersona *ultimo;
};
void imprimirMenu(void);
int opcionMenu(void);
void casemenu(int opt);

int main(int argc, const char * argv[]) {
    int opt=0;
    printf("BIENVENIDO A LA PRACTICA 6");
    printf("\n--------------------------");
    do {
        imprimirMenu();
        opt=opcionMenu();
    } while (opt>5 || opt<1);
    
    opt=opcionMenu();
    imprimirMenu();
    return 0;
}

//MIS FUNCIONES BÁSICAS
void imprimirMenu(void){
    printf("\nMENU:"
            "\n\t1. Añadir un registro de alumno \n\t2. Añadir nota al alumno \n\t3. Mostrar nota media de todos los alumnos registrados \n\t4. Eliminar nota asignatura\n\t5. Salir del programa");
}

int opcionMenu(void){
    int opt=0;
    printf("\nEscoge una de las opciones: ");
    scanf("%d",&opt);
    return opt;
}

void casemenu(int opt){
    
}
