//
//  main.c
//  exTareasMoodle
//
//  Created by Ivan Zheng on 14/4/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void subirTareaMoodle(struct tipoListaAlumno *listaAlumno);
void visualizarTareasAlumno(struct tipoListaAlumno *listaAlumnmo);

//*** MIS FUNCIONES SECUNDARIAS ***
void crearListadeListas(struct tipoListaAlumno *lista);
void crearListaTareas(struct listaTarea *listaTarea);
void crearAlumno(struct tipoListaAlumno *listaAlumno);
int menu(void);
void showAllAlumnos(struct tipoListaAlumno *listaAlumno);
struct nodoAlumno *checkLoginAlumno(struct tipoListaAlumno *listaAlumno, char loginAlumno[]);
int escogerTipoTarea(void);
void addNodoTarea(struct nodoAlumno *alumno, int tipoTarea);
void addNodoAlumno(struct tipoListaAlumno *listaAlumno);


int main(int argc, const char * argv[]) {
    struct tipoListaAlumno listaAlumnos;
    int opc;
    printf("\n*** BIENVENIDO AL REGISTRO DE TAREAS DE MOODLE ***");
    crearListadeListas(&listaAlumnos);
    
    printf("BIENVENIDO A ExTareasMoodle\n");
    do{
        opc=menu();
        
        switch (opc) {
            case 1:
                printf("\n1. Subir tarea a Moodle");
                subirTareaMoodle(&listaAlumnos);
                break;
            case 2:
                printf("\n2. Visualizar tareas de un alumno");
                visualizarTareasAlumno(&listaAlumnos);
                break;
            case 3:
                printf("\n3. Mostrar listado de alumnos");
                showAllAlumnos(&listaAlumnos);
            default:
                break;
        }
    }while(opc!=0);
    
    return 0;
}


//*** MIS FUNCIONES PRINCIPALES ***

void subirTareaMoodle(struct tipoListaAlumno *listaAlumno){
    char loginAlumno[20];
    int tipoTarea;
    if(listaAlumno->primero==NULL){
        printf("\nLa lista de alumnos está vacía");
        return;
    }
    
    showAllAlumnos(listaAlumno);
    printf("\nEscoge qué alumno quieres que suba una tarea: "); fflush(stdin);
    scanf("%s",loginAlumno);
    
    //Compruebo que el alumno existe
    struct nodoAlumno *alumno = checkLoginAlumno(listaAlumno, loginAlumno);
    if(alumno==NULL){
        printf("\nEl alumno introducido no está en la lista");
        return;
    }
    tipoTarea= escogerTipoTarea();
    addNodoTarea(alumno,tipoTarea);
    printf("\nTarea añadida con éxito");
}

