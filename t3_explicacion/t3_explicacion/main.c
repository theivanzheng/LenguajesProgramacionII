
#include <stdio.h>
#include <stdlib.h>
int menu(void);

struct tipoInfo{ int key;
double value; };
struct tipoNodo{
    struct tipoInfo information; struct tipoNodo *siguiente; struct tipoNodo *anterior;
};
struct listaDoble{
    struct tipoNodo *primero;
    struct tipoNodo *ultimo;
};

void aniadirAlfinal(struct listaDoble *lista);
void rellenarInfo(struct tipoInfo *info);

int main() {
    struct listaDoble lista; lista.primero = NULL;
    lista.ultimo = NULL;
    int opc;
    //IMPORTANTE INICIALIZAR LA LISTA VACIA
    lista.primero=NULL;
    lista.ultimo=NULL;
    do{
        opc=menu();
        switch(opc){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
                
        }
        
    }while(opc!=0);
    return 0;
}

int menu(void){
    int opc=0;
    do{
        printf("\n\t1.- Visualizar la información");
        printf("\n\t2.- Aniadir al final");
        printf("\n\t3.- Buscar con key");
        printf("\n\t4.- Eliminar nodo al final");
        printf("\n\t5.- Aniadir en una lista ordenada por key");
        printf("\n\t0.- Salir");

        printf("\nIntroduce una opción: ");
        scanf("%d",&opc);
      
    }while(opc<0||opc>5);
    return opc;
}

void aniadirAlfinal(struct listaDoble *lista){
    struct tipoNodo *nuevo;
    
    //1.- Reservo memoria
    nuevo=(struct tipoNodo *) malloc(sizeof(struct tipoNodo));
    if(nuevo==NULL){
        printf("\n**ERROR**");
        return;
    }
    //2.- Añado información
    rellenarInfo(&nuevo->information);
    //3.- Conecto con la lista
        //Tengo 2 casos: 1.- la lista está vacía 2.- la lista ya tenga nodos
    if(lista->primero==NULL){
        lista->primero=nuevo;
        lista->ultimo=nuevo;
        //Inicializo sus siguientes y anteriores
        nuevo->siguiente=NULL;
        nuevo->anterior=NULL;
    }else{//La lista ya tiene nodos
        //Insertar por detrás
        nuevo->siguiente=NULL;
        nuevo->anterior = lista->ultimo;
        lista->ultimo->siguiente=nuevo;
        lista->ultimo=nuevo;
        
    }
}

void rellenarInfo(struct tipoInfo *info){
    printf("\n\tIntroduce la clave: ");
    scanf("%d",&info->key);
    printf("\n\tIntroduce el valor: ");
    scanf("%lf",&info->value);
}
