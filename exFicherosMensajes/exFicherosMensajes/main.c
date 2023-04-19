//
//  main.c
//  exFicherosMensajes
//
//  Created by Ivan Zheng on 18/4/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NodoMensaje{
    char nickEmisor[10];
    char nickReceptor[10];
    char texto[500];
    struct NodoMensaje *siguiente;
    struct NodoMensaje *anterior;
};

struct listaMansajes{
    struct NodoMensaje *primero;
    struct NodoMensaje *ultimo;
};

struct nodoUsuario{
    char numTelefono[10];
    char nick[10];
    struct listaMansajes *mensajes;
    struct nodoUsuario *siguiente;
    struct nodoUsuario *anterior;
};

struct listaUsuarios{
    struct nodoUsuario *primero;
    struct nodoUsuario *ultimo;
};

void menu(void);
void crearListadeListas(struct listaUsuarios *lista);
void addUsuario(struct listaUsuarios *lista);
struct nodoUsuario *usuarioComprobado(char nick[],struct listaUsuarios *lista);

// ***** MI MAIN ******
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    struct listaUsuarios listaUsuarioss;
    crearListadeListas(&listaUsuarioss);
    
    
    return 0;
}

void menu(void){
    printf("\n*** MENU ***");
    printf("\n\t1. Add usuario");
    printf("\n\t1. Add usuario");
    printf("\n\t1. Add usuario");
}

void crearListadeListas(struct listaUsuarios *lista){
    int numUsuario;
    
    printf("\nCuantos usuarios quieres crear: ");
    scanf("%d",&numUsuario);
    
    for (int i = 0; i<numUsuario; i++) {
        printf("\nPara usuario %d: ", i+1);
        addUsuario(lista);
    }
}

void addUsuario(struct listaUsuarios *lista){
    struct nodoUsuario *nuevo;
    
    //1.- Reservo espacio
    nuevo=(struct nodoUsuario *)malloc(sizeof(struct nodoUsuario));
    if(nuevo==NULL){
        printf("\n** ERROR DE MEMORIA **");
    }
    
    //2.- Relleno la información
    printf("\n\tIntroduce el numero de teléfono: ");
    scanf("%s",nuevo->numTelefono);
    printf("\n\tIntroduce el nick del usuario: ");
    scanf("%s",nuevo->nick);
    nuevo->mensajes=NULL;

    //3.- Conecto con la lista
    if(lista->primero==NULL){    //la lista está vacía
        lista->primero=nuevo;
    }else{
        lista->ultimo->siguiente=nuevo;
    }
    nuevo->anterior=lista->ultimo;
    lista->ultimo=nuevo;
    nuevo->siguiente=NULL;
    
    }


struct nodoUsuario *usuarioComprobado(char nick[],struct listaUsuarios *lista){
    struct nodoUsuario *recorre=lista->primero;
    
    //1.- La lista está vacía
    if(lista->primero==NULL){
        return NULL;
    }else{
    //2.- La lista no está vacía hay que cmparar
        while (recorre!=NULL) {
            if(  strcmp(nick, recorre->nick) ==0){
                return recorre;
            }
            recorre=recorre->siguiente;
        }
    }
    
    return recorre;
}
