//
//  main.c
//  ejercicio4PracticarListasDeListas
//
//  Created by Ivan Zheng on 14/4/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//*** MIS STRUCTS ***
struct infoPersona{
    char dni[8];
    char nombre[20];
};

struct nodoPersona{
    struct infoPersona infoPersona;
    struct nodoPersona *siguiente;
    struct nodoPersona *anterior;
};

struct listaPersonas{
    struct nodoPersona *primero;
    struct nodoPersona *ultimo;
};

struct infoVentanilla{
    int numVentanilla;
    char operacionArealizar[20];
    struct listaPersonas listaPersonas;
};

struct nodoVentanilla{
    struct infoVentanilla infoVentanilla;
    struct nodoVentanilla *siguiente;
    struct nodoVentanilla *anterior;
};

struct listaVentanillas{
    struct nodoVentanilla *primero;
    struct nodoVentanilla *ultimo;
};



//*** MIS FUNCIONES PRINCIPALES***
void crearListadeListas(struct listaVentanillas *listaVentanillas);
void visualizarNumVentanillas(struct listaVentanillas listaVentanillas);
void realizarCambioVentanilla(struct listaVentanillas *listaVentanillas);

//*** MIS FUNCIONES AUXILIARES ***
void addNodoVentanilla(struct listaVentanillas *listaVentanillas);
void addNodoPersona(struct listaPersonas *listaPersonas);
int menu(void);
struct nodoVentanilla *checkVentanilla(struct listaVentanillas listaVentanillas, int numVentanilla);
void showPersonas(struct listaPersonas listaPersonas);
struct nodoPersona *checkDNI(struct nodoVentanilla *ventanilla, char dniAcambiar[]);
void addPersonaAotraVentanilla(struct listaPersonas *listapersonas, struct nodoPersona *personaCambiar);
void eliminarDeVentanilla(struct listaPersonas *listapersonas, struct nodoPersona *personaCambiar);
void showLista(struct listaVentanillas listaVentanilla);
void showListaPersonas(struct listaPersonas listaPersonas);

int main(int argc, const char * argv[]) {

    struct listaVentanillas lista;
    lista.primero=NULL;
    lista.ultimo=NULL;
    crearListadeListas(&lista);
    int opc;
    
    do{
        opc=menu();
        switch (opc) {
            case 1:
                printf("\n1. Visualizar numero ventanillas");
                printf("\n--------------------------------");
                visualizarNumVentanillas(lista);
                break;
            case 2:
                printf("\n2. Cambio de ventanilla");
                printf("\n-----------------------");
                realizarCambioVentanilla(&lista);
                break;
                
            default:
                printf("\n*** HAS SALIDO DEL PROGRAMA ***");
                break;
        }

    }while(opc!=0);
    
        
    return 0;
}

//*** MIS FUNCIONES PRINCIPALES ***
void visualizarNumVentanillas(struct listaVentanillas listaVentanillas){
    struct nodoVentanilla *recorre=listaVentanillas.primero;
    struct nodoPersona *recorrePersonas;
    int numPersonas=0;
    
    if(recorre==NULL){
        printf("\nLa lista está vacía");
        return;
    }
    
    while (recorre!=NULL) {
        printf("\nNumero de Ventanilla: %d",recorre->infoVentanilla.numVentanilla);
        recorrePersonas=recorre->infoVentanilla.listaPersonas.primero;
        
        //hago otro bucle para contar las personas
        while (recorrePersonas!=NULL) {
            numPersonas++;
            recorrePersonas=recorrePersonas->siguiente;
        }
        printf("\n\tNumero de Personas: %d",numPersonas);
        recorre=recorre->siguiente;
    }
}

