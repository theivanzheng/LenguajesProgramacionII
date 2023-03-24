//
//  main.c
//  practica5
//
//  Created by Ivan Zheng on 23/3/23.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//******    MIS STRUCTS ******
struct infoPersona{
    char dni[9];
    char nombre[20];
};
struct nodoPersona {
    struct infoPersona informacion;
    struct nodoPersona *siguiente;
    struct nodoPersona *anterior;
};
struct listaPersonas {
    struct nodoPersona *primero;
    struct nodoPersona *ultimo;
};
struct infoVentanilla{
    int numeroVentanilla;
    char operacion[20];
};

struct nodoVentanilla {
    struct infoVentanilla informacion;
    struct listaPersonas personas; //lista doble de personas en la ventanilla
    struct nodoVentanilla *siguiente;
    struct nodoVentanilla *anterior;
};

struct listaVentanillas {
    struct nodoVentanilla *primero;
    struct nodoVentanilla *ultimo;
};


//******    PROTOTIPO DE MIS FUNCIONES  *****
void crearListaDelistas(struct listaVentanillas *listaVentanillas);
void addNodoVentanilla(struct listaVentanillas *listaVentanillas);
void addNodoPersona(struct listaPersonas *listaPersonas);
int menu(void);
void visualizar(struct nodoVentanilla *primero);
struct nodoVentanilla *buscarVentanilla(struct nodoVentanilla *primero, int numeroVentanillaBuscar);
struct nodoPersona *buscarPersona(struct nodoPersona *primero, char dniBuscar[]);
void eliminar(struct listaPersonas *listaPersonas, struct nodoPersona *personaMover);
void addPersona(struct listaPersonas *listaPersonas,struct nodoPersona *personaAñadir);
void gestionarCambioVentanilla(struct nodoVentanilla *primero);
void ponerseCola(struct nodoVentanilla *primero, struct listaVentanillas *listaVentanilla);
void atender(struct nodoVentanilla *primero, struct listaVentanillas *listaVentanilla);
void eliminarPrimero(struct nodoVentanilla *buscada, struct listaVentanillas *listaVentanilla);
void mostrarAtendido(struct nodoVentanilla *buscada);

//EMPIEZO MI CODIGO
int main() {
    struct listaVentanillas listaVentanillas;
    int opc;
    
    crearListaDelistas(&listaVentanillas);
    do {
        opc = menu();
        switch (opc)
        {
            case 1:
                break;
            case 2:gestionarCambioVentanilla(listaVentanillas.primero);
                break;
            case 3:visualizar(listaVentanillas.primero);
                break;
            case 4:
                ponerseCola(listaVentanillas.primero, &listaVentanillas);
                break;
            case 5:
                atender(listaVentanillas.primero, &listaVentanillas);
                break;
            case 6:
                break;
        }
    } while (opc != 0);
    return 0;
}

int menu()
{
    int opc;
    
    do
    {
        printf("\n1. Visualizar los numeros de ventanillas y el numero de personas a la cola");
        printf("\n2. Realizar un cambio de ventanilla");
        printf("\n3. Visualizar todo");
        printf("\n4. Ponerse a la cola");
        printf("\n5. Atender a una persona");
        printf("\n6. Cerrar ventanilla");
        printf("\n0. Salir");
        printf("\nIntroduce la opcion deseada... ");
        scanf("%d", &opc);
    } while ((opc<0) || (opc>6));
    return opc;
}



void eliminar(struct listaPersonas *listaPersonas, struct nodoPersona *personaMover){
    struct nodoPersona *anterior, *siguiente;
    anterior = personaMover->anterior;
    siguiente = personaMover->siguiente;
    //ver qué casos tengo
    //tratar todos los casos dejando la lista bien conectada
    //único, primero, último, otro
    if (listaPersonas->primero == personaMover && listaPersonas->ultimo == personaMover){
        listaPersonas->primero = NULL;
        listaPersonas->ultimo  = NULL;
    }
    else if (listaPersonas->primero == personaMover){
        listaPersonas->primero = siguiente;
        siguiente->anterior = NULL;
    }
    else if (listaPersonas->ultimo == personaMover){
        listaPersonas->ultimo = anterior;
        anterior->siguiente = NULL;
    }
    else{
        siguiente->anterior = anterior;
        anterior->siguiente = siguiente;
    }
    
    //IMPORTANTE NO tengo que liberar pq estoy moviendo
}
void addPersona(struct listaPersonas *listaPersonas,struct nodoPersona *personaAñadir){
    
    //IMPORTANTE ya está reservado y rellenado
    //solo conecto con la lista, por el final
    if (listaPersonas->primero == NULL){
        //si está vacía este es el único, pt el primero
        listaPersonas->primero = personaAñadir;
    }else{
        listaPersonas->ultimo->siguiente = personaAñadir;
    }
    //en todos los casos
    personaAñadir->siguiente = NULL;
    personaAñadir->anterior  = listaPersonas->ultimo;
    listaPersonas->ultimo = personaAñadir;
    
}

