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
    char nombreAsignatura[20];
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
    struct listaAsignaturas listaAsignaturas;
    struct tipoNodoPersona *siguiente;
    struct tipoNodoPersona *anterior;
};

struct listaAlumnos{
    struct tipoNodoPersona *primero;
    struct tipoNodoPersona *ultimo;
};


//MIS FUNCIONES PRINCIPALES
void addNodoAlumno(struct listaAlumnos *lista);
void addNotaAlumno(struct listaAlumnos *lista);
void showMediaAlumnos(struct listaAlumnos *lista);
void eliminarNota(struct listaAlumnos *lista);

//MIS FUNCIONES SECUNDARIAS
int Menu(void);
void addAlumno(struct listaAlumnos *lista);
void crearListaDelistas(struct listaAlumnos *listaAlumnos);
struct tipoNodoPersona *checkExpediente( struct listaAlumnos *lista);
void mostrarAsignaturas(struct tipoNodoPersona *alumno);
struct asignatura *checkAsignatura(struct listaAlumnos *lista, struct tipoNodoPersona *personaAcomprobar);
void mostrarTodoDeUnAlumno(struct listaAlumnos *listaAlumnos);
void addNodoAsignaturas(struct listaAsignaturas *listaAsignaturas);
struct tipoNodoPersona *checkNombre(char nombreAcomprobar[], struct listaAlumnos *lista);
float calcularMediaAlumno(struct tipoNodoPersona *alumno);

//MI MAIN
int main(int argc, const char * argv[]) {
    int opt=0;
    struct listaAlumnos lista;
    crearListaDelistas(&lista);
    printf("\nBIENVENIDO A LA PRACTICA 6");
    printf("\n--------------------------");
    do {
        opt=Menu();
        switch (opt){
            case 1:
                addNodoAlumno(&lista);
                break;
            case 2:
                addNotaAlumno(&lista);
                break;
            case 3:
                showMediaAlumnos(&lista);
                break;
            case 4:
                break;
            case 5:
                mostrarTodoDeUnAlumno(&lista);
                break;
        }
        
    } while (opt!=0);

    return 0;
}

