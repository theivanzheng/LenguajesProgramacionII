//
//  main.c
//  examenMayo18_JavierPozo
//
//  Created by Javier on 10/4/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct infoAsignatura{
    char nombreAsignatura[20];
    float notaAlumno;
    int convocatoria;
};
struct nodoAsignatura{
    struct nodoAsignatura *anterior;
    struct nodoAsignatura *siguiente;
    struct infoAsignatura inforAsig;
};
struct listaAsignaturas{
    struct nodoAsignatura *primero;
    struct nodoAsignatura *ultimo;
};

struct infoAlumno{
    char numExpediente[6];
    char nombreAlumno[20];
    char titulacion[30];
};
struct nodoAlumno{
    struct nodoAlumno *anterior;
    struct nodoAlumno *siguiente;
    struct infoAlumno inforAlum;
    
    struct listaAsignaturas asignaturas;
};
struct listaAlumnos{
    struct nodoAlumno *primero;
    struct nodoAlumno *ultimo;
};

//************* FUNCIONES SWITCH ***************
void anadirAlumnoFinal(struct listaAlumnos *listaAlum);
void anadirNotaAlumnoFinal(struct listaAsignaturas *listaAsig, struct listaAlumnos listaAlum);
void visualizarListaAlumnosFinalPrincipio(struct nodoAlumno *ultimo);
void visualizarListaNotasAlumnoFinalPrincipio(struct nodoAsignatura *ultimo, struct listaAlumnos listaAlum);

//************ FUNCIONES ADICIONALES *************
int menu(void);
void rellenarInformacionAlumnos(struct infoAlumno *inforAlum);
void rellenarInformacionAsignaturas(struct infoAsignatura *inforAsig);
struct nodoAlumno * buscarAlumno(struct nodoAlumno *primero, char numExpediente[]);


