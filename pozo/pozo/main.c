//
//  main.c
//  yutube
//
//  Created by Javier on 19/4/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct infoAsignaturas{
    char nombreAsignatura[20];
    float notaAlumno;
};
struct nodoAsignaturas{
    struct nodoAsignaturas *anterior;
    struct nodoAsignaturas *siguiente;
    struct infoAsignaturas inforAsig;
};
struct listaAsignaturas{
    struct nodoAsignaturas *primero;
    struct nodoAsignaturas *ultimo;
};

struct infoAlumno{
    char nombreAlumno[40];
    char numExpediente[10];
};
struct nodoAlumno{
    struct nodoAlumno *anterior;
    struct nodoAlumno *siguiente;
    struct infoAlumno inforAlum;

    struct listaAsignaturas asignaturasAlumno;
};
struct listaAlumnos{
    struct nodoAlumno *primero;
    struct nodoAlumno *ultimo;
};

//************** FUNCIONES SWITCH ***************
void anadirAlumnoFinal(struct listaAlumnos *listaAlum);
void anadirAsignaturaAlumno(struct listaAlumnos listaAlumnos);
void anadirAsignatura(struct listaAsignaturas *listaAsig);
void visualizarAlumnos(struct nodoAlumno *primero);
void visualizarAsignaturas(struct nodoAsignaturas *primero);
void eliminarAsignaturaAlumnos(struct nodoAlumno *primero);

//************** FUNCIONES ADICIONALES *************
int menu(void);
void rellenarInformacionAlumnos(struct infoAlumno *inforAlum);
struct nodoAlumno * buscarAlumno(struct nodoAlumno *primero, char numExpediente[]);
struct nodoAsignaturas * buscarAsignatura(struct nodoAsignaturas *primero, char nombreAsignatura[]);

int main(void) {
    struct listaAlumnos listaAlum;
    int opcion;

    listaAlum.primero = listaAlum.ultimo = NULL; //lista vacia

    do{
        opcion = menu();

        switch (opcion){
            case 1:
                anadirAlumnoFinal(&listaAlum);
                break;

            case 2:
                anadirAsignaturaAlumno(listaAlum);
                break;

            case 3:
                eliminarAsignaturaAlumnos(listaAlum.primero);
                break;

            case 4:
                visualizarAlumnos(listaAlum.primero);
                break;

            case 0:
                printf("Fin del programa... \n\n");
                break;

            default:
                printf("Opcion Invalida \n");
        }
    }while(opcion != 0);


    return 0;
}

int menu(void){
    int opcion;

    do{
        printf("\n************* MENU *************\n");
        printf("\t 1. Anadir un alumno. \n");
        printf("\t 2. Calificar a un alumno. \n");
        printf("\t 3. Eliminar una asignatura de un alumno. \n");
        printf("\t 4. Visualizar la informacion de todos los alumnos. \n");
        printf("\t 0. SALIR");

        printf("\nEscoja una opcion: ");
        scanf("%d", &opcion);
        printf("\n");
    }while((opcion < 0) || (opcion > 4));

    return opcion;
}

void anadirAlumnoFinal(struct listaAlumnos *listaAlum){
    struct nodoAlumno *nuevo, *comprobar;
    char numExpedienteBuscar[10];

    printf("\n************** INFO ALUMNO *************\n");
    printf("\t Numero de expediente: ");
    fpurge(stdin);
    scanf("%s", numExpedienteBuscar);

    comprobar = buscarAlumno(listaAlum->primero, numExpedienteBuscar);

    if(comprobar != NULL){
        printf("El alumno con expedeiente: %s ya esta registrado \n", numExpedienteBuscar);
        return;
    }

    nuevo = (struct nodoAlumno *) malloc (sizeof(struct nodoAlumno));

    if(nuevo == NULL){
        printf("ERROR DE MEMORIA, no se ha podido anadir \n");
        return;
    }

    strcpy(nuevo->inforAlum.numExpediente, numExpedienteBuscar);

    rellenarInformacionAlumnos(&nuevo->inforAlum);

    nuevo->asignaturasAlumno.primero = nuevo->asignaturasAlumno.ultimo = NULL;

    if(listaAlum->primero == NULL){
        listaAlum->primero = nuevo;
    }
    else{
        listaAlum->ultimo->siguiente = nuevo;
    }

    nuevo->siguiente = NULL;
    nuevo->anterior = listaAlum->ultimo;
    listaAlum->ultimo = nuevo;
}

struct nodoAlumno * buscarAlumno(struct nodoAlumno *primero, char numExpedinte[]){
    struct nodoAlumno *recorre = primero;

    while((recorre != NULL) && (strcmp(recorre->inforAlum.numExpediente, numExpedinte) != 0)){
        recorre = recorre->siguiente;
    }

    return recorre;
}