//CODIGO DE  FUNCIONES PRINCIPALES
void addNotaAlumno(struct listaAlumnos *lista){
    struct tipoNodoPersona *expedienteComprobar=checkExpediente (lista);
    struct asignatura *recorre;
    printf("\n\n2. AÑADIR NOTA AL ALUMNO");
    printf("\n-------------------------");
    if(expedienteComprobar==NULL){
        printf("\nEl alumno no está en la lista");
        return;
    }else{
        recorre=expedienteComprobar->listaAsignaturas.primero;
        mostrarAsignaturas(expedienteComprobar);
        struct asignatura *asignaturaElegida=checkAsignatura(lista, expedienteComprobar);
        
        if(asignaturaElegida==NULL){
            printf("La asignatura elegida no coincide con ninguna de las anteriores");
        }else{
            printf("\nIntroduce la nota que ha obtenido en %s: ",asignaturaElegida->nombreAsignatura);
            scanf("%f",&asignaturaElegida->fNota);
            (asignaturaElegida->convocatoria)++;
        }
    }
    printf("\nSe ha añadido la nota con exito");
    printf("\n\nLas notas actualizadas: ");
    while (recorre!=NULL) {
        printf("\n\t%s COnvocatoria: %d Nota: %.2f",recorre->nombreAsignatura,recorre->convocatoria,recorre->fNota);
        recorre=recorre->siguiente;
    }
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
    fflush(stdin);
    scanf("%[^\n]",nuevo->info.nombre);
    checkNombre(nuevo->info.nombre, lista);
    if( checkNombre(nuevo->info.nombre, lista) == NULL){
        //printf("/nEl usuario no se encuentra en la lista, se pocede a insertar en la lista");
        printf("\nIntroduce el expediente del alumno: ");
        fflush(stdin);
        scanf("%[^\n]",nuevo->info.numexpediente);
        printf("\nIntroduce la titulacion del alumno: ");
        fflush(stdin);
        scanf("%[^\n]",nuevo->info.titulacion);
        
        //inicializo la lista de asignaturas
        printf("\nCuantas asignaturas tiene %s: ", nuevo->info.nombre);
        scanf("%d", &numAsignaturas);
        nuevo->listaAsignaturas.primero=nuevo->listaAsignaturas.ultimo=NULL;
        for (int i=0; i<numAsignaturas; i++) {
            addNodoAsignaturas(&nuevo->listaAsignaturas);
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

void showMediaAlumnos(struct listaAlumnos *lista){
    struct tipoNodoPersona *recorre=lista->primero;
    printf("\n\n3. MEDIA DE LOS ALUMNOS: ");
    printf("\n------------------------");
    if(lista->primero==NULL){
        printf("\nLa lista está vacía");
        return;
    }else{
        while (recorre!=NULL) {
            printf("\n%s, media: %.2f",recorre->info.nombre,calcularMediaAlumno(recorre));
            recorre=recorre->siguiente;
        }
    }
 
}

void eliminarNota(struct listaAlumnos *lista){
    printf("\n4. ELIMINAR NOTA ASIGNATURA");
    printf("\n---------------------------");
    struct tipoNodoPersona *persona =checkExpediente(lista);
    struct asignatura *asignatura=NULL;
    if(persona==NULL){
        printf("\nEl expediente introducido no se encuentra en la lista");
        return;
    }
    while (asignatura==NULL) {
        printf("La asignatura escogida no está en la lista, prueba otra vez");
        asignatura=checkAsignatura(lista, persona);
    }
    if(asignatura->fNota!=0){
        asignatura->fNota=0;
    }
    
}


//CODIGO DE  FUNCIONES SECUNDARIAS
int Menu(void){
    int opt=0;
    do{
        
        
        printf("\nMENU:"
               "\n\t1. Añadir un registro de alumno \n\t2. Añadir nota al alumno \n\t3. Mostrar nota media de las asignaturas aprobadas de todos \n\t4. Eliminar nota asignatura\n\t5. Mostrar todo\n\t6. Salir del programa\nSelecciona una opción: ");
        scanf("%d",&opt);
    }while (opt<0 || opt>6);
    return opt;
}

void addNodoAsignaturas(struct listaAsignaturas *listaAsignaturas){
    struct asignatura *nuevo;
    
    //1.- Reservo memoria
    nuevo=(struct asignatura*)malloc(sizeof(struct asignatura));
    if(nuevo==NULL){
        printf("\nERROR DE MEMORIA, NO SE HA PODDIDO CREAR ASIGNATURA");
    }
    //2.- Relleno la información
    printf("Introduce el nombre de la asignatura: ");  fflush(stdin);
    scanf("%s", nuevo->nombreAsignatura);
    printf("Introduce la nota obtenida: ");
    scanf("%f", &nuevo->fNota);
    printf("Introduce la convocatoria: ");
    scanf("%d", &nuevo->convocatoria);
    
    //3.- Conecto con la lista
    if(listaAsignaturas->primero==NULL){
        listaAsignaturas->primero=nuevo;
    }else{
        listaAsignaturas->ultimo->siguiente=nuevo;
    }
    nuevo->siguiente = NULL;
    nuevo->anterior = listaAsignaturas->ultimo;
    listaAsignaturas->ultimo = nuevo;
}

struct tipoNodoPersona *checkNombre(char nombreAcomprobar[], struct listaAlumnos *lista){
    struct tipoNodoPersona *recorre=lista->primero;
    
    if(recorre==NULL){
       // printf("\nLa lista está vacía");
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

struct tipoNodoPersona *checkExpediente(struct listaAlumnos *lista){
    char expediente[6];
    struct tipoNodoPersona *recorre=lista->primero;
    printf("\nIntroduce el expediente del alumno: ");
    scanf("%s",expediente);
    if(recorre==NULL){
        printf("\nLa lista está vacía");
        return recorre;
    }
    
    while (strcmp(expediente, recorre->info.numexpediente)!=0) {
        recorre=recorre->siguiente;
    }
    return recorre;
}

void mostrarAsignaturas(struct tipoNodoPersona *alumno){
    struct asignatura *recorre = alumno->listaAsignaturas.primero;
    printf("\nLas asignaturas de %s: ",alumno->info.nombre);
    while (recorre!=NULL) {
        printf("\n\t %s",recorre->nombreAsignatura);
        recorre=recorre->siguiente;
    }
}

struct asignatura *checkAsignatura(struct listaAlumnos *lista, struct tipoNodoPersona *personaAcomprobar){
    struct asignatura *recorre=personaAcomprobar->listaAsignaturas.primero;
    char asignaturaAcomprobar[20];
    printf("\nEscoge una asignatura: ");
    fflush(stdin);
    scanf("%[^\n]",asignaturaAcomprobar);
    
    while (recorre!=NULL&&(strcmp(recorre->nombreAsignatura, asignaturaAcomprobar)!=0)) {
        recorre=recorre->siguiente;
    }
    return recorre;
}

void mostrarTodoDeUnAlumno(struct listaAlumnos *listaAlumnos){
    struct tipoNodoPersona *recorre=listaAlumnos->primero;
    printf("\nEL expediente de todos los alumnos: ");
    while (recorre!=NULL) {
        printf("\n\tExpediente: %s Nombre: %s",recorre->info.numexpediente, recorre->info.nombre);
        recorre=recorre->siguiente;
    }
}

float calcularMediaAlumno(struct tipoNodoPersona *alumno){
    float contador=0,sumador=0,media=0;
    struct asignatura *recorre=alumno->listaAsignaturas.primero;
    
    while (recorre!=NULL) {
        if(recorre->fNota >=5){
            sumador=sumador + recorre->fNota;
            contador++;
        }
        recorre=recorre->siguiente;
    }
    media=sumador/contador;
    return media;
}
