//
//  main.c
//  ExListasDeListas2012
//
//  Created by Ivan Zheng on 19/4/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodoAsignaturas{
    char nombreAsignatura[20];
    int nota;
    struct nodoAsignaturas *siguiente;
    struct nodoAsignaturas *anterior;
};

struct listaAsignaturas{
    struct nodoAsignaturas *primero;
    struct nodoAsignaturas *ultimo;
};

struct listaAlumnos{
    struct nodoAlumno *primero;
    struct nodoAlumno *ultimo;
};

struct nodoAlumno{
    int expediente;
    char nombre[20];
    char apellidos[40];
    struct listaAsignaturas asignaturas;
    struct nodoAlumno *siguiente;
    struct nodoAlumno *anterior;
};


//*** MIS FUNCIONES PRINCIPALES ***
void addAlumno(struct listaAlumnos *listaAlumnos);
void addAsignatura(struct listaAlumnos *listaAlumnos);
void eliminarAsignatura(struct listaAlumnos *listaAlumnos, struct nodoAlumno *alumno, char nombreAsignatura[]);
void  mostrarTodo(struct listaAlumnos *listaAlumnos);
//*** MIS FUNCIONES SECUNDARIAS ***
int menu(void);
struct nodoAlumno * checkExpediente(struct listaAlumnos *listaAlumno, int numExpediente);
void showAlumno(struct listaAlumnos *listaAlumnos, struct nodoAlumno alumno);
struct nodoAsignaturas * checkAsignatura(struct nodoAlumno *alumno, char asignatura[]);
void eliminarAsignaturasBucleAlumnos(struct listaAlumnos *listaAlumnos);
void showAlumnoAsignaturas(struct listaAlumnos *listaAlumnos, struct nodoAlumno *alumno);


int main(int argc, const char * argv[]) {
    int opt;
    struct listaAlumnos listaAlumnos;
    do{
        opt=menu();
        
        switch (opt) {
            case 1:
                printf("\n1. Dar de alta un alumno.");
                addAlumno(&listaAlumnos);
                break;
            case 2:
                printf("\n2. Añadir asignaturas y calificaciones.");
                addAsignatura(&listaAlumnos);
                break;
            case 3:
                printf("\n3. Eliminar una asignatura a todos los alumnos");
                eliminarAsignaturasBucleAlumnos(&listaAlumnos);
                break;
            case 4:
                printf("\n4. Listado de la información de los alumnos: ");
                mostrarTodo(&listaAlumnos);
                break;
            case 5:
                printf("\n5. Almacenar listado en un fichero de la opción 4 en un fichero de texto.");

                break;
            case 6:
                printf("\nHas salido del programa");

                break;

            default:
                break;
        }
        
    }while (opt!=6);
    
    return 0;
}


//*** MIS FUNCIONES PRINCIPALES ***
void addAlumno(struct listaAlumnos *listaAlumnos){
    int expediente;
    struct nodoAlumno *alumno;
    printf("\nIntroduce el expediente: ");
    scanf("%d",&expediente);
    alumno=checkExpediente(listaAlumnos, expediente);
    if(alumno!=NULL){
        printf("\nUn alumno con el mismo expediente ya está en la lista");
    }else{
        //1.- Reservo espacio
        struct nodoAlumno *nuevo;
        nuevo=(struct nodoAlumno*)malloc(sizeof(struct nodoAlumno));
        if(nuevo==NULL){
            printf("\nERROR DE MEMORIA");
            return;;
        }
        //2.- relleno informacion
        nuevo->expediente=expediente;
        printf("\n\tIntroduce el nombre del alumno"); fpurge(stdin);
        scanf("%s",nuevo->nombre);
        printf("\n\tIntroduce el apellido del alumno"); fpurge(stdin);
        scanf("%s",nuevo->apellidos);
        
        //3.- Enalzo con la lsita
        if(listaAlumnos->primero==NULL){    //No hay nada en lista
            listaAlumnos->primero=nuevo;
            
        }else{
            listaAlumnos->ultimo->siguiente=nuevo;
        }
        nuevo->anterior=listaAlumnos->ultimo;
        nuevo->siguiente=NULL;
        listaAlumnos->ultimo=nuevo;
        
    }
}

void addAsignatura(struct listaAlumnos *listaAlumnos){
    int expediente;
    struct nodoAlumno *alumno;
    
    
    printf("\nIntroduce el expediente: ");
    scanf("%d",&expediente);
    alumno=checkExpediente(listaAlumnos, expediente);
    if(alumno==NULL){
        printf("\nEl alumno que has introducido no está en a lista");
    }else{
        //1.- reservo memoria
        struct nodoAsignaturas *nuevo;
        nuevo=(struct nodoAsignaturas *)malloc(sizeof(struct nodoAsignaturas));
        if(nuevo==NULL){
            printf("\nERROR DE MEMORIA");
            return;
        }
        //2.- relleno informacion
        printf("\n\tIntroduce el nombre de la asignatura"); fpurge(stdin);
        scanf("%s",nuevo->nombreAsignatura);
        
        checkAsignatura(alumno, nuevo->nombreAsignatura);
        
        if(checkAsignatura(alumno, nuevo->nombreAsignatura)!=NULL){
            printf("\Esa asignatura ya está registrada");
            return;
        }
        
        printf("\n\tIntroduce la nota de la asignatura");
        scanf("%d",&nuevo->nota);
        
        //3.- Enalzo con la lsita
        if(alumno->asignaturas.primero== NULL){    //No hay nada en lista
            alumno->asignaturas.primero= nuevo;
        }else{
            alumno->asignaturas.ultimo= nuevo;
        }
        nuevo->anterior=alumno->asignaturas.ultimo;
        nuevo->siguiente=NULL;
        alumno->asignaturas.ultimo=nuevo;
    }
    
}

