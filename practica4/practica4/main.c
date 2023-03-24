#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
struct fecha{
    int dia;
    int mes;
    int anio;
};

struct infoUser{
    char id[20];
    char texto[165];
    struct fecha fecha;
};

struct tipoNodo{
    struct infoUser userInfo;
    struct tipoNodo *previous;
    struct tipoNodo *next;
};

struct listaDoble{
    struct tipoNodo *primero;
    struct tipoNodo *ultimo;
};

int menu(void);
void addEntryEnd(struct listaDoble *lista );
void fillInfo(struct infoUser *informacion);
void showAll(struct listaDoble lista);
void show(struct tipoNodo recorre);
void showLast(struct listaDoble lista);
void showUserPosts(struct listaDoble lista);
int main(int argc, const char * argv[]) {
    int opc;
    
    struct listaDoble lista;
    lista.ultimo=NULL;
    lista.primero=NULL;
   // struct tipoNodo *buscado;
    
    
    do{
        opc = menu();
        switch (opc){
            case 1://añadir entrada nueva
                addEntryEnd(&lista);
                break;
            case 2:
                showLast(lista);
                break;
            case 3:
                showUserPosts(lista);
                break;
            case 4:
                break;
            case 5:
                showAll(lista);
                break;
        }
        
    }while (opc != 0);
    
    
    return 0;
}

int menu(){
    int opc;
    do{
        printf("\n--------------------------------------------");
        printf("\nMENU: ");
        printf("\n\t 1. Añadir entrada");
        printf("\n\t 2. Mostrar ultima entrada de un usuario");
       printf("\n\t 3. Visualizar entradas de un usuario");
       printf("\n\t 4. Añadir entrada para fecha concreta");
        printf("\n\t 5. Visualizar todo");
        printf("\n\t 0. SALIR");

        printf("\n Introduce una opción: ");
        scanf("%d",&opc);
        printf("\n--------------------------------------------");

    }while(opc<0 || opc>5);
    return opc;
}
void fillInfo(struct infoUser *newUser){
    printf("\n Introduce el id de usuario: ");
    fpurge(stdin);
    scanf("%s",newUser->id);
    printf("\n Introduce el texto: ");
    fpurge(stdin);
    scanf("%[^\n]",newUser->texto);
    
    //introducir fecha
    printf("\nIntroduce el dia: ");
    scanf("%d",&newUser->fecha.dia);
    printf("\nIntroduce el mes: ");
    scanf("%d",&newUser->fecha.mes);
    printf("\nIntroduce el anio: ");
    scanf("%d",&newUser->fecha.anio);
}


void addEntryEnd(struct listaDoble *lista ){
    struct tipoNodo *nuevo;
    //1.- Reservo memoria
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    if(nuevo==NULL){
        printf("\n*ERROR DE MEMORIA*");
    }
    //2.- Relleno
    fillInfo(&nuevo->userInfo);
    
    //3.- Conecto
    if(lista->primero == NULL){ //La lista está vacia
        lista->primero = nuevo;
        lista->ultimo = nuevo;
        nuevo->previous = NULL;
        nuevo->next = NULL;
    }else{
        struct tipoNodo *recorre = lista->ultimo;
        while(recorre != NULL){
            if(recorre->userInfo.fecha.anio < nuevo->userInfo.fecha.anio){
                // insert at end
                nuevo->previous = recorre;
                nuevo->next = NULL;
                recorre->next = nuevo;
                lista->ultimo = nuevo;
                break;
            }
            else if(recorre->userInfo.fecha.anio == nuevo->userInfo.fecha.anio
                    && recorre->userInfo.fecha.mes < nuevo->userInfo.fecha.mes){
                // insert at end
                nuevo->previous = recorre;
                nuevo->next = NULL;
                recorre->next = nuevo;
                lista->ultimo = nuevo;
                break;
            }
            else if(recorre->userInfo.fecha.anio == nuevo->userInfo.fecha.anio
                    && recorre->userInfo.fecha.mes == nuevo->userInfo.fecha.mes
                    && recorre->userInfo.fecha.dia <= nuevo->userInfo.fecha.dia){
                // insert at end
                nuevo->previous = recorre;
                nuevo->next = NULL;
                recorre->next = nuevo;
                lista->ultimo = nuevo;
                break;
            }
            else if(recorre->previous == NULL){
                // insert at beginning
                nuevo->previous = NULL;
                nuevo->next = recorre;
                recorre->previous = nuevo;
                lista->primero = nuevo;
                break;
            }
            else if(recorre->previous->userInfo.fecha.anio < nuevo->userInfo.fecha.anio){
                // insert in between
                nuevo->previous = recorre->previous;
                nuevo->next = recorre;
                recorre->previous->next = nuevo;
                recorre->previous = nuevo;
                break;
            }
            else if(recorre->previous->userInfo.fecha.anio == nuevo->userInfo.fecha.anio
                    && recorre->previous->userInfo.fecha.mes < nuevo->userInfo.fecha.mes){
                // insert in between
                nuevo->previous = recorre->previous;
                nuevo->next = recorre;
                recorre->previous->next = nuevo;
                recorre->previous = nuevo;
                break;
            }
            else if(recorre->previous->userInfo.fecha.anio == nuevo->userInfo.fecha.anio
                    && recorre->previous->userInfo.fecha.mes == nuevo->userInfo.fecha.mes
                    && recorre->previous->userInfo.fecha.dia > nuevo->userInfo.fecha.dia){
            

void show(struct tipoNodo recorre){
    printf("\nUsuario: %s", recorre.userInfo.id);
    printf("\n\tTexto: %s",recorre.userInfo.texto);
    printf("\n\tFecha de publicacion: %d - %d - %d", recorre.userInfo.fecha.dia, recorre.userInfo.fecha.mes , recorre.userInfo.fecha.anio);
}

void showAll(struct listaDoble lista){
    struct tipoNodo *recorre=lista.primero;
    
    if(recorre==NULL){
        printf("\n La lista está vacía");
    }else{
        while (recorre!=NULL) {
            show(*recorre);
            recorre=recorre->next;
        }
    }
    printf("\nSe ha termindado de mostrar la lista");
}
void showLast(struct listaDoble lista){
    struct tipoNodo *buscar;
    struct tipoNodo *recorre = lista.ultimo;
    char userFind[20];
    printf("\nIntroduce el usuario del que quieres buscar: ");
    scanf("%s",userFind);
    if(recorre==NULL){
        printf("\n La lista está vacía");
    }else{
        while (recorre!=NULL && strcmp(userFind, recorre->userInfo.id)!=0) {
            recorre=recorre->previous;
        }
    }
    buscar=recorre;
    if(buscar==NULL){
        printf("\nNo se ha encontrado el usuario");
        return;
    }else{
        printf("\n La ultima publicación: ");
        show(*recorre);
    }
    
}

void showUserPosts(struct listaDoble lista){
    struct tipoNodo *recorre = lista.primero;
    char userFind[20];
    int contadorMensaje=0;
    printf("\nIntroduce el usuario del que quieres buscar: ");
    scanf("%s",userFind);
    
    if(recorre==NULL){
        printf("\nLa lista está vacia");
        return;
    }else{
        while (recorre!=NULL) {
            if(strcmp(userFind, recorre->userInfo.id)==0){
                show(*recorre);
                contadorMensaje++;
            }
            recorre=recorre->next;
        }
        if(contadorMensaje==0){
            printf("\nEl usuario introducido no tiene publicaciones");
        }
        
    }
}