//EJERCICIO 1
void ponerseCola(struct nodoVentanilla *primero, struct listaVentanillas *listaVentanilla){
    int numeroVentanilla=0;
    printf("\nVamos a introducir el número ventanilla: ");
    scanf("%d",&numeroVentanilla);
    struct nodoVentanilla *buscada =buscarVentanilla(primero, numeroVentanilla);
    if(buscada==NULL){
        printf("\nNo se ha encontrado la ventanilla que buscas");
    }else{
        addNodoPersona(&buscada->personas);
    };
}

//EJERCICIO 2: ATENDER A UNA PERSONA
void atender(struct nodoVentanilla *primero, struct listaVentanillas *listaVentanilla){
    int ventanillaBuscar=0;
    int contador=0;
    struct nodoVentanilla *recorre;
    printf("\nIntroduce la ventanilla que quieres atender: ");
    scanf("%d",&ventanillaBuscar);
    struct nodoVentanilla *buscada= buscarVentanilla(primero,ventanillaBuscar); //esto me da la ventanilla de la que quiero sacar su lista personas y atender al primero
    
    if(buscada==NULL){
        printf("\nNo se ha encontrado la ventanilla que quieres");
    }else{
        eliminarPrimero(buscada, listaVentanilla);
        
    }
}


void gestionarCambioVentanilla(struct nodoVentanilla *primero){
    int numeroVentanillaOrigen, numeroVentanillaDestino;
    char dniPersonaCambiar[9];
    
    struct nodoVentanilla *ventanillaOrigen;
    struct nodoVentanilla *ventanillaDestino;
    struct nodoPersona *personaCambiar;
    
    
    //introducir datos iniciales
    printf("\n Introduce el n. de la ventanilla en la que estás: ");
    scanf("%d",&numeroVentanillaOrigen);
    ventanillaOrigen = buscarVentanilla(primero, numeroVentanillaOrigen);
    if (ventanillaOrigen == NULL){
        printf("\n No existe la ventanilla numero %d",numeroVentanillaOrigen);
        printf("\n IMPOSIBLE el cambio");
        return;
    }
    //pido el dni
    printf("\n Introduce tu dni: ");fpurge(stdin);
    scanf("%s",dniPersonaCambiar);
    //personaCambiar = buscarPersona(ventanillaOrigen->personas.primero, dniPersonaCambiar);
    if (personaCambiar == NULL){
        printf("\n No estas en la cola de esa ventanilla");
        printf("\n IMPOSIBLE el cambio");
        return;
    }
    printf("\n Introduce el n. de la ventanilla destino: ");
    scanf("%d",&numeroVentanillaDestino);
    ventanillaDestino =  buscarVentanilla(primero, numeroVentanillaDestino);
    if (ventanillaDestino == NULL){
        printf("\n No existe la ventanilla numero %d",numeroVentanillaDestino);
        printf("\n IMPOSIBLE el cambio");
        return;
    }
    eliminar(&ventanillaOrigen->personas, personaCambiar);
    addPersona(&ventanillaDestino->personas, personaCambiar);
    
    
}

void visualizarPersonas(struct nodoPersona *primero){
    struct nodoPersona *recorre = primero;
    int contador = 1;
    if (primero == NULL){
        printf("\n\t No hay personas a la cola");
        return;
    }
    while (recorre != NULL){
        printf("\n\t %d: dni:%s nombre:%s",contador,recorre->informacion.dni,recorre->informacion.nombre);
        contador += 1;
        recorre = recorre->siguiente;
    }
    printf("\n\n");
}

void visualizar(struct nodoVentanilla *primero){
    struct nodoVentanilla *recorre = primero;
    if (primero == NULL){
        printf("\n Lista de ventanillas vacía");
        return;
    }
    while (recorre != NULL){
        printf("\n Ventanilla n. %d: %s",recorre->informacion.numeroVentanilla,recorre->informacion.operacion);
        visualizarPersonas(recorre->personas.primero);
  
        recorre = recorre->siguiente;
    }
    
}