void eliminarAsignatura(struct listaAlumnos *listaAlumnos,struct nodoAlumno *alumno, char nombreAsignatura[]){
    struct nodoAsignaturas *recorre=alumno->asignaturas.primero;
    
    while (recorre!=NULL) {
        if(strcmp(nombreAsignatura, recorre->nombreAsignatura)==0){
            showAlumno(listaAlumnos, *alumno);
            //1.- que se el unico
            if(recorre->siguiente==NULL && recorre->anterior==NULL){
                alumno->asignaturas.ultimo=alumno->asignaturas.primero=NULL;
                
            //2.- que sea el primero
            }else if(recorre->anterior==NULL){
                recorre->siguiente->anterior=NULL;
                alumno->asignaturas.primero=recorre->siguiente;
                recorre->siguiente=NULL;
                
            //3.- que sea el último
            }else if(recorre->siguiente==NULL){
                recorre->anterior->siguiente=NULL;
                alumno->asignaturas.ultimo=recorre->anterior;
            //4.- que sea el del medio

            }else{
                recorre->siguiente->anterior=recorre->anterior;
                recorre->anterior->siguiente=recorre->siguiente;
                recorre->anterior=NULL;
                recorre->siguiente=NULL;
            }
            //Para todos los casos
            recorre=NULL;
            free(recorre);
            
               }
    }
    
}

void  mostrarTodo(struct listaAlumnos *listaAlumnos){
    struct nodoAlumno *recorre = listaAlumnos->primero;

    while (recorre!=NULL) {
        showAlumno(listaAlumnos, *recorre);
        
        recorre=recorre->siguiente;
    }
}

//*** MIS FUNCIONES SECUNDARIAS ***
int menu(void){
    int opt;
    do{
        printf("\n****** MENU ******");
        printf("\n\t1. Dar de alta un alumno.");
        printf("\n\t2. Añadir asignaturas y calificaciones.");
        printf("\n\t3. Eliminar una asignatura a todos los alumnos ");
        printf("\n\t4. Listado de la información de los alumnos");
        printf("\n\t6. Salir.");
        printf("\n\t7. Mostrar todo.");
        printf("\nSelecciona una opción: ");
        scanf("%d",&opt);
    }while(opt>7||opt<0);
    return opt;
}

struct nodoAlumno * checkExpediente(struct listaAlumnos *listaAlumno, int numExpediente){
    struct nodoAlumno *recorre = listaAlumno->primero;
    
    while (recorre!=NULL) {
        if(recorre->expediente==numExpediente){
            return recorre;
        }
        recorre=recorre->siguiente;
    }
    return recorre;
}

void showAlumno(struct listaAlumnos *listaAlumnos, struct nodoAlumno alumno){
    
    printf("\n\tNombre: %s, Apellidos: %s",alumno.nombre, alumno.apellidos);
    showAlumnoAsignaturas(listaAlumnos, &alumno);
}

struct nodoAsignaturas * checkAsignatura(struct nodoAlumno *alumno, char asignatura[]){
    struct nodoAsignaturas *recorre = alumno->asignaturas.primero;
    
    while (recorre!=NULL) {
        if(strcmp(asignatura, recorre->nombreAsignatura)==0){
            return recorre;
        }
        recorre=recorre->siguiente;
    }
    return recorre;
}

void eliminarAsignaturasBucleAlumnos(struct listaAlumnos *listaAlumnos){
    struct nodoAlumno *recorre = listaAlumnos->primero;
    char nombreAsignatura[20];
    printf("\nQué asignatura quieres eliminar: ");
    scanf("%s",nombreAsignatura);
    
    while (recorre!=NULL) {
        showAlumno(listaAlumnos, *recorre);
        eliminarAsignatura(listaAlumnos, recorre, nombreAsignatura);
        printf("\n** Se ha eliminado el alumno **");
        recorre=recorre->siguiente;
    }

}

void showAlumnoAsignaturas(struct listaAlumnos *listaAlumnos, struct nodoAlumno *alumno){
    struct nodoAsignaturas *recorre = alumno->asignaturas.primero;
    printf(" Asignaturas: ");
    
    while (recorre!=NULL) {
        printf("\n\t\t%s Nota: %d ",recorre->nombreAsignatura,recorre->nota);
        recorre=recorre->siguiente;
    }
}
