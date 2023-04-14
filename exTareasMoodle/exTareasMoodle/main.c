//
//  main.c
//  exTareasMoodle
//
//  Created by Ivan Zheng on 14/4/23.
//

#include <stdio.h>
#include <stdlib.h>

//*** MIS STRUCTS ***
struct tipoFecha{
    int dia;
    int mes;
    int anio;
};
struct nodoTarea{
    char tituloTarea[40];
    struct tipoFecha fecha;
    struct nodoTarea *siguiente;
    struct nodoTarea *anterior;
};

struct listaTarea{
    struct nodoTarea *primero;
    struct nodoTarea *ultima;
};

struct tipoInfoAlumno{
    char login[20];
    struct listaTarea *obligatorias;
    struct listaTarea *voluntarias;
};

struct nodoAlumno{
    struct tipoInfoAlumno info;
    struct nodoAlumno *siguiente;
    struct nodoAlumno *anterior;
};

struct tipoListaAlumno{
    struct nodoAlumno *primero;
    struct nodoAlumno *ultimo;
};

//*** MIS FUNCIONES PRINCIPALES ***

//*** MIS FUNCIONES SECUNDARIAS ***
void crearListadeListas(struct tipoListaAlumno lista);
void crearAlumno(struct tipoListaAlumno *listaAlumno);
int menu(void);

int main(int argc, const char * argv[]) {
    struct tipoListaAlumno listaAlumnos;
    int opc;
    crearAlumno(&listaAlumnos);
    
    printf("BIENVENIDO A ExTareasMoodle\n");
    do{
        opc=menu();
        
        switch (opc) {
            case 1:
                
                break;
                
            default:
                break;
        }
    }while(opc!=0);
    
    return 0;
}


//*** MIS FUNCIONES PRINCIPALES ***
void crearListadeListas(struct tipoListaAlumno lista){
    int numAlumnos,i;
    
    printf("\n\tCuantos alumnos quieres crear?: ");
    scanf("%d",&numAlumnos);
    
    for (i=0; i<numAlumnos; i++) {
        crearAlumno(&lista);
    }
    
}


//*** MIS FUNCIONES SECUNDARIAS ***
int menu(void){
    int opc;
    
    do{
        printf("\n*** MENU ****");
        printf("\n\t1. Subir tarea a Moodle");
        printf("\n\t2. Visualizar tareas (o|v) de un alumno");
        printf("\n\t3. Listado de alumno");
        printf("\n\t4. Eliminar todas las tareas obl. de un alumno");
        printf("\n\t0. Salir del programa");
        printf("\nEscoge una de las opciones");
        scanf("%d",&opc);
        
    }while(opc<0||opc>4);
    
    return opc;
}

void crearAlumno(struct tipoListaAlumno *listaAlumno){
    struct nodoAlumno *nuevo;
    //1.Reservo espacio
    nuevo= (struct nodoAlumno *)malloc(sizeof(struct nodoAlumno *));
        if(nuevo==NULL){
            printf("\n*** ERROR DE MEMORIA ***");
        }
    //2.- Relleno la informacion
    printf("\n\tCual es el login del alumno: ");
    scanf("%s",nuevo->info.login);
    nuevo->info.obligatorias->primero = nuevo->info.obligatorias->ultima=NULL;
    nuevo->info.voluntarias->primero  = nuevo->info.voluntarias->ultima=NULL;
    
    //3.- Conecto con la lista
    if(listaAlumno->primero==NULL){     //Es el primero
        listaAlumno->primero=nuevo;
    }else{
        listaAlumno->ultimo->siguiente=nuevo;
    }
    //----para todos los casos
    nuevo->siguiente=NULL;
    listaAlumno->ultimo->siguiente=nuevo;
    nuevo->anterior=listaAlumno->ultimo;
}