void realizarCambioVentanilla(struct listaVentanillas *listaVentanillas){
    int numVentanillaOrigen;
    int numVentanillaDestino;
    char dniPersonaCambiar[8];
    struct nodoVentanilla *ventanillaOrigen;
    struct nodoVentanilla *ventanillaDestino;
    struct nodoPersona *personaCambiar;
    
    visualizarNumVentanillas(*listaVentanillas);
    printf("\n\tA qué ventanilla quieres acceder: ");
    scanf("%d",&numVentanillaOrigen);
    ventanillaOrigen=checkVentanilla(*listaVentanillas, numVentanillaOrigen);
        if(ventanillaOrigen==NULL){
            printf("\n\tLa ventanilla escogida no se encuentra en la lista");
            return;
        }
    printf("\nQué DNI quieres cambiar de ventanilla: "); fflush(stdin);
    scanf("%s",dniPersonaCambiar);
    personaCambiar = checkDNI(ventanillaOrigen, dniPersonaCambiar);
        if(personaCambiar==NULL){
            printf("\nEl dni escogido no se encuentra en la lista.");
            return;
        }
    printf("\n\tA qué ventanilla quieres moverte: ");
    scanf("%d",&numVentanillaDestino);
    ventanillaDestino = checkVentanilla(*listaVentanillas, numVentanillaDestino);
        if(ventanillaDestino==NULL){
            printf("\nLa ventanilla escogida no se encuentra en la lista");
            return;
        }
    eliminarDeVentanilla(&ventanillaOrigen->infoVentanilla.listaPersonas, personaCambiar);
    addPersonaAotraVentanilla(&ventanillaDestino->infoVentanilla.listaPersonas, personaCambiar);
    printf("\nEl cambio se ha realizado con éxito");
}


//*** MIS FUNCIONES AUXILIARES ***
int menu(void){
    int opc;
    do{
        printf("\n\n*** MENU ***");
        printf("\n\t1. Visualizar numero ventanillas");
        printf("\n\t2. Cambio de ventanilla");
        printf("\n\t0. Salir del programa");
        scanf("%d",&opc);
    }while(opc<0||opc>3);
    
    return opc;
}

void crearListadeListas(struct listaVentanillas *listaVentanillas){
    int i,n;
    //hago que la lista esté vacía
    listaVentanillas->primero=listaVentanillas->ultimo=NULL;
    printf("\nCuantas ventanillas quieres crear?: ");
    scanf("%d",&n);
    
    for (i=0; i<n; i++) {
        printf("Ventanilla %d",i+1);
        addNodoVentanilla(listaVentanillas);
    }
    
}

void addNodoVentanilla(struct listaVentanillas *listaVentanillas){
    int numPersonas;
    //1.- Reservo espacio
    struct nodoVentanilla *nuevo;
    nuevo=(struct nodoVentanilla *)malloc(sizeof(struct nodoVentanilla));
        if(nuevo==NULL){
            printf("\n** ERROR EN LA MEMORIA**");
            return;;
        }
    //2.- Relleno información
    printf("\nQué numero le quieres poner a la ventanilla: ");
    scanf("%d",&nuevo->infoVentanilla.numVentanilla);
    printf("\nQué operación quieres realizar en la ventanilla: "); fflush(stdin);
    scanf("%s",nuevo->infoVentanilla.operacionArealizar);
    printf("\nCuántas personas tienes en la ventanilla: ");
    scanf("%d",&numPersonas);
    
    for (int i=0; i<numPersonas; i++) {
        addNodoPersona(&nuevo->infoVentanilla.listaPersonas);
    }
    //3.- Conecto con la lista
    if(listaVentanillas->primero==NULL){    //la lista está vacía
        listaVentanillas->primero=nuevo;
    }else{                                  //la lista no está vacía
        listaVentanillas->ultimo->siguiente=nuevo;
    }
    nuevo->siguiente=NULL;
    nuevo->anterior=listaVentanillas->ultimo;
    listaVentanillas->ultimo = nuevo;
}