void rellenarInformacionAlumnos(struct infoAlumno *inforAlum){
    printf("\t Nombre: ");
    fpurge(stdin);
    scanf("%[^\n]", inforAlum->nombreAlumno);
}

void anadirAsignaturaAlumno(struct listaAlumnos listaAlumnos){
    struct nodoAlumno *comprobar;
    char numExpedienteBuscar[10];

    printf("Numero de expedinte del alumno a calificar: ");
    fpurge(stdin);
    scanf("%s", numExpedienteBuscar);

    comprobar = buscarAlumno(listaAlumnos.primero, numExpedienteBuscar);

    if(comprobar == NULL){
        printf("El alumno con expedeiente: %s no esta registrado \n", numExpedienteBuscar);
        return;
    }

    anadirAsignatura(&comprobar->asignaturasAlumno);
}

void anadirAsignatura(struct listaAsignaturas *listaAsig){
    struct nodoAsignaturas *nuevo, *comprobar;
    char nombreAsignaturaBuscar[20];

    printf("\n************ INFO ASIGNATURAS ************\n");
    printf("\t Nombre asignatura: ");
    fpurge(stdin);
    scanf("%[^\n]", nombreAsignaturaBuscar);

    comprobar = buscarAsignatura(listaAsig->primero, nombreAsignaturaBuscar);

    if(comprobar != NULL){
        printf("%s ya se le ha calificado a dicho alumno", nombreAsignaturaBuscar);
        return;
    }

    nuevo = (struct nodoAsignaturas *) malloc (sizeof(struct nodoAsignaturas));

    if(nuevo == NULL){
        printf("ERROR DE MEMORIA, no se ha podido anadir \n");
        return;
    }

    strcpy(nuevo->inforAsig.nombreAsignatura, nombreAsignaturaBuscar);

    printf("\t Nota: ");
    scanf("%f", &nuevo->inforAsig.notaAlumno);

    if(listaAsig->primero == NULL){
        listaAsig->primero = nuevo;
    }
    else{
        listaAsig->ultimo->siguiente = nuevo;
    }

    nuevo->siguiente = NULL;
    nuevo->anterior = listaAsig->ultimo;
    listaAsig->ultimo = nuevo;
}

struct nodoAsignaturas * buscarAsignatura(struct nodoAsignaturas *primero, char nombreAsignatura[]){
    struct nodoAsignaturas *recorre = primero;

    while((recorre != NULL) && (strcmp(recorre->inforAsig.nombreAsignatura, nombreAsignatura) != 0)){
        recorre = recorre->siguiente;
    }

    return recorre;
}

void visualizarAsignaturas(struct nodoAsignaturas *primero){
    struct nodoAsignaturas *recorre = primero;

    printf("\t Asignaturas: \n");

    while(recorre != NULL){
        printf("\t\t <%s>: <%.2f> \n", recorre->inforAsig.nombreAsignatura, recorre->inforAsig.notaAlumno);

        recorre = recorre->siguiente;
    }
}

void visualizarAlumnos(struct nodoAlumno *primero){
    struct nodoAlumno *recorre = primero;

    while(recorre != NULL){
        printf("Alumno: <%s> - <%s> \n", recorre->inforAlum.nombreAlumno, recorre->inforAlum.numExpediente);
        visualizarAsignaturas(recorre->asignaturasAlumno.primero);

        recorre = recorre->siguiente;
    }
}

void eliminarAsignaturaAlumnos(struct nodoAlumno *primero){
    struct nodoAsignaturas *borrar, *siguiente = NULL, *anterior = NULL, *recorre = asignaturasAlumnos->primero;
    char nombreAsignaturaBuscar[20];

    printf("\t Nombre asignatura: ");
    fpurge(stdin);
    scanf("%[^\n]", nombreAsignaturaBuscar);

    borrar = buscarAsignatura(asignaturasAlumnos->primero, nombreAsignaturaBuscar);

    if(borrar == NULL){
        printf("%s no esta registrada \n", nombreAsignaturaBuscar);
        return;
    }

    while(recorre != NULL){
        if(strcmp(recorre->inforAsig.nombreAsignatura, nombreAsignaturaBuscar) == 0){
            borrar->siguiente = siguiente;
            borrar->anterior = anterior;

            if((anterior == NULL) && (siguiente == NULL)){
                asignaturasAlumnos->primero = NULL;
                asignaturasAlumnos->ultimo = NULL;
            }
            else if(asignaturasAlumnos->primero == borrar){
                asignaturasAlumnos->primero = siguiente;
                siguiente->anterior = NULL;
            }
            else if(asignaturasAlumnos->ultimo == borrar){
                asignaturasAlumnos->ultimo = anterior;
                anterior->siguiente = NULL;
            }
            else{
                anterior->siguiente = siguiente;
                siguiente->anterior = anterior;
            }

            free(borrar);
        }

        recorre = recorre->siguiente;
    }
}