void crearListaDelistas(struct listaVentanillas *listaVentanillas) {
    int n, i;
    
    //inicializo la lista
    listaVentanillas->primero = listaVentanillas->ultimo = NULL; //lista vacÌa
    printf("\n Introduce el numero de ventanillas que hay: ");scanf("%d", &n);
    
    for (i = 0;i < n; i++) {
        printf("\n Para la ventanilla %d",i+1);
        addNodoVentanilla(listaVentanillas);

    }
}

void addNodoVentanilla(struct listaVentanillas *listaVentanillas) {
    //aÒado por el final
    struct nodoVentanilla *nuevo;
    int numPersonas, i;
    
    //1. reservo
    nuevo = (struct nodoVentanilla *)malloc(sizeof(struct nodoVentanilla));
    if (nuevo == NULL) {
        printf("\n ERROR de memoria");
        return;
    }
    
    //2. relleno
    printf("\n Introduce la informaciÛn del numero de la ventanilla: ");
    scanf("%d", &nuevo->informacion.numeroVentanilla);
    printf("\n Introduce la operacion de la ventanilla: ");fflush(stdin);
    fpurge(stdin);
    scanf("%s", nuevo->informacion.operacion);
    //tb relleno las personas
    printf("\n Introduce el numero de personas: ");
    scanf("%d", &numPersonas);
    //inicializar la lista de personas
    nuevo->personas.primero = nuevo->personas.ultimo = NULL;
    
    for (i=0;i<numPersonas;i++){
        addNodoPersona(&nuevo->personas);
    }
 
    //3. Conecto con  la lista
    if (listaVentanillas->primero == NULL) {
        //lista vacia aÒado el primero
        listaVentanillas->primero = nuevo;
    }
    else {//no esta vacÌa, va despues del ultimo
        listaVentanillas->ultimo->siguiente = nuevo;
    }
    nuevo->siguiente = NULL;
    nuevo->anterior = listaVentanillas->ultimo;
    listaVentanillas->ultimo = nuevo;
}

void addNodoPersona(struct listaPersonas *listaPersonas) {
    struct nodoPersona *nuevo;
    //1. Reservo
    nuevo = (struct nodoPersona *)malloc(sizeof(struct nodoPersona));
    if (nuevo == NULL) {
        printf("\n ERROR de memoria");
        return;
    }
    
    //2.Relleno
    printf("\n DNI de la persona: ");fflush(stdin);
    fpurge(stdin);
    scanf("%s", nuevo->informacion.dni);
    printf("\n Nombre de la persona: ");fflush(stdin);
    fpurge(stdin);
    scanf("%s", nuevo->informacion.nombre);
    
    //3. Conecto
    if (listaPersonas->primero == NULL) {
        //lista vacia aÒado el primero
        listaPersonas->primero = nuevo;
    }
    else {//no esta vacÌa, va despues del ultimo
        listaPersonas->ultimo->siguiente = nuevo;
    }
    nuevo->siguiente = NULL;
    nuevo->anterior = listaPersonas->ultimo;
    listaPersonas->ultimo = nuevo;
}


struct nodoVentanilla *buscarVentanilla(struct nodoVentanilla *primero, int numeroVentanillaBuscar){
    struct nodoVentanilla *recorre = primero;
    while (recorre!=NULL && recorre->informacion.numeroVentanilla != numeroVentanillaBuscar) {
        recorre=recorre->siguiente;
    }
    return recorre; //Aquí ya nos retorna la posición de la ventanilla
}


void eliminarPrimero(struct nodoVentanilla *buscada, struct listaVentanillas *listaVentanilla){
   //Siempre vamos a coger el primero entonces nos ahorramos el codigo para los que sean de en medio
    mostrarAtendido(buscada);

    
    //caso 1: que sea el unico
    if(buscada->personas.primero==buscada->personas.ultimo){
        buscada->personas.primero=NULL;
        buscada->personas.ultimo=NULL;
        
    //Caso 2: que sea el primero
    }else if(buscada->personas.primero->anterior==NULL){
        //respecto al antiguo primero
        buscada->personas.primero->siguiente=NULL;
        
        //respecto al nuevo primero
        buscada->personas.primero->siguiente = buscada->personas.primero; //Convierto el anterior siguiente al primero
        buscada->personas.primero->anterior=NULL; //Su anterior es NULL
    }

}

void mostrarAtendido(struct nodoVentanilla *buscada){
    printf("\nSe acaba de atender a : %s, con DNI: %s, en la ventanilla %d", buscada->personas.primero->informacion.nombre, buscada->personas.primero->informacion.dni, buscada->informacion.numeroVentanilla);
}