void addNodoPersona(struct listaPersonas *listaPersonas){
    struct nodoPersona *nuevo;
    
    //1.- Reservo espacio
    nuevo=(struct nodoPersona *)malloc(sizeof(struct nodoPersona));
    if(nuevo==NULL){
        printf("\n*** ERROR DE MEMORIA ***");
    }
    //2.- Relleno información
    printf("\n\tIntroduce el nombre de la persona: "); fflush(stdin);
    scanf("%s",nuevo->infoPersona.nombre);
    printf("\n\tIntroduce el dni de la persona: "); fflush(stdin);
    scanf("%s",nuevo->infoPersona.dni);
    
    //3.- Conecto con la lista
    if(listaPersonas->primero==NULL){   //La lista está vacía
        listaPersonas->primero=nuevo;
    }else{                              //La lista no está vacía
        listaPersonas->ultimo->siguiente=nuevo;
    }
    nuevo->siguiente = NULL;
    nuevo->anterior = listaPersonas->ultimo;
    listaPersonas->ultimo = nuevo;
    
}

struct nodoVentanilla *checkVentanilla(struct listaVentanillas listaVentanillas, int numVentanilla){
    struct nodoVentanilla *recorre=listaVentanillas.primero;
    
    while (recorre!=NULL) {
        if(numVentanilla == recorre->infoVentanilla.numVentanilla){
            return recorre;
        }
        recorre=recorre->siguiente;
    }
    return recorre;
}

void showPersonas(struct listaPersonas listaPersonas){
    struct nodoPersona *recorre=listaPersonas.primero;
    printf("\nLista de personas: ");
    while (recorre!=NULL) {
        printf("\n\tNombre: %s DNI: %s",recorre->infoPersona.nombre, recorre->infoPersona.dni);
    }
}

struct nodoPersona *checkDNI(struct nodoVentanilla *ventanilla, char dniAcambiar[]){
    struct nodoPersona *recorre=ventanilla->infoVentanilla.listaPersonas.primero;
    
    while (recorre!=NULL) {
        if(strcmp(dniAcambiar, recorre->infoPersona.dni)==0){
            return recorre;
        }
        recorre=recorre->siguiente;
    }
    return recorre;
}

void addPersonaAotraVentanilla(struct listaPersonas *listapersonas, struct nodoPersona *personaCambiar){
    //Ya está reservado y rellenado
    
    if(listapersonas->primero==NULL){       //Está vacío así que vamos a hacerlo el primero
        listapersonas->primero=personaCambiar;
    }else{
        listapersonas->ultimo->siguiente=personaCambiar;
    }
    //En todos los casos
    personaCambiar->siguiente=NULL;
    personaCambiar->anterior=listapersonas->ultimo;
    listapersonas->ultimo=personaCambiar;
}

void eliminarDeVentanilla(struct listaPersonas *listapersonas, struct nodoPersona *personaCambiar){
    //NO hay que liberar memoria solo lo estamos moviendo
    
    //Caso 1: es el unico en la lista
    if(listapersonas->primero==personaCambiar && listapersonas->ultimo==personaCambiar){
        listapersonas->primero = NULL;
        listapersonas->ultimo  = NULL;
      
    //Caso 2: es el primero de la lista
    }else if(listapersonas->primero==personaCambiar){
        listapersonas->primero=personaCambiar->siguiente;
        listapersonas->primero->anterior=NULL;
        
    //Caso 3: es el ultimo de la lista
    }else if(listapersonas->ultimo==personaCambiar){
        listapersonas->ultimo = personaCambiar->anterior;
        listapersonas->ultimo = NULL;
        
    //Caso 4: esta en el medio de la lista
    }else{
        personaCambiar->siguiente->anterior= personaCambiar->anterior;
        personaCambiar->anterior->siguiente = personaCambiar->siguiente;
    }
    
    //NO LIBERO MEMORIA PORQUE SOLO ESTOY MOVIENDO
}

void showLista(struct listaVentanillas listaVentanilla){
    
}