int main(void) {
    struct listaAlumnos listaAlum;
    struct listaAsignaturas listaAsig;
    int opcion;
    
    listaAlum.primero = listaAlum.ultimo = NULL;
        
    do{
        opcion = menu();
        
        switch (opcion){
            case 1:
                anadirAlumnoFinal(&listaAlum);
                break;
                
            case 2:
                anadirNotaAlumnoFinal(&listaAsig, listaAlum);
                break;
                
            case 3:
                
                break;
                
            case 4:
                
                break;
                
            case 5:
                visualizarListaAlumnosFinalPrincipio(listaAlum.ultimo);
                break;
                
            case 6:
                visualizarListaNotasAlumnoFinalPrincipio(listaAsig.ultimo, listaAlum);
                break;
                
            case 0:
                printf("Fin del programa \n\n");
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
        printf("\n************ MENU ************ \n");
        printf("\t 1. Anadir un alumno \n");
        printf("\t 2. Anadir nota a un alumno \n");
        printf("\t 3. Mostrar la nota media de la carrera \n");
        printf("\t 4. Eliminar una nota de un alumno \n");
        printf("\t 5. Visualizar todos los alumnos \n");
        printf("\t 6. Visualizar las notas de un alumno concreto \n");
        printf("\t 0. SALIR \n");
        
        printf("\nEscoja una opcion: ");
        scanf("%d", &opcion);
        printf("\n");
    }while((opcion < 0) || (opcion > 6));
    
    return opcion;
}

void anadirAlumnoFinal(struct listaAlumnos *listaAlum){
    struct nodoAlumno *nuevo, *comprobar;
    char numExpediente[6];
    
    nuevo = (struct nodoAlumno *) malloc (sizeof(struct nodoAlumno));
    
    if(nuevo == NULL){
        printf("ERROR DE MEMORIA, no se ha podido anadir \n");
        return;
    }
    
    printf("\n************ INFO ALUMNO ***********\n");
    printf("\t Numero de expediente: ");
    fpurge(stdin);
    scanf("%s", numExpediente);
    
    comprobar = buscarAlumno(listaAlum->primero, numExpediente);
    
    if(comprobar == NULL){
        strcpy(nuevo->inforAlum.numExpediente, numExpediente);
        
        rellenarInformacionAlumnos(&nuevo->inforAlum);
        
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
    else{
        printf("ERROR, el alumno con expediente %s ya esta registrado", numExpediente);
    }
}

void rellenarInformacionAlumnos(struct infoAlumno *inforAlum){
    printf("\t Nombre del alumno: ");
    fpurge(stdin);
    scanf("%[^\n]", inforAlum->nombreAlumno);
    printf("\t Titulacion: ");
    fpurge(stdin);
    scanf("%[^\n]", inforAlum->titulacion);
}

void visualizarListaAlumnosFinalPrincipio(struct nodoAlumno *ultimo){
    struct nodoAlumno *recorre = ultimo;
    
    printf("\n*************** ALUMNOS ***************\n");
    
    while(recorre != NULL){
        printf("\t Numero de expediente: %s \n", recorre->inforAlum.numExpediente);
        printf("\t Nombre del alumno: %s \n", recorre->inforAlum.nombreAlumno);
        printf("\t Titulacion: %s \n", recorre->inforAlum.titulacion);
        printf("\n");
        
        recorre = recorre->anterior;
    }
}

struct nodoAlumno * buscarAlumno(struct nodoAlumno *primero, char numExpediente[]){
    struct nodoAlumno *recorre = primero;
    
    while((recorre != NULL) && (strcmp(recorre->inforAlum.numExpediente, numExpediente) != 0)){
        recorre = recorre->siguiente;
    }
    
    return recorre;
}

void anadirNotaAlumnoFinal(struct listaAsignaturas *listaAsig, struct listaAlumnos listaAlum){
    struct nodoAsignatura *nuevo;
    struct nodoAlumno *comprobar;
    char numExpediente[6];
    
    printf("Introduce el numero de expediente del alumno al que desea asignarle una nota: ");
    fpurge(stdin);
    scanf("%s", numExpediente);
    
    comprobar = buscarAlumno(listaAlum.primero, numExpediente);
    
    if(comprobar == NULL){
        printf("No se ha encontrado al alumno \n");
        return;
    }
    
    nuevo = (struct nodoAsignatura *) malloc (sizeof(struct nodoAsignatura));
    
    if(nuevo == NULL){
        printf("ERROR DE MEMORIA, no se ha podido anadir \n");
        return;
    }
    
    rellenarInformacionAsignaturas(&nuevo->inforAsig);
    
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

void rellenarInformacionAsignaturas(struct infoAsignatura *inforAsig){
    inforAsig->convocatoria = 1;
    
    printf("\n*************** INFO ASIGNATURA ***************\n");
    printf("\t Nombre de la asignatura: ");
    fpurge(stdin);
    scanf("%[^\n]", inforAsig->nombreAsignatura);
    printf("\t Nota alumno: ");
    scanf("%f", &inforAsig->notaAlumno);
    
    if(inforAsig->notaAlumno <= 5){
        inforAsig->notaAlumno++;
    }
    
}

void visualizarListaNotasAlumnoFinalPrincipio(struct nodoAsignatura *ultimo, struct listaAlumnos listaAlum){
    struct nodoAsignatura *recorre = ultimo;
    struct nodoAlumno *comprobar;
    char numExpedienteBuscar[6];
    
    printf("Introduce el numero de expediente del alumno del que desea ver sus notas: ");
    fpurge(stdin);
    scanf("%s", numExpedienteBuscar);
    
    comprobar = buscarAlumno(listaAlum.primero, numExpedienteBuscar);
    
    if(comprobar == NULL){
        printf("No se ha encontrado al alumno \n");
    }
    else{
        printf("\n************ ASIGNATURAS %s ************\n", comprobar->inforAlum.nombreAlumno);
        
        while(recorre != NULL){
            if(recorre==NULL){
                return;
            }
            printf("\t Nombre de la asignatura: %s \n", recorre->inforAsig.nombreAsignatura);
            printf("\t Nota del alumno: %f \n", recorre->inforAsig.notaAlumno);
            printf("\t Convocatoria: %d \n", recorre->inforAsig.convocatoria);
            printf("\n");
            
            recorre = recorre->anterior;
        }
    }
}