void visualizarTareasAlumno(struct tipoListaAlumno *listaAlumnmo){
    char loginCHosen[20];
    struct nodoAlumno *alumno;
    struct nodoTarea *recorre;
    
    showAllAlumnos(listaAlumnmo);
    printf("\nEscoge de qué alumno quieres ver las tareas: ");
    scanf("%s",loginCHosen);
    alumno = checkLoginAlumno(listaAlumnmo, loginCHosen);
    if(alumno==NULL){
        printf("\nEl login del alumno escogido no está en la lista");
        return;
    }
    
    //ahora voy a recorrer las dos listas
    printf("\nLas tareas obligatorias");
    recorre=alumno->info.obligatorias->primero;
    
    if(alumno->info.obligatorias->primero ==NULL){
        printf("\n*** No tiene tareas obligatorias ***");
    }else{
        printf("\nLas tareas obligatorias");
        recorre=alumno->info.obligatorias->primero;
        while (recorre!=NULL) {
            printf("\n\t\tNombre de la tarea: %s", recorre->tituloTarea);
            printf("\n\t\tFecha de la tarea: %d/ %d/ %d", recorre->fecha.dia,recorre->fecha.mes, recorre->fecha.anio);
            printf("\n");
            recorre=recorre->siguiente;
        }
    }
   
    if(alumno->info.voluntarias->primero ==NULL){
        printf("\n*** No tiene tareas voluntarias ***");
    }else{
        printf("\nLas tareas voluntarias");
        recorre=alumno->info.voluntarias->primero;
        while (recorre!=NULL) {
            printf("\n\t\tNombre de la tarea: %s", recorre->tituloTarea);
            printf("\n\t\tFecha de la tarea: %d/ %d/ %d", recorre->fecha.dia,recorre->fecha.mes, recorre->fecha.anio);
            printf("\n");
            recorre=recorre->siguiente;
        }
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

void crearListadeListas(struct tipoListaAlumno *lista){
    int numAlumnos,i;
    
    //Inicializo mi lista
    lista->primero=lista->ultimo=NULL;
    printf("\n\tCuantos alumnos quieres crear?: ");
    scanf("%d",&numAlumnos);
    
    for (i=0; i<numAlumnos; i++) {
        crearAlumno(lista);
    }
}

void crearAlumno(struct tipoListaAlumno *listaAlumno){
    struct nodoAlumno *nuevo;
    
    //1.Reservo espacio
    nuevo= (struct nodoAlumno *)malloc(sizeof(struct nodoAlumno ));
        if(nuevo==NULL){
            printf("\n*** ERROR DE MEMORIA ***");
        }
    //2.- Relleno la informacion
    do{
        printf("\n\tCual es el login del alumno: ");
        scanf("%s",nuevo->info.login);
        
        if(checkLoginAlumno(listaAlumno, nuevo->info.login)!=NULL){
            printf("\n\tEl alumno con ese login ya existe, vuelve a intentarlo");
        
        }
        
    }while (checkLoginAlumno(listaAlumno, nuevo->info.login)!=NULL);
    
    nuevo->info.obligatorias = (struct listaTarea*) malloc(sizeof(struct listaTarea));
    nuevo->info.voluntarias = (struct listaTarea*) malloc(sizeof(struct listaTarea));

    
    crearListaTareas(nuevo->info.obligatorias);
    crearListaTareas(nuevo->info.voluntarias);
    
    


    //3.- Conecto con la lista
    if(listaAlumno->primero==NULL){     //Es el primero
        listaAlumno->primero=nuevo;
    }else{
        listaAlumno->ultimo->siguiente=nuevo;
    }
    //----para todos los casos
    nuevo->siguiente=NULL;
    nuevo->anterior=listaAlumno->ultimo;
    listaAlumno->ultimo=nuevo;
}

void showAllAlumnos(struct tipoListaAlumno *listaAlumno){
    struct nodoAlumno *recorre = listaAlumno->primero;
    printf("\nTodos los alumnos: ");
    while (recorre!=NULL) {
        printf("\n\t%s",recorre->info.login);
        recorre=recorre->siguiente;
    }
}

struct nodoAlumno *checkLoginAlumno(struct tipoListaAlumno *listaAlumno, char loginAlumno[]){
    struct nodoAlumno *recorre = listaAlumno->primero;
    while (recorre!=NULL) {
        if(strcmp(loginAlumno, recorre->info.login)==0){
            return recorre;
        }
        recorre=recorre->siguiente;
    }
    return recorre;
}

int escogerTipoTarea(void){
    int opc;
    do{
        printf("\nEscoge el tipo de tarea");
        printf("\n\t1. Obligatoria");
        printf("\n\t2. Voluntaria");
        scanf("%d",&opc);
        if(opc<1 || opc>2){
            printf("\n*** La opción esocgido no es valida *** ");
        }
    }while(opc<1 || opc>2);
    
    return opc;
}

void addNodoTarea(struct nodoAlumno *alumno, int tipoTarea){
    struct nodoTarea *nuevo;
    struct listaTarea *listaTarea;

    if (tipoTarea == 1) {
           listaTarea = alumno->info.obligatorias;
       } else if (tipoTarea == 2) {
           listaTarea = alumno->info.voluntarias;
       } else {
           printf("\n*** Tipo de tarea no válido ***");
           return;
       }
    
    //1.- reservo memoria
    nuevo = (struct nodoTarea *)malloc(sizeof(struct nodoTarea *));
    if(nuevo==NULL){
        printf("*** ERROR DE MEMORIA ***");
    }
    
    //2.- Relleno la informacion
    printf("\n\tEscribe el nombre de la tarea: "); fflush(stdin);
    scanf("%[^\n]",nuevo->tituloTarea);
    printf("\n\t\tIntroduce el día de entrega: ");
    scanf("%d", &nuevo->fecha.dia);
    printf("\n\t\tIntroduce el mes de entrega: ");
    scanf("%d", &nuevo->fecha.mes);
    printf("\n\t\tIntroduce el anio de entrega: ");
    scanf("%d", &nuevo->fecha.anio);
    
    
    //3.- Conecto con la lista
    if (listaTarea->primero == NULL) {
           //Es el primero de la lista
           listaTarea->primero = nuevo;
           listaTarea->ultima = nuevo;
       } else {
           //Está en otra posición
           nuevo->anterior = listaTarea->ultima;
           listaTarea->ultima->siguiente = nuevo;
           listaTarea->ultima = nuevo;
       }
       //------igual para todas las situaciones
       nuevo->siguiente = NULL;
   }

void crearListaTareas(struct listaTarea *listaTarea){
    struct nodoTarea *nuevo;
    
    //1.- reservo memoria
    nuevo = (struct nodoTarea *)malloc(sizeof(struct nodoTarea ));
    if(nuevo==NULL){
        printf("*** ERROR DE MEMORIA ***");
    }
    
    //2.- Relleno la informacion

    
    //3.- Conecto con la lista

    if(listaTarea->primero==NULL){                   //Es el primero de la lista
        listaTarea->primero=nuevo;
        listaTarea->ultima=nuevo;
    }else{
        listaTarea->ultima->siguiente=nuevo;        //Está en otra posición
        nuevo->anterior=listaTarea->ultima;
    }
    //------igual para todas las situaciones
    
    nuevo->siguiente=NULL;
    
}
