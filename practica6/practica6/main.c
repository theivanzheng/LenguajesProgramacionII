//
//  main.c
//  practica6
//
//  Created by Ivan Zheng on 29/3/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct asignatura{
    char asignatura[20];
    float fNota;
    int convocatoria;
    struct asignatura *siguiente;
    struct asignatura *anterior;
};
struct listaAsignaturas{
    struct asignatura *primero;
    struct asignatura *ultimo;
};

struct infoPersona{
    char numexpediente[6];
    char nombre[20];
    char titulacion[30];
};

struct tipoNodoPersona{
    struct infoPersona info;
    struct listaAsignaturas asignaturas;
    struct tipoNodoPersona *siguiente;
    struct tipoNodoPersona *anterior;
};

struct listaAlumnos{
    struct tipoNodoPersona *primero;
    struct tipoNodoPersona *ultimo;
};


//MIS FUNCIONES PRINCIPALES
void addAlumno(struct listaAlumnos *lista);
void addNodoAlumno(struct listaAlumnos *lista);
void addNotaAlumno(struct listaAlumnos *lista);
void addNodoAsignaturas(struct listaAsignaturas *listaAsginaturas);
struct tipoNodoPersona *checkNombre(char nombreAcomprobar[], struct listaAlumnos *lista);

//MIS FUNCIONES SECUNDARIAS
int Menu(void);
void crearListaDelistas(struct listaAlumnos *listaAlumnos);


//MI MAIN
int main(int argc, const char * argv[]) {
    int opt=0;
    struct listaAlumnos lista;
    printf("BIENVENIDO A LA PRACTICA 6");
    printf("\n--------------------------");
    do {
        opt=Menu();
        switch (opt){
            case 1:
                addNodoAlumno(&lista);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
        }
        
    } while (opt!=0);

    return 0;
}

//CODIGO DE  FUNCIONES PRINCIPALES
void addNotaAlumno(struct listaAlumnos *lista){
    char nombre[20];
    printf("\nIntroduce el nombre del alumno: ");
    fpurge(stdin);
    scanf("%[^\n]",nombre);
    
    if(  checkNombre(nombre, lista)==NULL){
        printf("\nEl alumno no está en la lista");
        return;
    }else{
       
    }
}
void addAlumno(struct listaAlumnos *lista){
    
}
void addNodoAlumno(struct listaAlumnos *lista){
    printf("\n1.- AÑADIR UN REGISTRO DE UN ALUMNO");
    printf("\n-----------------------------------");
    struct tipoNodoPersona *nuevo;
    int numAsignaturas;
    
    //1.- reservo memoria
    nuevo= (struct tipoNodoPersona *)malloc(sizeof(struct tipoNodoPersona));
        if(nuevo==NULL){
            printf("\nERROR DE MEMORIA, NO SE HA PODIDO CREAR UN NUEVO ALUMNO.");
        }
    //2.- Relleno la información
    printf("\nIntroduce el nombre del alumno: ");
    fpurge(stdin);
    scanf("%[^\n]",nuevo->info.nombre);
    checkNombre(nuevo->info.nombre, lista);
    if( checkNombre(nuevo->info.nombre, lista) == NULL){
        //printf("/nEl usuario no se encuentra en la lista, se pocede a insertar en la lista");
        printf("\nIntroduce el expediente del alumno: ");
        fpurge(stdin);
        scanf("%[^\n]",nuevo->info.numexpediente);
        printf("\nIntroduce la titulacion del alumno: ");
        fpurge(stdin);
        scanf("%[^\n]",nuevo->info.titulacion);
        
        //inicializo la lista de asignaturas
        printf("\nCuantas asignaturas tiene %s", nuevo->info.nombre);
        scanf("%d", &numAsignaturas);
        nuevo->asignaturas.primero=nuevo->asignaturas.ultimo=NULL;
        for (int i=0; i<numAsignaturas; i++) {
            add
        }
    }else{
        printf("\nEl usuario ya está en la lista");
        return;
    }
    
    //3.-CONECTO CON LA LISTA
    if(lista->primero==NULL){
        lista->primero=nuevo;
    }else{
        lista->ultimo->siguiente=nuevo;
    }
    nuevo->siguiente = NULL;
    nuevo->anterior = lista->ultimo;
    lista->ultimo = nuevo;
}

void addNodoAsignaturas(struct listaAsignaturas *listaAsginaturas){
    struct asignatura *nuevo;
    
    //1.- Reservo memoria
    nuevo=(struct asignatura *)malloc(sizeof(struct asignatura));
    if(nuevo==NULL){
        printf("\nERROR DE MEMORIA, NO SE HA PODDIDO CREAR ASIGNATURA");
    }
}

//CODIGO DE  FUNCIONES SECUNDARIAS
int Menu(void){
    int opt=0;
    do{
        
        
        printf("\nMENU:"
               "\n\t1. Añadir un registro de alumno \n\t2. Añadir nota al alumno \n\t3. Mostrar nota media de todos los alumnos registrados \n\t4. Eliminar nota asignatura\n\t5. Salir del programa\nSelecciona una opción: ");
        scanf("%d",&opt);
    }while (opt<0 || opt>5);
    return opt;
}

struct tipoNodoPersona *checkNombre(char nombreAcomprobar[], struct listaAlumnos *lista){
    struct tipoNodoPersona *recorre=lista->primero;
    
    if(recorre==NULL){
        printf("\nLa lista está vacía");
        return recorre;
    }else{
        while (recorre!=NULL && (strcmp(recorre->info.nombre , nombreAcomprobar)!=0)){
            recorre=recorre->siguiente;
        }
    }
    return recorre;
}

void crearListaDelistas(struct listaAlumnos *listaAlumnos){
    int n, i;
    
    //inicializo la lista
    listaAlumnos->primero = listaAlumnos->ultimo=NULL;
    printf("Introduce el número de alumnos que hay: "); scanf("%d", &n);
    for (i=0; i<n; i++) {
        printf("Para el alumno %d",i+1);
        addNodoAlumno(listaAlumnos);
    }
}

